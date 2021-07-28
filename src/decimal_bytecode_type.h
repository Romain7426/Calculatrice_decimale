#ifndef DECIMAL_BYTECODE_TYPE_H
#define DECIMAL_BYTECODE_TYPE_H

#define DECIMAL_BYTECODE_TYPE__LIST					\
  X(DECIMAL__BYTECODE__NULL, = 0)					\
    X(DECIMAL__BYTECODE__HALT, )					\
    X(DECIMAL__BYTECODE__NOP, )						\
    X(DECIMAL__BYTECODE__PUSH_ZERO, )					\
    X(DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__INT, )			\
    X(DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__FLOAT_V, )		\
    X(DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__FLOAT_D, )		\
    X(DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__FLOAT_E, )		\
    X(DECIMAL__BYTECODE__INC, )						\
    X(DECIMAL__BYTECODE__DEC, )						\
    X(DECIMAL__BYTECODE__NEG, )						\
    X(DECIMAL__BYTECODE__ADD, )						\
    X(DECIMAL__BYTECODE__SUB, )						\
    X(DECIMAL__BYTECODE__MULT, )					\
    X(DECIMAL__BYTECODE__DIV, )						

#define X(ident, value) ident value, 
enum { 
  DECIMAL_BYTECODE_TYPE__LIST
}; 
#undef X 

#define X(ident, value) ident##___ID, 
enum { 
  DECIMAL_BYTECODE_TYPE__LIST
  DECIMAL_BYTECODE_TYPE__COUNT
}; 
#undef X 

typedef      uint8_t                      int_decimal_bytecode_type_t; 
extern const char *                       int_decimal_bytecode_type__get_cstr(const int_decimal_bytecode_type_t bytecode_type); 
extern const char *                       int_decimal_bytecode_type__id_cstr [DECIMAL_BYTECODE_TYPE__COUNT + 1]; // "+1" for the ending NULL pointer. 
enum {                                    int_decimal_bytecode_type__id_cstr__size = ARRAY_SIZE(int_decimal_bytecode_type__id_cstr) }; 
extern const uint8_t                      int_decimal_bytecode_type__id_cstr__size__compiled_value; 
extern const  int_decimal_bytecode_type_t int_decimal_bytecode_type__id_value[DECIMAL_BYTECODE_TYPE__COUNT]; 
enum {                                    int_decimal_bytecode_type__id_value__size = ARRAY_SIZE(int_decimal_bytecode_type__id_value) }; 
extern const uint8_t                      int_decimal_bytecode_type__id_value__size__compiled_value; 


#define X(ident, value) extern const int_decimal_bytecode_type_t ident##__compiled_value; 
DECIMAL_BYTECODE_TYPE__LIST 
#undef X 


static void int_decimal_bytecode_type__check_and_assert(void) { 
  assert(DECIMAL_BYTECODE_TYPE__COUNT <= UINT8_MAX); 
#define X(ident, value) assert(ident == ident##__compiled_value); 
DECIMAL_BYTECODE_TYPE__LIST 
#undef X 
  assert(int_decimal_bytecode_type__id_cstr__size  == int_decimal_bytecode_type__id_cstr__size__compiled_value ); 
  assert(int_decimal_bytecode_type__id_value__size == int_decimal_bytecode_type__id_value__size__compiled_value); 
}; 





#endif /* DECIMAL_BYTECODE_TYPE_H */
