#include "decimal_global.h"
#include "decimal.h" 
#include "decimal_stack.h" 

const int32_t decimal_stack__sizeof__compiled_value = DECIMAL_STACK__SIZEOF; 

decimal_stack_t * decimal_stack__make_m(const uint8_t stack_size) { 
  decimal_stack_t * this; 
  const uint16_t requested_bytesize = DECIMAL_STACK__SIZEOF + ((stack_size - 1) * sizeof(decimal_t)); 
  this = (decimal_stack_t *) malloc(requested_bytesize); 
  if (this == NULL) return NULL; 
  bzero(this, requested_bytesize); 
  this -> malloced_flag = 1; 
  this -> bytesize = requested_bytesize; 
  this -> size = stack_size; 
  this -> nb = 0; 
  return this; 
}; 

decimal_stack_t * decimal_stack__make_r(decimal_stack_t * this, const uint8_t stack_size) { 
 return NULL; 
}; 

decimal_stack_t * decimal_stack__make_b(const uint16_t buffer_size, uint8_t * buffer, uint16_t * buffer_size_used_r, const uint8_t stack_size) { 
  const uint16_t requested_bytesize = DECIMAL_STACK__SIZEOF + ((stack_size - 1) * sizeof(decimal_t)); 
  if (requested_bytesize > buffer_size) return NULL; 
  if (buffer_size_used_r != NULL) { *buffer_size_used_r = requested_bytesize; }; 
  decimal_stack_t * this = (decimal_stack_t *) buffer; 
  //decimal_stack__make_r(this, stack_size); 
  bzero(this, requested_bytesize); 
  this -> malloced_flag = 0; 
  this -> bytesize = requested_bytesize; 
  this -> size = stack_size; 
  this -> nb = 0; 
  return this; 
}; 

decimal_stack_t * decimal_stack__make_b2(const uint16_t buffer_size, uint8_t * buffer, uint16_t * buffer_size_used_r) { 
  const uint16_t min_bytesize = DECIMAL_STACK__SIZEOF - sizeof(decimal_t); 
  if (min_bytesize > buffer_size) return NULL; 
  const uint8_t stack_size = (buffer_size - min_bytesize) / sizeof(decimal_t); 
  return decimal_stack__make_b(buffer_size, buffer, buffer_size_used_r, stack_size); 
}; 

void decimal_stack__delete(decimal_stack_t * this) { 
  const uint8_t malloced_flag = this -> malloced_flag; 
  decimal_stack__delete_r(this); 
  if (1 == malloced_flag) free(this); 
}; 

void decimal_stack__delete_r(decimal_stack_t * this) { 
  bzero(this, this -> bytesize); 
}; 

decimal_stack_t * decimal_stack__bzero(decimal_stack_t * this) { 
  const uint8_t malloced_flag = this -> malloced_flag; 
  const uint16_t bytesize = this -> bytesize; 
  const uint8_t stack_size = this -> size; 
  bzero(this, bytesize); 
  this -> size = stack_size; 
  this -> bytesize = bytesize; 
  this -> malloced_flag = malloced_flag; 
  return this; 
}; 

decimal_stack_t * decimal_stack__reset(decimal_stack_t * this) { 
  decimal_stack__bzero(this); 
  return this; 
}; 

uint16_t decimal_stack__get_bytesize(const decimal_stack_t * this) { 
 return this -> bytesize; 
}; 



// *********************** STACK *********************** 


decimal_t * decimal_stack__push(decimal_stack_t * this) { 
  if (this -> nb >= this -> size) return NULL; 
  decimal_t * top = this -> array + this -> nb; 
  this -> nb++; 
  return top; 
}; 

int_decimal_error_t decimal_stack__pop(decimal_stack_t * this) { 
  if (this -> nb <= 0) return DECIMAL__STACK__EMPTY; 
  this -> nb--; 
  return DECIMAL__OK; 
}; 

decimal_t * decimal_stack__top(decimal_stack_t * this) { 
  if (this -> nb <= 0) return NULL; 
  decimal_t * top = this -> array + this -> nb - 1; 
  return top;   
}; 

