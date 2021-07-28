#include "decimal_global.h"
#include "decimal_token.h" 
#include "decimal_token_type.h" 

enum { INT_DECIMAL_TOKEN_TOP = sizeof(int_decimal_token_t) == 1 ? UINT8_MAX : sizeof(int_decimal_token_t) == 2 ? UINT16_MAX : sizeof(int_decimal_token_t) == 4 ? UINT32_MAX : sizeof(int_decimal_token_t) == 8 ? UINT64_MAX : -1 }; 
enum { INT_DECIMAL_TOKEN_MAX = INT_DECIMAL_TOKEN_TOP - 2 }; // The top value («~0») is used as an invalid value. 
 
const int_decimal_token_t int_decimal_token_max = INT_DECIMAL_TOKEN_MAX; 
const int_decimal_token_t DECIMAL_TOKEN_I_INVALID__compiled_value = DECIMAL_TOKEN_I_INVALID; 
const int_decimal_token_t DECIMAL_TOKEN_I_BOF__compiled_value = DECIMAL_TOKEN_I_BOF; 



enum { 
  DECIMAL_TOKEN__OK = 0, 
  DECIMAL_TOKEN__STRCOPY = INT8_MIN, 
  DECIMAL_TOKEN__FD_NEG, 
  DECIMAL_TOKEN__FDOPEN, 
}; 


//#include "decimal_token_env.ci" 

enum { DECIMAL_TOKEN__SIZE = 512 }; 
// Roughly, the number of produced tokens will be around 12.5% of the size of the source file. Therefore, if we have a 500k input file, around 69k would be produced. 
// On another file, I have 21%. 


enum { DECIMAL_TOKEN_ENV__SRCFILE_STACK_SIZE = (1 << 11) }; 
enum { DECIMAL_TOKEN_ENV__SRCVAL_STACK_SIZE  = (1 << 14) }; 
enum { DECIMAL_TOKEN_ENV__ERROR_BUFFER_SIZE  = (1 << 11) }; 
enum { DECIMAL_TOKEN_ENV__STRING_STACK_SIZE  = (1 << 12) }; 

struct decimal_token_env_t { 
  uint8_t malloced_flag; // 0 if not, 1 if yes. 
  
  int stdlog_d; // Foreign — we don't own it; valid only if 'stdlog_d > 0' 
  
  uint8_t error_id; 
  char    error_str[DECIMAL_TOKEN_ENV__ERROR_BUFFER_SIZE]; 
  
  char     string_stack[DECIMAL_TOKEN_ENV__STRING_STACK_SIZE]; 
  uint16_t string_stack_nb; 
  
  char     srcfile_stack[DECIMAL_TOKEN_ENV__SRCFILE_STACK_SIZE]; 
  uint16_t srcfile_stack_nb; 
  
  char     srcval_stack[DECIMAL_TOKEN_ENV__SRCVAL_STACK_SIZE]; 
  uint16_t srcval_stack_nb; 
  
  // STACK 
  const char *             srcfile[DECIMAL_TOKEN__SIZE]; 
  const char *             srcval [DECIMAL_TOKEN__SIZE]; 
  int_decimal_token_type_t type   [DECIMAL_TOKEN__SIZE]; 
  int32_t                  offset0[DECIMAL_TOKEN__SIZE]; 
  int24_packed_t           line1  [DECIMAL_TOKEN__SIZE]; 
  uint16_t                 column0[DECIMAL_TOKEN__SIZE]; 
  int_decimal_token_t      nb; 
  
  // 'SYNTAX_MASTER' and 'SYNTAX_KEYWORD' are a way to extend the token sets. 
  // For instance, in the case of the game, we want to add a 'menu' syntax. 
  // We use those things. 
  // SYNTAX_MASTER 
  const char *   master__array[DECIMAL_TOKEN__SYNTAX_MASTER__SIZE]; 
  int            master__len  [DECIMAL_TOKEN__SYNTAX_MASTER__SIZE]; 
  int8_t         master__nb; 
  
  // SYNTAX_KEYWORD 
  const char *   syntax_keyword__array[DECIMAL_TOKEN__SYNTAX_KEYWORD__SIZE]; 
  int            syntax_keyword__len  [DECIMAL_TOKEN__SYNTAX_KEYWORD__SIZE]; 
  int8_t         syntax_keyword__nb; 
}; 




static void assert_compile__dkushdsuf2387645kjhsdfr1(void) { 
  ASSERT_COMPILE(DECIMAL_TOKEN__SIZE     <= INT_DECIMAL_TOKEN_MAX); 
  ASSERT_COMPILE(DECIMAL_TOKEN_I_INVALID >  INT_DECIMAL_TOKEN_MAX); 
  ASSERT_COMPILE(DECIMAL_TOKEN_I_INVALID <= INT_DECIMAL_TOKEN_TOP); 
  ASSERT_COMPILE(DECIMAL_TOKEN_I_BOF     >  INT_DECIMAL_TOKEN_MAX); 
  ASSERT_COMPILE(DECIMAL_TOKEN_I_BOF     <= INT_DECIMAL_TOKEN_TOP); 
}; 

enum { DECIMAL_TOKEN_ENV__SIZEOF = sizeof(decimal_token_env_t) }; 
const int32_t decimal_token_env__sizeof = DECIMAL_TOKEN_ENV__SIZEOF; 

static void assert_compile__dakjdds4388ds1p(void) { 
  ASSERT_COMPILE(INT_DECIMAL_TOKEN_MAX >= DECIMAL_TOKEN__SIZE); 
  
  decimal_token_env_t * this; 
  //ASSERT_COMPILE(sizeof(this ->  srcval) >= sizeof(int_decimal_string_t    )); 
  ASSERT_COMPILE(sizeof(this ->    type) >= sizeof(int_decimal_token_type_t)); 
  //ASSERT_COMPILE(sizeof(this -> srcfile) >= sizeof(int_decimal_string_t    )); 
  ASSERT_COMPILE(sizeof(this ->      nb) >= sizeof(int_decimal_token_t     )); 
  
  ASSERT_COMPILE(sizeof(this -> master__nb) == sizeof(int8_t)); 
  ASSERT_COMPILE(INT8_MAX >= DECIMAL_TOKEN__SYNTAX_MASTER__SIZE); 
  
  ASSERT_COMPILE(sizeof(this -> syntax_keyword__nb) == sizeof(int8_t)); 
  ASSERT_COMPILE(INT8_MAX >= DECIMAL_TOKEN__SYNTAX_KEYWORD__SIZE); 
}; 

decimal_token_env_t * decimal_token_env__bzero(decimal_token_env_t * this) { 
  const uint8_t malloced_flag = this -> malloced_flag; 
  const int stdlog_d = this -> stdlog_d; 
  bzero(this, sizeof(*this)); 
  this -> stdlog_d = stdlog_d; 
  this -> malloced_flag = malloced_flag; 
  return this; 
}; 

decimal_token_env_t * decimal_token_env__reset(decimal_token_env_t * this) { 
  decimal_token_env__bzero(this); 
  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb++; 
  this -> srcfile_stack[0] = '\0'; 
  this -> srcfile_stack_nb++; 
  this -> srcval_stack[0] = '\0'; 
  this -> srcval_stack_nb++; 
  return this; 
}; 

decimal_token_env_t * decimal_token_env__make_r(decimal_token_env_t * this, const int stdlog_d) {
  decimal_token_env__reset(this); 
  this -> stdlog_d = stdlog_d; 
  return this; 
}; 

decimal_token_env_t * decimal_token_env__make_b(const int bsize, void * bvalue, int * used_size_ref, const int stdlog_d) {
  decimal_token_env_t * this; 
  if (bsize < (int)sizeof(*this)) return NULL; 
  this = (decimal_token_env_t *) bvalue; 
  if (NULL != used_size_ref) *used_size_ref = sizeof(*this); 
  return decimal_token_env__make_r(this, stdlog_d); 
}; 
 
decimal_token_env_t * decimal_token_env__make(const int stdlog_d) {
  decimal_token_env_t * this; 
  this = (decimal_token_env_t *) malloc(sizeof(*this)); 
  if (NULL == this) return NULL; 
  decimal_token_env__make_r(this, stdlog_d); 
  this -> malloced_flag = 1; 
  return this; 
}; 


void decimal_token_env__delete_r(decimal_token_env_t * this) {
  bzero(this, sizeof(*this)); 
}; 

void decimal_token_env__delete(decimal_token_env_t * this) {
  const int malloced_flag = this -> malloced_flag; 
  decimal_token_env__delete_r(this); 
  if (1 == malloced_flag) { 
    free(this); 
  }; 
}; 

int decimal_token__parser__stdlog(const decimal_token_env_t * this) { 
  return this -> stdlog_d; 
}; 


const char * decimal_token_env__strcopy(decimal_token_env_t * this, const char * cstr) { 
  if (NULL ==  cstr) { return this -> string_stack; }; 
  if ('\0' == *cstr) { return this -> string_stack; }; 
  const int len1 = 1 + strlen(cstr); 
  if (this -> string_stack_nb + len1 > DECIMAL_TOKEN_ENV__STRING_STACK_SIZE) { 
    this -> error_id = DECIMAL_TOKEN__STRCOPY; 
    snprintf(this -> error_str, DECIMAL_TOKEN_ENV__ERROR_BUFFER_SIZE, "Not enough space in the decimal buffer to copy the string (mem needed: %d ; mem left: %d ; cstr: '%s')", len1, DECIMAL_TOKEN_ENV__STRING_STACK_SIZE - this -> string_stack_nb, cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return NULL; 
  }; 
  char * new_str = this -> string_stack + this -> string_stack_nb; 
  bcopy(cstr, new_str, len1); 
  this -> string_stack_nb += len1; 
  return new_str; 
}; 


static int cstr_stack_lookup(const int stack_size, const int stack_nb, const char * stack, const int rstr_len, const char * rstr) { 
  int stack_i = 0; 
  for (;;) { 
    if (stack_i >= stack_size) { return ~0; }; 
    const int len = strlen(stack + stack_i); 
    if (len != rstr_len) { stack_i += len + 1; continue; }; 
    const int equal_huh = (0 == bcmp(stack + stack_i, rstr, len)); 
    if (equal_huh) { return stack_i; }; 
    stack_i += len + 1; 
  }; 
}; 

static const char * decimal_token_env__srcfile_stack__lookup_push(decimal_token_env_t * this, const int rstr_len, const char * rstr) { 
  if (NULL ==  rstr) { return this -> srcfile_stack; }; 
  if ('\0' == *rstr) { return this -> srcfile_stack; }; 
  const int uplooked_index = cstr_stack_lookup(ARRAY_SIZE(this -> srcfile_stack), this -> srcfile_stack_nb, this -> srcfile_stack, rstr_len, rstr); 
  if (0 <= uplooked_index && uplooked_index < this -> srcfile_stack_nb) { return this -> srcfile_stack + uplooked_index; }; 
  const int len1 = 1 + rstr_len; 
  if (this -> srcfile_stack_nb + len1 > DECIMAL_TOKEN_ENV__SRCFILE_STACK_SIZE) { 
    this -> error_id = DECIMAL_TOKEN__STRCOPY; 
    snprintf(this -> error_str, DECIMAL_TOKEN_ENV__ERROR_BUFFER_SIZE, "Not enough space in the decimal token srcfile_stack to copy the string (mem needed: %d ; mem left: %d ; rstr: TBD)", len1, DECIMAL_TOKEN_ENV__SRCFILE_STACK_SIZE - this -> srcfile_stack_nb); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return NULL; 
  }; 
  char * new_str = this -> srcfile_stack + this -> srcfile_stack_nb; 
  bcopy(rstr, new_str, rstr_len); 
  *(new_str + rstr_len) = '\0'; 
  this -> srcfile_stack_nb += len1; 
  return new_str; 
}; 

static const char * decimal_token_env__srcval_stack__lookup_push(decimal_token_env_t * this, const int rstr_len, const char * rstr) { 
  if (NULL ==  rstr) { return this -> srcval_stack; }; 
  if ('\0' == *rstr) { return this -> srcval_stack; }; 
  const int uplooked_index = cstr_stack_lookup(ARRAY_SIZE(this -> srcval_stack), this -> srcval_stack_nb, this -> srcval_stack, rstr_len, rstr); 
  if (0 <= uplooked_index && uplooked_index < this -> srcval_stack_nb) { return this -> srcval_stack + uplooked_index; }; 
  const int len1 = 1 + rstr_len; 
  if (this -> srcval_stack_nb + len1 > DECIMAL_TOKEN_ENV__SRCVAL_STACK_SIZE) { 
    this -> error_id = DECIMAL_TOKEN__STRCOPY; 
    snprintf(this -> error_str, DECIMAL_TOKEN_ENV__ERROR_BUFFER_SIZE, "Not enough space in the decimal token srcval_stack to copy the string (mem needed: %d ; mem left: %d ; rstr: TBD)", len1, DECIMAL_TOKEN_ENV__SRCVAL_STACK_SIZE - this -> srcval_stack_nb); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return NULL; 
  }; 
  char * new_str = this -> srcval_stack + this -> srcval_stack_nb; 
  bcopy(rstr, new_str, rstr_len); 
  *(new_str + rstr_len) = '\0'; 
  this -> srcval_stack_nb += len1; 
  return new_str; 
}; 

static const char * decimal_token_env__string_stack__lookup_push(decimal_token_env_t * this, const int rstr_len, const char * rstr) { 
  if (NULL ==  rstr) { return this -> string_stack; }; 
  if ('\0' == *rstr) { return this -> string_stack; }; 
  const int uplooked_index = cstr_stack_lookup(ARRAY_SIZE(this -> string_stack), this -> string_stack_nb, this -> string_stack, rstr_len, rstr); 
  if (0 <= uplooked_index && uplooked_index < this -> string_stack_nb) { return this -> string_stack + uplooked_index; }; 
  const int len1 = 1 + rstr_len; 
  if (this -> string_stack_nb + len1 > DECIMAL_TOKEN_ENV__STRING_STACK_SIZE) { 
    this -> error_id = DECIMAL_TOKEN__STRCOPY; 
    snprintf(this -> error_str, DECIMAL_TOKEN_ENV__ERROR_BUFFER_SIZE, "Not enough space in the decimal token string_stack to copy the string (mem needed: %d ; mem left: %d ; rstr: TBD)", len1, DECIMAL_TOKEN_ENV__STRING_STACK_SIZE - this -> string_stack_nb); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return NULL; 
  }; 
  char * new_str = this -> string_stack + this -> string_stack_nb; 
  bcopy(rstr, new_str, rstr_len); 
  *(new_str + rstr_len) = '\0'; 
  this -> string_stack_nb += len1; 
  return new_str; 
}; 



// *** TOKEN_STACK *** 

int decimal_token__push(decimal_token_env_t * this, const int srcval_len, const char * srcval_rstr, const int token_type, const char * srcfile, const int offset0, const int line1, const int column0) { 
  assert(DECIMAL_TOKEN__SIZE > this -> nb); 
  const int idx          =  this -> nb; 
  this -> srcfile[idx]   = decimal_token_env__srcfile_stack__lookup_push(this, strlen(srcfile), srcfile); 
  this -> srcval [idx]   = decimal_token_env__srcval_stack__lookup_push(this, srcval_len, srcval_rstr); 
  this -> type   [idx]   =  token_type; 
  this -> srcfile[idx]   =     srcfile; 
  this -> offset0[idx]   =     offset0; 
  //this -> line1[idx]   =       line1; 
  INT24_PACKED_ASSIGN_UNPACKED(this -> line1[idx], line1); 
  this -> column0[idx]   =     column0; 
  this -> nb++; 
  return idx; 
}; 

const char * decimal_token__get_srcfile_cstr(const decimal_token_env_t * this, const int token_idx){  
  return this -> srcfile[token_idx]; 
}; 
 
const char * decimal_token__get_srcval_cstr(const decimal_token_env_t * this, const int token_idx){  
  return this -> srcval[token_idx]; 
}; 
 
int decimal_token__get_type(const decimal_token_env_t * this, const int token_idx){  
  return this -> type[token_idx]; 
}; 

void decimal_token__syntax_filtering__adjust_type(decimal_token_env_t * this, const int token_idx, const int adjusted_type) { 
  this -> type[token_idx] = adjusted_type; 
}; 

int decimal_token__get_offset0(const decimal_token_env_t * this, const int token_idx){  
  return this -> offset0[token_idx]; 
}; 
 
int decimal_token__get_line1(const decimal_token_env_t * this, const int token_idx){ 
  //return this -> line1[token_idx]; 
  int line1; 
  INT24_PACKED_READ(this -> line1[token_idx],line1); 
  return line1; 
}; 
 
int decimal_token__get_column0(const decimal_token_env_t * this, const int token_idx){  
  return this -> column0[token_idx]; 
}; 



// *** STATS QUERY *** 

int decimal_token__get_count(const decimal_token_env_t * this) { 
  return this -> nb; 
}; 

int decimal_token__get_size(const decimal_token_env_t * this) { 
  return DECIMAL_TOKEN__SIZE; 
}; 


// *** SYNTAX_MASTER *** 
#if 1 
static int decimal_token__master_push__common(decimal_token_env_t * this, const char * ident_lower_well_allocated) { 
  assert(this -> master__nb < DECIMAL_TOKEN__SYNTAX_MASTER__SIZE); 
  const int index = this -> master__nb; 
  this -> master__nb++; 
  this -> master__array[index] = ident_lower_well_allocated; 
  this -> master__len[index] = strlen(ident_lower_well_allocated); 
  return DECIMAL_TOKEN__SYNTAX_MASTER__BASE + index; 
}; 
 
int decimal_token__master_push_cstr(decimal_token_env_t * this, const char * ident_cstr) { 
  const int  ident_len = strlen(ident_cstr); 
  char ident_lower_cstr[ident_len]; 
  for (int i = 0; i <= ident_len; i++) { 
    ident_lower_cstr[i] = tolower(ident_cstr[i]); 
  }; 
  const char * ident_lower_well_allocated = decimal_token_env__srcval_stack__lookup_push(this, ident_len, ident_lower_cstr); 
  return decimal_token__master_push__common(this, ident_lower_well_allocated); 
}; 

int decimal_token__master_push_pstr(decimal_token_env_t * this, const int ident_pstr) { 
#if 1 
  assert(false); 
  return ~0; 
#else 
  const char * ident_cstr = decimal_string__get_cstr(this -> string_env, ident_pstr); 
  return decimal_token__master_push_cstr(this, ident_cstr); 
#endif 
}; 

int decimal_token__master_count(const decimal_token_env_t * this) { 
  return this -> master__nb; 
}; 

const int * decimal_token__master_len(const decimal_token_env_t * this) { 
  return this -> master__len; 
}; 
 
const char * * decimal_token__master_cstr(const decimal_token_env_t * this) { 
#if defined(__clang__)
  #pragma clang diagnostic push 
  #pragma clang diagnostic ignored "-Wcast-qual" 
#endif
  
  return (const char * * ) this -> master__array; 
  
#if defined(__clang__)
  #pragma clang diagnostic pop 
#endif
}; 
#endif  



// *** SYNTAX_KEYWORD *** 
#if 1 
static int decimal_token__syntax_keyword_push__common(decimal_token_env_t * this, const char * ident_lower_well_allocated) { 
  assert(this -> syntax_keyword__nb < DECIMAL_TOKEN__SYNTAX_KEYWORD__SIZE); 
  const int index = this -> syntax_keyword__nb; 
  this -> syntax_keyword__nb++; 
  this -> syntax_keyword__array[index] = ident_lower_well_allocated; 
  this -> syntax_keyword__len[index] = strlen(ident_lower_well_allocated); 
  return DECIMAL_TOKEN__SYNTAX_KEYWORD__BASE + index; 
}; 
 
int decimal_token__syntax_keyword_push_cstr(decimal_token_env_t * this, const char * ident_cstr) { 
  const int  ident_len = strlen(ident_cstr); 
  char ident_lower_cstr[ident_len]; 
  for (int i = 0; i <= ident_len; i++) { 
    ident_lower_cstr[i] = tolower(ident_cstr[i]); 
  }; 
  const char * ident_lower_well_allocated = decimal_token_env__srcval_stack__lookup_push(this, ident_len, ident_lower_cstr); 
  return decimal_token__syntax_keyword_push__common(this, ident_lower_well_allocated); 
}; 

int decimal_token__syntax_keyword_push_pstr(decimal_token_env_t * this, const int ident_pstr) { 
#if 1 
  assert(false); 
  return ~0; 
#else 
  const char * ident_cstr = decimal_string__get_cstr(this -> string_env, ident_pstr); 
  return decimal_token__syntax_keyword_push_cstr(this, ident_cstr); 
#endif 
}; 

int decimal_token__syntax_keyword_count(const decimal_token_env_t * this) { 
  return this -> syntax_keyword__nb; 
}; 

const int * decimal_token__syntax_keyword_len(const decimal_token_env_t * this) { 
  return this -> syntax_keyword__len; 
}; 
 
const char * * decimal_token__syntax_keyword_cstr(const decimal_token_env_t * this) { 
#if defined(__clang__)
  #pragma clang diagnostic push 
  #pragma clang diagnostic ignored "-Wcast-qual" 
#endif
  
  return (const char * * ) this -> syntax_keyword__array; 
  
#if defined(__clang__)
  #pragma clang diagnostic pop 
#endif
}; 
#endif  



// *** PRINT *** 

void decimal_token__print_one_token(const int filedes, const decimal_token_env_t * this, const int token_i) {
  //const int filedes = fileno(yydecimalout); 
  const char * token_i__str                 = int_string__stack(token_i); 
  const int    token_i__str__spaces_nb      = MAX(0, 6 - strlen(token_i__str)); 
  const int    token_type                   = this -> type[token_i]; 
  const char * token_type_i_str             = int_string__stack(token_type); //decimal_parser__token_type__get_cstr(token_type); 
  const int    token_type_i_str__spaces_nb  = MAX(0, 3 - strlen(token_type_i_str)); 
  const char * token_type_str               = decimal_token__type_get_cstr(token_type); //decimal_parser__token_type__get_cstr(token_type); 
  const int    token_type_str__spaces_nb    = MAX(0, 18 - strlen(token_type_str)); 
  const char * token_srcval_cstr            = decimal_token__get_srcval_cstr(this, token_i); 
  const int    token_srcval_cstr__spaces_nb = MAX(0, 47 - strlen(token_srcval_cstr)); 
  const int    srcval_len                   = strlen(token_srcval_cstr); 
  const char * token_len_str                = int_string__stack(srcval_len); 
  const int    token_len_str_len            = strlen(token_len_str); 
  const int    token_len_str_len_spaces_nb  = MAX(0, 6 - token_len_str_len); 

  const int    token_line1                    = decimal_token__get_line1(this, token_i); 
  const char * token_line1_cstr               = int_string__stack(token_line1); 
  const int    token_line1_cstr_len           = strlen(token_line1_cstr); 
  const int    token_line1_cstr_len_spaces_nb = MAX(0, 6 - token_line1_cstr_len); 

  const int    token_column0                    = this -> column0[token_i]; 
  const char * token_column0_cstr               = int_string__stack(token_column0); 
  const int    token_column0_cstr_len           = strlen(token_column0_cstr); 
  const int    token_column0_cstr_len_spaces_nb = MAX(0, 6 - token_column0_cstr_len); 

  const int    token_offset0                    = this -> offset0[token_i]; 
  const char * token_offset0_cstr               = int_string__stack(token_offset0); 
  const int    token_offset0_cstr_len           = strlen(token_offset0_cstr); 
  const int    token_offset0_cstr_len_spaces_nb = MAX(0, 6 - token_offset0_cstr_len); 

  const char * token_srcfile_cstr               = this -> srcfile[token_i]; 
  const int    token_srcfile_cstr_len           = strlen(token_srcfile_cstr); 
  const int    token_srcfile_cstr_len_spaces_nb = MAX(0, 6 - token_srcfile_cstr_len); 
  
  dputs(filedes, "IDX "); 
  dput_spaces(filedes, token_i__str__spaces_nb); 
  dputs(filedes, token_i__str); 
  dputs(filedes, ": "); 
  dputs(filedes, token_type_str); 
  dputs(filedes, "("); 
  //dput_spaces(filedes, token_type_i_str__spaces_nb); 
  dputs(filedes, token_type_i_str); 
  dputs(filedes, ")"); 
  //dput_spaces(filedes, token_type_str__spaces_nb); 
  dput_spaces(filedes, token_type_i_str__spaces_nb + token_type_str__spaces_nb); 
#if 0 
  dputs(filedes, " [len =  "); 
  dput_spaces(filedes, token_len_str_len_spaces_nb); 
  dputs(filedes, token_len_str); 
  dputs(filedes, " ] : "); 
#endif 
  dputs(filedes, " : "); 
  dputs(filedes, token_srcval_cstr); 
  dput_spaces(filedes, token_srcval_cstr__spaces_nb); 
  dputs(filedes, " [ srcfile: "); 
  dput_spaces(filedes, token_srcfile_cstr_len_spaces_nb); 
  dputs(filedes, "<"); 
  dputs(filedes, token_srcfile_cstr); 
  dputs(filedes, ">@"); 
  dputs(filedes, token_offset0_cstr); 
  dput_spaces(filedes, token_offset0_cstr_len_spaces_nb); 
  dputs(filedes, " - line1: "); 
  dput_spaces(filedes, token_line1_cstr_len_spaces_nb); 
  dputs(filedes, token_line1_cstr); 
  dputs(filedes, " - column0: "); 
  dput_spaces(filedes, token_column0_cstr_len_spaces_nb); 
  dputs(filedes, token_column0_cstr); 
  dputs(filedes, " ] "); 
#if 0
  const char * str = cstring__concat__zarray__stack(((const char *[]) {
     "" , ": ", 
	decimal_token__get_srcval_cstr(this, token_i), 
	NULL})); 
  dputs(filedes, str); 
#endif 
}; 

static void decimal_token__print_stats__base(const int filedes, const decimal_token_env_t * this, const int base) {
  //const int filedes = fileno(yydecimalout); 
  dputs(filedes, "TOKEN_STACK("); 
  dputn(filedes, this -> nb); 
  dputs(filedes, " / "); 
  dputn(filedes, base); 
  dputs(filedes, " = "); 
  dputn(filedes, (int) (((double) (100 * this -> nb)) / ((double) base))); 
  dputs(filedes, "% ) \n"); 
}; 

void decimal_token__print_stats(const int filedes, const decimal_token_env_t * this) {
  decimal_token__print_stats__base(filedes, this, DECIMAL_TOKEN__SIZE); 
}; 

void decimal_token__print_nb_tokens(const int filedes, const decimal_token_env_t * this, const int token_nb) {
  //const int filedes = fileno(yydecimalout); 
  dputs(filedes, "TOKEN_STACK("); 
  dputn(filedes, this -> nb); 
  dputs(filedes, " / "); 
  dputn(filedes, DECIMAL_TOKEN__SIZE); 
  dputs(filedes, " = "); 
  dputn(filedes, (int) (((double) (100 * this -> nb)) / ((double) DECIMAL_TOKEN__SIZE))); 
  dputs(filedes, "% ) = { \n"); 
  const int nb = MIN(this -> nb,token_nb); 
  for (int i = 0; i < nb; i++) {
    dputs(filedes, "  "); 
    decimal_token__print_one_token(filedes, this, i);
    dputs(filedes, "\n"); 
  }; 
  dputs(filedes, "} \n"); 
}; 
 
void decimal_token__print_all_tokens(const int filedes, const decimal_token_env_t * this) {
  decimal_token__print_nb_tokens(filedes, this, this -> nb); 
}; 
 


// *** RAW DUMP & RESTORE *** 

#if 0 
struct decimal_token_env_t { 
  int16_t        srcval [DECIMAL_TOKEN__SIZE]; 
  int8_t         type   [DECIMAL_TOKEN__SIZE]; 
  int16_t        srcfile[DECIMAL_TOKEN__SIZE]; 
  int32_t        offset0[DECIMAL_TOKEN__SIZE]; 
  int24_packed_t line1  [DECIMAL_TOKEN__SIZE]; 
  int16_t        column0[DECIMAL_TOKEN__SIZE]; 
  int16_t        nb; 
}; 
#endif 

#ifdef ENDIAN_BIG 
#error 
#else 
#define BUFFER_WRITE(type_t,a) { *((type_t *)p) = (a); p += sizeof(type_t); } 
//#define BUFFER_READ(type_t,a) { a = *((type_t *)p); p += sizeof(type_t); } 
#define BUFFER_READ(type_t,a) a = *((type_t *)p); p += sizeof(type_t); 
#endif 
#define WRITE_ARRAY(a,s) { const int s_ = (s); written_chars_count += write(filedes, (a), (s_)); should_have_written_chars_count += s_; }
#define READ_ARRAY(a,s)  { const int s_ = (s);    read_chars_count += read (filedes, (a), (s_)); should_have_read_chars_count    += s_; }


enum { decimal_token__dump_raw__buffer_size = 63 }; 
int decimal_token__dump_raw(const int filedes, const decimal_token_env_t * this) { 
  int written_chars_count = 0; 
  int should_have_written_chars_count = 0; 
  char buffer[decimal_token__dump_raw__buffer_size]; 
  char * p = buffer; 
  BUFFER_WRITE(int8_t,sizeof(this ->  srcval[0])); 
  BUFFER_WRITE(int8_t,sizeof(this ->    type[0])); 
  BUFFER_WRITE(int8_t,sizeof(this -> srcfile[0])); 
  BUFFER_WRITE(int8_t,sizeof(this -> offset0[0])); 
  BUFFER_WRITE(int8_t,sizeof(this ->   line1[0])); 
  BUFFER_WRITE(int8_t,sizeof(this -> column0[0])); 
  BUFFER_WRITE(int8_t,sizeof(this ->      nb   )); 
  BUFFER_WRITE(int16_t,this -> nb); 
  written_chars_count += write(filedes, buffer, p - buffer); should_have_written_chars_count += (p - buffer); 
  WRITE_ARRAY(this -> srcval,  (this -> nb) * sizeof(this ->  srcval[0])); 
  WRITE_ARRAY(this -> type,    (this -> nb) * sizeof(this ->    type[0])); 
  WRITE_ARRAY(this -> srcfile, (this -> nb) * sizeof(this -> srcfile[0])); 
  WRITE_ARRAY(this -> offset0, (this -> nb) * sizeof(this -> offset0[0])); 
  WRITE_ARRAY(this -> line1,   (this -> nb) * sizeof(this ->   line1[0])); 
  WRITE_ARRAY(this -> column0, (this -> nb) * sizeof(this -> column0[0])); 
  if (written_chars_count == should_have_written_chars_count) { return written_chars_count; } 
  return INT_MIN & written_chars_count; 
}; 

//#define return assert(false); 
int decimal_token__restore_raw(const int filedes, decimal_token_env_t * this) { 
  if (this -> nb > 0) { return INT_MIN; }; 
  char buffer[decimal_token__dump_raw__buffer_size]; 
  char * p = buffer; 
  int read_chars_count = 0; 
  int should_have_read_chars_count = 0; 
  READ_ARRAY(buffer, 9); 
  //dputs_array(stderr, __func__, ": ", "read_chars_count: ", int_string__stack(read_chars_count), "\n"); 
#if 0 
  const int8_t int_srcval_sizeof  = buffer[0]; 
  const int8_t int_type_sizeof    = buffer[1]; 
  const int8_t int_srcfile_sizeof = buffer[2]; 
  const int8_t int_offset0_sizeof = buffer[3]; 
  const int8_t int_line1_sizeof   = buffer[4]; 
  const int8_t int_column0_sizeof = buffer[5]; 
  const int8_t int_nb_sizeof      = buffer[6]; 
#endif 
  const int8_t BUFFER_READ(int8_t, int_srcval_sizeof ); 
  const int8_t BUFFER_READ(int8_t, int_type_sizeof   ); 
  const int8_t BUFFER_READ(int8_t, int_srcfile_sizeof); 
  const int8_t BUFFER_READ(int8_t, int_offset0_sizeof); 
  const int8_t BUFFER_READ(int8_t, int_line1_sizeof  ); 
  const int8_t BUFFER_READ(int8_t, int_column0_sizeof); 
  const int8_t BUFFER_READ(int8_t, int_nb_sizeof     ); 
  if (int_srcval_sizeof  != sizeof(this ->  srcval[0])) { return INT_MIN | read_chars_count; }; 
  if (int_type_sizeof    != sizeof(this ->    type[0])) { return INT_MIN | read_chars_count; }; 
  if (int_srcfile_sizeof != sizeof(this -> srcfile[0])) { return INT_MIN | read_chars_count; }; 
  if (int_offset0_sizeof != sizeof(this -> offset0[0])) { return INT_MIN | read_chars_count; }; 
  if (int_line1_sizeof   != sizeof(this ->   line1[0])) { return INT_MIN | read_chars_count; }; 
  if (int_column0_sizeof != sizeof(this -> column0[0])) { return INT_MIN | read_chars_count; }; 
  if (int_nb_sizeof      != sizeof(this ->      nb   )) { return INT_MIN | read_chars_count; }; 
  BUFFER_READ(int16_t,this -> nb); 
  READ_ARRAY(this -> srcval,  (this -> nb) * sizeof(this ->  srcval[0])); 
  READ_ARRAY(this -> type,    (this -> nb) * sizeof(this ->    type[0])); 
  READ_ARRAY(this -> srcfile, (this -> nb) * sizeof(this -> srcfile[0])); 
  READ_ARRAY(this -> offset0, (this -> nb) * sizeof(this -> offset0[0])); 
  READ_ARRAY(this -> line1,   (this -> nb) * sizeof(this ->   line1[0])); 
  READ_ARRAY(this -> column0, (this -> nb) * sizeof(this -> column0[0])); 
  if (read_chars_count == should_have_read_chars_count) { return read_chars_count; } 
  return INT_MIN | read_chars_count; 
  return 0; 
}; 



