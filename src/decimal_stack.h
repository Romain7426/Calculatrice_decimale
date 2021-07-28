#ifndef DECIMAL_STACK_H
#define DECIMAL_STACK_H

#ifndef DECIMAL_STACK_T 
#define DECIMAL_STACK_T
struct decimal_stack_t; 
typedef struct decimal_stack_t decimal_stack_t; 
#endif /* DECIMAL_STACK_T */


struct decimal_stack_t { 
  uint8_t malloced_flag; // 0 if not, 1 if yes. 
  uint16_t bytesize; 
  
#if 0 
  int stdlog_d; // Foreign — we don't own it; valid only if 'stdlog_d > 0' 
  
  int_decimal_error_t error_id; 
  char                error_str[DECIMAL_STACK__ERROR_BUFFER_SIZE]; 
  uint16_t            error_buffer_size; 
#endif 
  
  uint8_t size; 
  uint8_t nb; 
  decimal_t array[1]; 
}; 


enum { DECIMAL_STACK__SIZEOF = sizeof(decimal_stack_t) }; 
extern const int32_t decimal_stack__sizeof__compiled_value; 

extern decimal_stack_t * decimal_stack__make_m (const uint8_t stack_size); 
extern decimal_stack_t * decimal_stack__make_r (decimal_stack_t * this, const uint8_t stack_size); 
extern decimal_stack_t * decimal_stack__make_b (const uint16_t buffer_size, uint8_t * buffer, uint16_t * buffer_size_used_r, const uint8_t stack_size); 
extern decimal_stack_t * decimal_stack__make_b2(const uint16_t buffer_size, uint8_t * buffer, uint16_t * buffer_size_used_r); 
extern void              decimal_stack__delete  (decimal_stack_t * this); 
extern void              decimal_stack__delete_r(decimal_stack_t * this); 
extern decimal_stack_t * decimal_stack__bzero(decimal_stack_t * this); 
extern decimal_stack_t * decimal_stack__reset(decimal_stack_t * this); 

extern uint16_t          decimal_stack__get_bytesize(const decimal_stack_t * this); 

extern decimal_t       *   decimal_stack__push(decimal_stack_t * this); 
extern int_decimal_error_t decimal_stack__pop (decimal_stack_t * this); 
extern decimal_t       *   decimal_stack__top (decimal_stack_t * this); 

#endif /* DECIMAL_STACK_H */ 

