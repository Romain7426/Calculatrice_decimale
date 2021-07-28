#include "decimal_global.h"
#include "decimal.h" 
#include "decimal_stack.h" 
#include "decimal_vm.h" 
#include "decimal_bytecode_type.h" 

enum { DECIMAL_VM_ENV__ERROR_BUFFER_SIZE  = (1 << 11) }; 
enum { DECIMAL_VM_ENV__STRING_STACK_SIZE  = (1 << 12) }; 

struct decimal_vm_env_t { 
  uint8_t malloced_flag; // 0 if not, 1 if yes. 
  
  int stdlog_d; // Foreign — we don't own it; valid only if 'stdlog_d > 0' 
  
  uint8_t error_id; 
  char    error_str[DECIMAL_VM_ENV__ERROR_BUFFER_SIZE]; 
  
  char     string_stack[DECIMAL_VM_ENV__STRING_STACK_SIZE]; 
  uint16_t string_stack_nb; 

  decimal_env_t * decimal_env; 
  decimal_stack_t * stack; 
  uint8_t * bytecode_data; 
  uint16_t  bytecode_size; 
  uint16_t  bytecode_pc; 
  uint8_t   halted_huh; 
  const char * const_string_array; 
  uint16_t     const_string_sizeof; 
}; 


enum { DECIMAL_VM_ENV__SIZEOF__actual = sizeof(decimal_vm_env_t) }; 
const size_t decimal_vm_env__sizeof = sizeof(decimal_vm_env_t); 



decimal_vm_env_t * decimal_vm_env__bzero(decimal_vm_env_t * this) { 
  const uint8_t malloced_flag = this -> malloced_flag; 
  const int stdlog_d = this -> stdlog_d; 
  bzero(this, sizeof(*this)); 
  this -> stdlog_d = stdlog_d; 
  this -> malloced_flag = malloced_flag; 
  return this; 
}; 

decimal_vm_env_t * decimal_vm_env__reset0(decimal_vm_env_t * this) { 
  decimal_vm_env__bzero(this); 
  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb++; 
  return this; 
}; 

decimal_vm_env_t * decimal_vm_env__reset(decimal_vm_env_t * this, decimal_env_t * decimal_env, decimal_stack_t * stack, uint8_t * bytecode_data, const uint16_t bytecode_size, const uint16_t bytecode_start, const char * const_string_array, const uint16_t const_string_sizeof) { 
  decimal_vm_env__bzero(this); 
  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb++; 
  this -> decimal_env = decimal_env; 
  this -> stack = stack; 
  this -> bytecode_data = bytecode_data; 
  this -> bytecode_size = bytecode_size; 
  this -> bytecode_pc   = bytecode_start; 
  this -> halted_huh = false; 
  this -> const_string_array  = const_string_array; 
  this -> const_string_sizeof = const_string_sizeof; 
  return this; 
}; 

decimal_vm_env_t * decimal_vm_env__make_m(const int stdlog_d) { 
  decimal_vm_env_t * this; 
  this = (decimal_vm_env_t *) malloc(sizeof(*this)); 
  if (NULL == this) return NULL; 
  decimal_vm_env__make_r(this, stdlog_d); 
  this -> malloced_flag = 1; 
  return this; 
}; 

decimal_vm_env_t * decimal_vm_env__make_r(decimal_vm_env_t * this, const int stdlog_d) { 
  decimal_vm_env__reset0(this); 
  this -> stdlog_d = stdlog_d; 
  return this; 
}; 

decimal_vm_env_t * decimal_vm_env__make_b(const uint16_t buffer_size, uint8_t * buffer, uint16_t * buffer_size_used_r, const int stdlog_d) { 
  decimal_vm_env_t * this; 
  if (buffer_size < (int)sizeof(*this)) return NULL; 
  this = (decimal_vm_env_t *) buffer; 
  if (NULL != buffer_size_used_r) *buffer_size_used_r = sizeof(*this); 
  return decimal_vm_env__make_r(this, stdlog_d); 
}; 
 

void decimal_vm_env__delete_r(decimal_vm_env_t * this) {
  bzero(this, sizeof(*this)); 
}; 

void decimal_vm_env__delete(decimal_vm_env_t * this) {
  const int malloced_flag = this -> malloced_flag; 
  decimal_vm_env__delete_r(this); 
  if (1 == malloced_flag) { free(this); }; 
}; 

int decimal_vm_env__get_stdlog(const decimal_vm_env_t * this) { 
  return this -> stdlog_d; 
}; 

int_decimal_error_t decimal_vm_env__get_error_id(const decimal_vm_env_t * this) { 
  return this -> error_id; 
}; 

const char * decimal_vm_env__get_error_str(const decimal_vm_env_t * this) { 
  return this -> error_str; 
}; 

static int rstr_stack_lookup(const int stack_nb, const char * stack, const int rstr_len, const char * rstr) { 
  //if (NULL == cstr) return 0; 
  //if ('\0' == *cstr) return 0; 
  int stack_i = 1; 
  //const int cstr_len = strlen(cstr); 
  for (;;) { 
    if (stack_i >= stack_nb) { return ~0; }; 
    const int len = strlen(stack + stack_i); 
    if (len != rstr_len) { stack_i += len + 1; continue; }; 
    const int equal_huh = (0 == bcmp(stack + stack_i, rstr, len)); 
    if (equal_huh) { return stack_i; }; 
    stack_i += len + 1; 
  }; 
  assert(false); 
}; 

const char * decimal_vm_env__strcopy(decimal_vm_env_t * this, const char * cstr) { 
  if (NULL ==  cstr) { return this -> string_stack; }; 
  if ('\0' == *cstr) { return this -> string_stack; }; 
  const int len0 = strlen(cstr); 
  const int lookedup = rstr_stack_lookup(this -> string_stack_nb, this -> string_stack, len0, cstr); 
  if (~lookedup != 0) { return this -> string_stack + lookedup; }; 
  const int len1 = 1 + len0; 
  const int available_men = DECIMAL_VM_ENV__STRING_STACK_SIZE - this -> string_stack_nb; 
  if (len1 > available_men) { 
    this -> error_id = DECIMAL__VM__STRCOPY; 
    snprintf(this -> error_str, DECIMAL_VM_ENV__ERROR_BUFFER_SIZE, "Not enough space to copy the string (mem needed: %d ; mem left: %d ; cstr: '%s')", len1, available_men, cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return NULL; 
  }; 
  char * new_str = this -> string_stack + this -> string_stack_nb; 
  bcopy(cstr, new_str, len1); 
  this -> string_stack_nb += len1; 
  return new_str; 
}; 




// *********************** VM *********************** 


int decimal_vm__halted_huh(const decimal_vm_env_t * this) { 
  return this -> halted_huh; 
}; 


int_decimal_error_t decimal_vm__step(decimal_vm_env_t * this) { 
  int_decimal_error_t error_id; 
  error_id = DECIMAL__VM__ERROR_ID_NOT_ASSIGNED; 
  goto label__start; 

  assert(false); 
  
  label__exit: { 
    return error_id; 
  }; 

  assert(false); 

 label__error__bytecode_overflow: { 
    error_id = DECIMAL__VM__PC_OUT_OF_BOUNDS; 
    snprintf(this -> error_str, sizeof(this -> error_str), "PC out of bytecode bounds"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return error_id; 
  }; 
  
  assert(false); 

 label__error__stack_overflow: { 
    error_id = DECIMAL__VM__STACK_OVERFLOW; 
    snprintf(this -> error_str, sizeof(this -> error_str), "Stack overflow"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return error_id; 
  }; 

  assert(false); 

 label__error__stack_underflow: { 
    error_id = DECIMAL__VM__STACK_UNDERFLOW; 
    snprintf(this -> error_str, sizeof(this -> error_str), "Stack underflow"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return error_id; 
  }; 

  assert(false); 

 label__error__const_string_overflow: { 
    error_id = DECIMAL__VM__CONST_STRING_ARRAY_OUT_OF_BOUNDS; 
    snprintf(this -> error_str, sizeof(this -> error_str), "PC out of bytecode bounds"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return error_id; 
  }; 
  
  assert(false); 

 label__error__null_bytecode: { 
    error_id = DECIMAL__VM__NULL_BYTECODE; 
    snprintf(this -> error_str, sizeof(this -> error_str), "Encountered null bytecode"); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return error_id; 
  }; 
  

  label__start: {}; 
  if (this -> halted_huh) { 
    error_id = DECIMAL__OK; 
    goto label__exit; 
  }; 
  
  if (this -> bytecode_pc >= this -> bytecode_size) { goto label__error__bytecode_overflow; }; 
  
  const int_decimal_bytecode_type_t bytecode_type = this -> bytecode_data[this -> bytecode_pc]; 

  error_id = DECIMAL__OK; 
  
  switch (bytecode_type) { 
#define X(ident, value) case ident: goto label__bytecode__##ident; break; 
    DECIMAL_BYTECODE_TYPE__LIST
#undef X 
  }; 

  assert(false); 

 label__bytecode__DECIMAL__BYTECODE__NULL: { 
    goto label__error__null_bytecode; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__HALT: { 
    this -> halted_huh = true; 
    goto label__exit; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__NOP: { 
    this -> bytecode_pc++; 
    goto label__exit; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__PUSH_ZERO: { 
    decimal_t * new_d_r = decimal_stack__push(this -> stack); 
    if (NULL == new_d_r) goto  label__error__stack_overflow; 
    decimal__zero_r(this -> decimal_env, new_d_r); 
    this -> bytecode_pc++; 
    goto label__exit; 
  }; 
  
  assert(false); 
  
#define BYTECODE_READ_UINT16(__uint16_var__) {				\
    if ((this -> bytecode_pc + sizeof(uint16_t)) > this -> bytecode_size) goto label__error__bytecode_overflow; \
    __uint16_var__ = *((uint16_t *)(((uint8_t *)this -> bytecode_data) + this -> bytecode_pc)); \
    this -> bytecode_pc += 2;						\
  }; 
  
#define CONST_STRING_GET_CSTR(__cstr_var__,__str_id__) {			\
    if ((__str_id__) >= this -> const_string_sizeof) goto label__error__const_string_overflow; \
    __cstr_var__ = this -> const_string_array + str_id;			\
  }; 

#define STACK_PUSH(__var_new_d_r__) {					\
    __var_new_d_r__ = decimal_stack__push(this -> stack);		\
    if (NULL == __var_new_d_r__) goto label__error__stack_overflow;	\
  }; 
  
#define STACK_TOP(__var_top_d_r__) {					\
    __var_top_d_r__ = decimal_stack__top(this -> stack);		\
    if (NULL == __var_top_d_r__) goto label__error__stack_underflow;	\
  }; 
  
#define STACK_POP() {							\
    error_id = decimal_stack__pop(this -> stack);			\
    if (DECIMAL__OK != error_id) goto label__error__stack_underflow;	\
  }; 


 label__bytecode__DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__INT: { 
    uint16_t str_id; 
    const char * cstr; 
    decimal_t * new_d_r; 
    this -> bytecode_pc++; 
    BYTECODE_READ_UINT16(str_id); 
    CONST_STRING_GET_CSTR(cstr,str_id); 
    STACK_PUSH(new_d_r); 
    const int entier = atoi(cstr); 
    decimal__cast_from_int_r(this -> decimal_env, new_d_r, entier); 
    goto label__exit; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__FLOAT_V: { 
    uint16_t str_id; 
    const char * cstr; 
    decimal_t * new_d_r; 
    this -> bytecode_pc++; 
    BYTECODE_READ_UINT16(str_id); 
    CONST_STRING_GET_CSTR(cstr,str_id); 
    STACK_PUSH(new_d_r); 
    const float reel = atof(cstr); 
    decimal__cast_from_float_r(this -> decimal_env, new_d_r, reel); 
    goto label__exit; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__FLOAT_D: { 
    uint16_t str_id; 
    const char * cstr; 
    decimal_t * new_d_r; 
    this -> bytecode_pc++; 
    BYTECODE_READ_UINT16(str_id); 
    CONST_STRING_GET_CSTR(cstr,str_id); 
    //dputs_array(STDERR_FILENO, "XXXX - ", cstr, "\n"); 
    STACK_PUSH(new_d_r); 
    const float reel = atof(cstr); 
    decimal__cast_from_float_r(this -> decimal_env, new_d_r, reel); 
    goto label__exit; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__FLOAT_E: { 
    uint16_t str_id; 
    const char * cstr; 
    decimal_t * new_d_r; 
    this -> bytecode_pc++; 
    BYTECODE_READ_UINT16(str_id); 
    CONST_STRING_GET_CSTR(cstr,str_id); 
    STACK_PUSH(new_d_r); 
    const float reel = atof(cstr); 
    decimal__cast_from_float_r(this -> decimal_env, new_d_r, reel); 
    goto label__exit; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__INC: { 
    decimal_t * top_d_r; 
    STACK_TOP(top_d_r); 
    decimal__inc_r(this -> decimal_env, top_d_r); 
    this -> bytecode_pc++; 
    goto label__exit; 
  }; 
  
  assert(false); 

 label__bytecode__DECIMAL__BYTECODE__DEC: { 
    decimal_t * top_d_r; 
    STACK_TOP(top_d_r); 
    decimal__dec_r(this -> decimal_env, top_d_r); 
    this -> bytecode_pc++; 
    goto label__exit; 
  }; 
  
  assert(false); 

 label__bytecode__DECIMAL__BYTECODE__NEG: { 
    decimal_t * top_d_r; 
    STACK_TOP(top_d_r); 
    decimal__neg_r(this -> decimal_env, top_d_r); 
    this -> bytecode_pc++; 
    goto label__exit; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__ADD: { 
    //dputs(STDERR
    decimal_t * top_d_r; 
    decimal_t * top_e_r; 
    STACK_TOP(top_e_r); 
    STACK_POP(); 
    STACK_TOP(top_d_r); 
    //decimal__print_ln_r(stderr_d, this -> decimal_env, top_d_r); 
    //decimal__print_ln_r(stderr_d, this -> decimal_env, top_e_r); 
    decimal__add_r(this -> decimal_env, top_d_r, top_e_r); 
    //decimal__print_ln_r(stderr_d, this -> decimal_env, top_d_r); 
    this -> bytecode_pc++; 
    goto label__exit; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__SUB: { 
    decimal_t * top_d_r; 
    decimal_t * top_e_r; 
    STACK_TOP(top_e_r); 
    STACK_POP(); 
    STACK_TOP(top_d_r); 
    decimal__sub_r(this -> decimal_env, top_d_r, top_e_r); 
    this -> bytecode_pc++; 
    goto label__exit; 
  }; 
  
  assert(false); 
  
 label__bytecode__DECIMAL__BYTECODE__MULT: { 
    decimal_t * top_d_r; 
    decimal_t * top_e_r; 
    STACK_TOP(top_e_r); 
    STACK_POP(); 
    STACK_TOP(top_d_r); 
    decimal__mult_r(this -> decimal_env, top_d_r, top_e_r); 
    this -> bytecode_pc++; 
    goto label__exit; 
  }; 
  
  assert(false); 

 label__bytecode__DECIMAL__BYTECODE__DIV: { 
    decimal_t * top_d_r; 
    decimal_t * top_e_r; 
    STACK_TOP(top_e_r); 
    STACK_POP(); 
    STACK_TOP(top_d_r); 
    decimal__div_r(this -> decimal_env, top_d_r, top_e_r); 
    this -> bytecode_pc++; 
    goto label__exit; 
  }; 



  
  assert(false); 
}; 


int_decimal_error_t decimal_vm__run(decimal_vm_env_t * this) { 
  int_decimal_error_t error_id; 
  error_id = DECIMAL__VM__ERROR_ID_NOT_ASSIGNED; 
  
  for (;;) { 
    if (this -> halted_huh) break; 
    error_id = decimal_vm__step(this); 
    if (error_id != DECIMAL__OK) break; 
  }; 
  
  return error_id; 
}; 



