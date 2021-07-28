#include "decimal_global.h"
#include "decimal.h" 
#include "decimal_bytecode_type.h" 


#define X(ident, value) const int_decimal_bytecode_type_t ident##__compiled_value = ident; 
DECIMAL_BYTECODE_TYPE__LIST 
#undef X 


#define X(ident, value) #ident, 
const char * int_decimal_bytecode_type__id_cstr[DECIMAL_BYTECODE_TYPE__COUNT + 1] = { 
DECIMAL_BYTECODE_TYPE__LIST 
  NULL
}; 
#undef X 
 

const uint8_t int_decimal_bytecode_type__id_cstr__size__compiled_value = ARRAY_SIZE(int_decimal_bytecode_type__id_cstr); 


#define X(ident, value) ident, 
const int_decimal_bytecode_type_t int_decimal_bytecode_type__id_value[DECIMAL_BYTECODE_TYPE__COUNT] = { 
DECIMAL_BYTECODE_TYPE__LIST 
}; 
#undef X 


const uint8_t int_decimal_bytecode_type__id_value__size__compiled_value = ARRAY_SIZE(int_decimal_bytecode_type__id_value); 


const char * int_decimal_bytecode_type__get_cstr(const int_decimal_bytecode_type_t bytecode_type) { 
  const char * bytecode_type__cstr = NULL; 
  switch (bytecode_type) { 
#define X(ident, value) case ident: bytecode_type__cstr = #ident; break; 
  DECIMAL_BYTECODE_TYPE__LIST
#undef X 
  }; 
  return bytecode_type__cstr; 
}; 



