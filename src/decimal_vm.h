#ifndef DECIMAL_VM_H
#define DECIMAL_VM_H

// *********************** VM ENV *********************** 

#ifndef DECIMAL_VM_ENV_T 
#define DECIMAL_VM_ENV_T 
struct         decimal_vm_env_t; 
typedef struct decimal_vm_env_t   decimal_vm_env_t; 
#endif 

enum { DECIMAL_VM_ENV__SIZEOF = /*sizeof(decimal_vm_env_t)*/(1 << 13) }; // Might be greater than 'sizeof(decimal_vm_env_t)'. 

extern  const  size_t             decimal_vm_env__sizeof; 
extern         decimal_vm_env_t * decimal_vm_env__make    (const int stdlog_d); 
extern         decimal_vm_env_t * decimal_vm_env__make_b  (const uint16_t buffer_size, uint8_t * buffer, uint16_t * buffer_size_used_r, const int stdlog_d); 
extern         decimal_vm_env_t * decimal_vm_env__make_r  (decimal_vm_env_t * this, const int stdlog_d); 
extern         decimal_vm_env_t * decimal_vm_env__bzero   (decimal_vm_env_t * this); 
extern         decimal_vm_env_t * decimal_vm_env__reset0  (decimal_vm_env_t * this); 
extern         decimal_vm_env_t * decimal_vm_env__reset   (decimal_vm_env_t * this, decimal_env_t * decimal_env, decimal_stack_t * stack, uint8_t * bytecode_data, const uint16_t bytecode_size, const uint16_t bytecode_start, const char * const_string_array, const uint16_t const_string_sizeof); 

extern         void                  decimal_vm_env__delete  (decimal_vm_env_t * this); 
extern         void                  decimal_vm_env__delete_r(decimal_vm_env_t * this); 
extern  const  char                * decimal_vm_env__strcopy (decimal_vm_env_t * this, const char * cstr); 

extern         int                   decimal_vm_env__get_stdlog   (const decimal_vm_env_t * this); 
extern         int_decimal_error_t   decimal_vm_env__get_error_id (const decimal_vm_env_t * this); 
extern  const  char                * decimal_vm_env__get_error_str(const decimal_vm_env_t * this); 

static void decimal_vm_env__check_and_assert(void) { 
  assert(DECIMAL_VM_ENV__SIZEOF >= decimal_vm_env__sizeof); 
}; 


// *********************** VM *********************** 

extern         int_decimal_error_t   decimal_vm__step      (decimal_vm_env_t * this); 
extern         int_decimal_error_t   decimal_vm__run       (decimal_vm_env_t * this); 
extern         int                   decimal_vm__halted_huh(const decimal_vm_env_t * this); 



#endif /* DECIMAL_VM_H */
