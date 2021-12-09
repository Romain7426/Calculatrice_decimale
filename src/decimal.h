#ifndef DECIMAL_H
#define DECIMAL_H

#define DECIMAL_VERSION__LIST		\
  X(DECIMAL_VERSION_MAJOR, = 3)		\
  X(DECIMAL_VERSION_MINOR, = 2)		\
  X(DECIMAL_VERSION_REVISION, = 0) 

#define X(ident, value) ident value, 
enum { 
  DECIMAL_VERSION__LIST 
}; 
#undef X 

#define X(ident, value) extern const uint8_t ident##__compiled_value; 
DECIMAL_VERSION__LIST 
#undef X 

static void decimal_version__check_and_assert(void) { 
#define X(ident, value) assert(ident == ident##__compiled_value); 
DECIMAL_VERSION__LIST 
#undef X 
}; 

extern const char       decimal_version[]; 
extern const uint16_t   decimal_version__strlen; 
extern const char     * decimal_version__get(void); 
extern void             decimal_version__print(const int stduser_d); 

extern const char       decimal_url[]; 
extern const uint16_t   decimal_url__strlen; 
extern const char     * decimal_url__get(void); 
extern void             decimal_url__print(const int stduser_d); 

extern const char       decimal_copyright[]; 
extern const uint16_t   decimal_copyright__strlen; 
extern const char     * decimal_copyright__get(void); 
extern void             decimal_copyright__print(const int stduser_d); 

extern const char       decimal_example[]; 
extern const uint16_t   decimal_example__strlen; 
extern const char     * decimal_example__get(void); 
extern void             decimal_example__print(const int stduser_d); 


// *** ERROR CODES & RETURN VALUES *** 
// See «man 2 wait» & «man 3 exit». 
// The exit value is gotten by the parent using the macro WEXITSTATUS(…), 
// which returns the lower 8 bits of the exit status. All other bits are 
// used as status information on the process. 
// The WEXITSTATUS(…) value is gotten from the lower 8 bits of the exit 
// call. 
// The system, the environment, can interpret the WEXITSTATUS(…) 8-bit value as 
// signed or unsigned — that depends. Thus: 
//  - Only the 0-127 range is sure. 
//  - The 128-255 range (the -128_-1 range) could be interpreted as positive or negative. 
// However, in the program, the sign interpretation of these values depends only 
// on the type declaration, «int8_t error_id» or «uint8_t error_id» — so they are safe. 


#define DECIMAL_ERROR__LIST			\
  X(DECIMAL__OK, = 0)				\
  /* Unspecified */				\
  X(DECIMAL__ERROR_GENERIC, = INT8_MIN)	\
  /* Errors */			\
  X(DECIMAL__STRCOPY, = INT8_MIN + 1) \
  X(DECIMAL__MAIN_ERROR_ID_NOT_ASSIGNED, ) \
  X(DECIMAL__STDERR_IS_NOT_A_TTY, ) \
  X(DECIMAL__STDOUT_IS_NOT_A_TTY, ) \
  X(DECIMAL__STDIN_IS_NOT_A_TTY, ) \
  X(DECIMAL__REPL_EXTRA_ARGS, ) \
  X(DECIMAL__REPL_ERROR_WHILE_READING, ) \
  X(DECIMAL__STDUSER_NOT_POS, ) \
  X(DECIMAL__MAKE_B_BUFFER_SIZE_TOO_SMALL, ) \
  X(DECIMAL__MAKE_B_BUFFER_IS_NULL, ) \
  X(DECIMAL__STATUS_NOT_LISTED_IN_SWITCH, ) \
  X(DECIMAL__NULL_CSTR, ) \
  X(DECIMAL__EMPTY_CSTR, ) \
  X(DECIMAL__ONLY_WHITE_SPACES_CSTR, ) \
  X(DECIMAL__ONLY_NEG_SIGN_CSTR, ) \
  X(DECIMAL__UNEXPECTED_DIGIT, ) \
  X(DECIMAL__DIGITS_LEN_IS_NULL, ) \
  X(DECIMAL__FIRST_DIGIT_IS_NULL, ) \
  X(DECIMAL__NULL_BASE_CSTR, ) \
  X(DECIMAL__NULL_NEW_D_STATUS_R, ) \
  X(DECIMAL__MALFORMED_NUMBER, ) \
  X(DECIMAL__NUMBER_WAS_EMPTY, ) \
  X(DECIMAL__D_LEN_WAS_ZERO, ) \
  X(DECIMAL__D_LAMBDA_WAS_ZERO, ) \
  X(DECIMAL__INTERNAL_ERROR, ) \
  X(DECIMAL__FD_NEG, ) \
  X(DECIMAL__FDOPEN, ) \
  X(DECIMAL__NULL_FIELD_NAME, ) \
  X(DECIMAL__UNKNOWN_FIELD, ) \
  X(DECIMAL__INDEX_OF_OUT_BOUNDS, ) \
  X(DECIMAL__NULL_ERROR_ID_R, ) \
  X(DECIMAL__ERROR_SIZE_LOWER_THAN_1, ) \
  X(DECIMAL__NULL_INPUT_ENV, ) \
  X(DECIMAL__NULL_TOKEN_ENV, ) \
  X(DECIMAL__TOKEN_PARSER__ERROR_WHILE_READING_THE_INPUT_STREAM, ) \
  X(DECIMAL__TOKEN_PARSER__TOKEN_MATCHES_NO_PATTERN, ) \
  X(DECIMAL__TOKEN_PARSER__ERROR_TOKEN, ) \
  X(DECIMAL__TOKEN_PARSER__STACK_OVERFLOW, ) \
  X(DECIMAL__DATA_GENERATION__NULL_SYNTAX_FILTERING, ) \
  X(DECIMAL__DATA_GENERATION__NULL_TOKEN_ENV, ) \
  X(DECIMAL__DATA_GENERATION__NULL_DIRECTIVE_OR_EXPR_HUH_R, ) \
  X(DECIMAL__DATA_GENERATION__NULL_BYTECODE_DATA, ) \
  X(DECIMAL__DATA_GENERATION__NULL_BYTECODE_LEN_R, ) \
  X(DECIMAL__DATA_GENERATION__NULL_CONST_STRING_ARRAY, ) \
  X(DECIMAL__DATA_GENERATION__NULL_CONST_STRING_LEN_R, ) \
  X(DECIMAL__DATA_GENERATION__ERROR_ID_NOT_ASSIGNED, ) \
  X(DECIMAL__DATA_GENERATION__NULL_FLOATVAL_R, ) \
  X(DECIMAL__DATA_GENERATION__NULL_INTVAL_R, ) \
  X(DECIMAL__DATA_GENERATION__NULL_ERROR_ID_R, ) \
  X(DECIMAL__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1, ) \
  X(DECIMAL__DATA_GENERATION__NOT_ENOUGH_TOKENS, ) \
  X(DECIMAL__DATA_GENERATION__TOO_MANY_TOKENS, ) \
  X(DECIMAL__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE, ) \
  X(DECIMAL__DATA_GENERATION__NON_MATCHING_TOKEN_VALUE, ) \
  X(DECIMAL__DATA_GENERATION__NULL_TREE_ENV, ) \
  X(DECIMAL__DATA_GENERATION__TREE_ENV__EMPTY, ) \
  X(DECIMAL__DATA_GENERATION__TREE_ENV__BEING_FILLED, ) \
  X(DECIMAL__DATA_GENERATION__TREE_ENV__NOT_FILLED, ) \
  X(DECIMAL__DATA_GENERATION__NOT_ENOUGH_TREES, ) \
  X(DECIMAL__DATA_GENERATION__TREE__WRONG_TREE_TYPE, ) \
  X(DECIMAL__DATA_GENERATION__MISSING_PHYSIQUE_SECTION, ) \
  X(DECIMAL__DATA_GENERATION__MISSING_GAMEPLAY_SECTION, ) \
  X(DECIMAL__DATA_GENERATION__MISSING_GRAPHIQUE_SECTION, ) \
  X(DECIMAL__DATA_GENERATION__STACK_OVERFLOW, ) \
  X(DECIMAL__DATA_GENERATION__STACK_UNDERFLOW, ) \
  X(DECIMAL__DATA_GENERATION__STACK_UNEXPECTED_TOKEN, ) \
  X(DECIMAL__DATA_GENERATION__STACK_TOO_MANY_ITEMS, ) \
  X(DECIMAL__DATA_GENERATION__STACK_NOT_ENOUGH_ITEMS, ) \
  X(DECIMAL__DATA_GENERATION__MEMBRES_OVERFLOW, ) \
  X(DECIMAL__DATA_GENERATION__RACINES_OVERFLOW, ) \
  X(DECIMAL__BYTECODE_GENERATION__NOT_ENOUGH_AVAILABLE_SPACE, ) \
  X(DECIMAL__STACK__EMPTY, ) \
  X(DECIMAL__VM__STRCOPY, ) \
  X(DECIMAL__VM__ERROR_ID_NOT_ASSIGNED, ) \
  X(DECIMAL__VM__PC_OUT_OF_BOUNDS, ) \
  X(DECIMAL__VM__STACK_OVERFLOW, ) \
  X(DECIMAL__VM__STACK_UNDERFLOW, ) \
  X(DECIMAL__VM__CONST_STRING_ARRAY_OUT_OF_BOUNDS, ) \
  X(DECIMAL__VM__NULL_BYTECODE, ) \
  X(DECIMAL__TREE__NO_SPACE_LEFT, ) \
  X(DECIMAL__TREE__WRONG_ADDRESS, ) \
  X(DECIMAL__SYNTAX_FILTERING__NULL_THIS, ) \
  X(DECIMAL__SYNTAX_FILTERING__NULL_TOKEN_ENV, ) \
  X(DECIMAL__SYNTAX_FILTERING__NULL_TOKEN_I, ) \
  X(DECIMAL__SYNTAX_FILTERING__OUTPUT_POSTFIX_BUFFER_TOO_SMALL, ) \
  X(DECIMAL__SYNTAX_FILTERING__PARENTHESIS_STACK_TOO_SMALL, ) \
  X(DECIMAL__SYNTAX_FILTERING__MISSING_CLOSING_PARENTHESIS, ) \
  X(DECIMAL__SYNTAX_FILTERING__MISSING_OPENING_PARENTHESIS, ) \
  X(DECIMAL__SYNTAX_FILTERING__MISMATCHING_PARENTHESIS, ) \
  X(DECIMAL__SYNTAX_FILTERING__NOT_AN_OPENING_PARENTHESIS, ) \
  X(DECIMAL__SYNTAX_FILTERING__NOT_AN_CLOSING_PARENTHESIS, ) \
  X(DECIMAL__SYNTAX_FILTERING__CANNOT_SKIP_TO_CLOSING_PARENTHESIS_IN_LALR_MODE, ) \
  X(DECIMAL__SYNTAX_FILTERING__CURRENT_TOKEN_OUT_OF_BOUND, ) \
  X(DECIMAL__SYNTAX_FILTERING__CURRENT_TOKEN_IS_INVALID, ) \
  X(DECIMAL__SYNTAX_FILTERING__CURRENT_TOKEN_IS_EOF, ) \
  X(DECIMAL__SYNTAX_FILTERING__LAST_TOKEN_SHOULD_BE_EOF, ) \
  X(DECIMAL__SYNTAX_FILTERING__LALR_MODE_ALREADY_SET, ) \
  X(DECIMAL__SYNTAX_FILTERING__UNEXPECTED_TOKEN, ) \
  X(DECIMAL__MAIN__OPTIONS__PARSING_ERROR, ) \
  X(DECIMAL__MAIN__OPTIONS__UNKNOWN, ) \
  X(DECIMAL__MAIN__OPTIONS__EXIT_QUICK, ) \
  X(DECIMAL__MAIN__CANNOT_OPEN_INPUT_FILE, ) \
  X(DECIMAL__TOKEN__PARSER__ERROR, ) \
  X(DECIMAL__TOKEN__INPUT__ERROR, ) \
  /* Warnings */ \
  X(DECIMAL__NULL_STRUCT, = 1) \
  X(DECIMAL__EMPTY_STRUCTURE, ) \
  X(DECIMAL__INTEGER_TOO_LARGE, ) \
  X(DECIMAL__FILLING_NOT_COMPLETED, ) \
  X(DECIMAL__HAS_BREAKING_UNCONSISTENCIES, ) \
  X(DECIMAL__HAS_NON_BREAKING_UNCONSISTENCIES, ) \
  X(DECIMAL__SYNTAX_FILTERING__TOKEN_ENV_HAS_ZERO_TOKEN, ) 

#define X(ident, value) ident value, 
enum { 
  DECIMAL_ERROR__LIST
}; 
#undef X 

#define X(ident, value) ident##___ID, 
enum { 
  DECIMAL_ERROR__LIST
  DECIMAL_ERROR__COUNT
}; 
#undef X 

typedef      int8_t               int_decimal_error_t;
extern const char *               int_decimal_error__get_cstr(const int_decimal_error_t error_id); 
extern const char *               int_decimal_error__id_cstr [DECIMAL_ERROR__COUNT + 1]; 
enum {                            int_decimal_error__id_cstr__size = ARRAY_SIZE(int_decimal_error__id_cstr) }; 
extern const uint8_t              int_decimal_error__id_cstr__size__compiled_value; 
extern const  int_decimal_error_t int_decimal_error__id_value[DECIMAL_ERROR__COUNT]; 
enum {                            int_decimal_error__id_value__size = ARRAY_SIZE(int_decimal_error__id_value) }; 
extern const uint8_t              int_decimal_error__id_value__size__compiled_value; 

#define X(ident, value) extern const int_decimal_error_t ident##__compiled_value; 
DECIMAL_ERROR__LIST 
#undef X 

static void int_decimal_error__check_and_assert(void) { 
  assert(DECIMAL_ERROR__COUNT <= UINT8_MAX); 
#define X(ident, value) assert(ident == ident##__compiled_value); 
DECIMAL_ERROR__LIST 
#undef X 
  assert(int_decimal_error__id_cstr__size  == int_decimal_error__id_cstr__size__compiled_value ); 
  assert(int_decimal_error__id_value__size == int_decimal_error__id_value__size__compiled_value); 
}; 



// *** DECIMAL_ENV_T *** 

#define DECIMAL_ENV_CONST__LIST				\
  X(DECIMAL_ENV__ERROR_BUFFER_SIZE, = (1 << 11))	\
  X(DECIMAL_ENV__STRING_STACK_SIZE, = (1 << 12))	\
  X(DECIMAL_ENV__SIZEOF, = (6184))		

#define X(ident, value) ident value, 
enum { 
  DECIMAL_ENV_CONST__LIST
}; 
#undef X 

#define X(ident, value) ident##___ID, 
enum { 
  DECIMAL_ENV_CONST__LIST
  DECIMAL_ENV_CONST__COUNT
}; 
#undef X 

#define X(ident, value) extern const uint16_t ident##__compiled_value; 
  DECIMAL_ENV_CONST__LIST
#undef X 

extern const uint16_t decimal_env__sizeof; 

static void decimal_env_const__check_and_assert(void) { 
#define X(ident, value) assert(ident == ident##__compiled_value); 
  DECIMAL_ENV_CONST__LIST
#undef X 
  assert(DECIMAL_ENV__ERROR_BUFFER_SIZE >= 3); 
  assert(DECIMAL_ENV__STRING_STACK_SIZE >= 3); 
  assert(DECIMAL_ENV__SIZEOF >= decimal_env__sizeof); 
}; 

struct decimal_env_t; 
typedef struct decimal_env_t decimal_env_t; 

extern decimal_env_t * decimal_env__make_m  (const int stdlog_d); 
extern decimal_env_t * decimal_env__make_r  (decimal_env_t * this, const int stdlog_d); 
extern decimal_env_t * decimal_env__make_b  (const int buffer_size, uint8_t * buffer, int * buffer_size_used_r, const int stdlog_d); 
extern void            decimal_env__delete  (decimal_env_t * this); 
extern void            decimal_env__delete_r(decimal_env_t * this); 
extern void            decimal_env__bzero   (decimal_env_t * this); 
extern const char *    decimal_env__strcopy (decimal_env_t * this, const char * cstr); 

extern void decimal_env__printing_int_and_float_separator_char__set(      decimal_env_t * this, const char separator); 
extern char decimal_env__printing_int_and_float_separator_char__get(const decimal_env_t * this); 



// *** DECIMAL_STATUS *** 

#define DECIMAL_STATUS__LIST		\
  X(DECIMAL_STATUS__INVALID, = UINT8_MAX)	\
  X(DECIMAL_STATUS__ZERO, = 0)		\
  X(DECIMAL_STATUS__INFINI, )		\
  X(DECIMAL_STATUS__POS, )		\
  X(DECIMAL_STATUS__NEG, )		\
  X(DECIMAL_STATUS__POS_INFINI, )	\
  X(DECIMAL_STATUS__NEG_INFINI, )	\
  X(DECIMAL_STATUS__POS_EPSILON, )	\
  X(DECIMAL_STATUS__NEG_EPSILON, )	\
  X(DECIMAL_STATUS__DEVELOPPEMENT_LIMITE_NECESSAIRE, ) 

#if 0 
  X(DECIMAL_STATUS__0_DIV_BY_0, )	\
  X(DECIMAL_STATUS__INF_DIV_BY_INF, )	\
  X(DECIMAL_STATUS__ZERO_BY_INF, )	\
  X(DECIMAL_STATUS__INF_BY_ZERO, )	
#endif 
    

#define X(ident, value) ident value, 
enum { 
  DECIMAL_STATUS__LIST 
}; 
#undef X 

#define X(ident, value) ident##___ID, 
enum { 
  DECIMAL_STATUS__LIST
  DECIMAL_STATUS__COUNT
}; 
#undef X 

#define X(ident, value) extern const uint8_t ident##__compiled_value; 
DECIMAL_STATUS__LIST 
#undef X 

extern const char *  decimal_status__id_cstr [DECIMAL_STATUS__COUNT + 1]; 
enum {               decimal_status__id_cstr__size = ARRAY_SIZE(decimal_status__id_cstr) }; 
extern const uint8_t decimal_status__id_cstr__size__compiled_value; 
extern const uint8_t decimal_status__id_value[DECIMAL_STATUS__COUNT]; 
enum {               decimal_status__id_value__size = ARRAY_SIZE(decimal_status__id_value) }; 
extern const uint8_t decimal_status__id_value__size__compiled_value; 

static void decimal_status__check_and_assert(void) { 
  assert(DECIMAL_STATUS__COUNT <= UINT8_MAX); 
#define X(ident, value) assert(ident == ident##__compiled_value); 
DECIMAL_STATUS__LIST 
#undef X 
  assert(decimal_status__id_cstr__size  == decimal_status__id_cstr__size__compiled_value ); 
  assert(decimal_status__id_value__size == decimal_status__id_value__size__compiled_value); 
}; 

extern const char *  decimal_status__cstr(const uint8_t status); 
extern       uint8_t decimal_status__id  (const uint8_t status); 
extern       int     decimal_status__value_is_a_status_huh(const uint8_t status); 



//* DECIMAL_T */

#if 0 
enum {  DECIMAL_SIZE             =                256 }; // TODO XXX FIXME: On a 8-bit compiler, that gonna fail. 
enum {  DECIMAL_FIXED_POINT_SIZE =                200 }; 
#else 
enum {  DECIMAL_SIZE             =                 32 }; // TODO XXX FIXME: On a 8-bit compiler, that gonna fail. 
enum {  DECIMAL_FIXED_POINT_SIZE =                 12 }; 
#endif 
#define DECIMAL_BASE_MACRO                         40 
enum {  DECIMAL_BASE             = DECIMAL_BASE_MACRO }; 
enum {  DECIMAL_BASE_MAX         =      UINT8_MAX - 1 }; 


#define DECIMAL_BASE_GENERIC__GET_QUOTIENT(__dividend__)  ((__dividend__) / DECIMAL_BASE) 
#define DECIMAL_BASE_GENERIC__GET_REMAINDER(__dividend__) ((__dividend__) % DECIMAL_BASE) 

#define DECIMAL_BASE_100__GET_QUOTIENT(__dividend__)  ((__dividend__) / DECIMAL_BASE) 
#define DECIMAL_BASE_100__GET_REMAINDER(__dividend__) ((__dividend__) % DECIMAL_BASE) 
  
#define DECIMAL_BASE_2__GET_QUOTIENT(__dividend__)  ((__dividend__) >> 1) 
#define DECIMAL_BASE_2__GET_REMAINDER(__dividend__) ((__dividend__) & 1) 
  
#if   (DECIMAL_BASE_MACRO == 100) 
#define DECIMAL_BASE__GET_QUOTIENT  DECIMAL_BASE_100__GET_QUOTIENT
#define DECIMAL_BASE__GET_REMAINDER DECIMAL_BASE_100__GET_REMAINDER 
#elif (DECIMAL_BASE_MACRO ==   2) 
#define DECIMAL_BASE__GET_QUOTIENT  DECIMAL_BASE_2__GET_QUOTIENT
#define DECIMAL_BASE__GET_REMAINDER DECIMAL_BASE_2__GET_REMAINDER 
#else 
#define DECIMAL_BASE__GET_QUOTIENT  DECIMAL_BASE_GENERIC__GET_QUOTIENT
#define DECIMAL_BASE__GET_REMAINDER DECIMAL_BASE_GENERIC__GET_REMAINDER 
#endif 

extern const uint16_t DECIMAL_SIZE__compiled_value; // TODO FIXME XXX: 16-bit value. 
extern const uint8_t  DECIMAL_FIXED_POINT_SIZE__compiled_value; 
extern const uint8_t  DECIMAL_BASE__compiled_value; 

static void decimal_struct__check_and_assert(void) { 
  assert(DECIMAL_SIZE <= UINT8_MAX + 1); 
  assert(DECIMAL_FIXED_POINT_SIZE < DECIMAL_SIZE); // Meaning that «DECIMAL_INT_INDEX» is «> 0». 
  assert(DECIMAL_BASE < UINT8_MAX); 
  assert(DECIMAL_BASE_MAX < UINT8_MAX); 
  
  assert(DECIMAL_SIZE > 0); 
  assert(DECIMAL_FIXED_POINT_SIZE > 0); 
  assert(DECIMAL_BASE > 1); 
  
  assert(DECIMAL_SIZE             == DECIMAL_SIZE__compiled_value            ); 
  assert(DECIMAL_FIXED_POINT_SIZE == DECIMAL_FIXED_POINT_SIZE__compiled_value); 
  assert(DECIMAL_BASE             == DECIMAL_BASE__compiled_value            ); 
}; 

typedef unsigned char decimal_t[DECIMAL_SIZE]; 


enum { DECIMAL__EXPRESSION_NESTEDNESS_MAX = 16 }; // The stack has to be allocated beforehand. 
extern const uint8_t DECIMAL__EXPRESSION_NESTEDNESS_MAX__compiled_value; 

// Buffer has to be allocated. 
enum { DECIMAL__LONGEST_INFIX_EXPRESSION = 64 }; // 2^6 = 64 — therefore, it means roughly a six-height tree (on average). 
extern const uint8_t DECIMAL__LONGEST_INFIX_EXPRESSION__compiled_value; 



static void decimal_expr__check_and_assert(void) { 
  assert(DECIMAL__EXPRESSION_NESTEDNESS_MAX == DECIMAL__EXPRESSION_NESTEDNESS_MAX__compiled_value); 
  assert(DECIMAL__LONGEST_INFIX_EXPRESSION  == DECIMAL__LONGEST_INFIX_EXPRESSION__compiled_value ); 
}; 





static void decimal__check_and_assert(void) { 
  decimal_version__check_and_assert(); 
  int_decimal_error__check_and_assert(); 
  decimal_env_const__check_and_assert(); 
  decimal_struct__check_and_assert(); 
  decimal_status__check_and_assert(); 
  decimal_expr__check_and_assert(); 
}; 


#define RETURN_ERROR 1

#ifdef RETURN_ERROR 
#  define RETURN_TYPE_T int_decimal_error_t 
#else 
#  define RETURN_TYPE_T decimal_t * 
#endif 

//extern RETURN_TYPE_T decimal__make_m          (decimal_env_t * this, decimal_t * d_r); // RL: Memory should not be handled here. 
//extern RETURN_TYPE_T decimal__make_r          (decimal_env_t * this, decimal_t * d_r); // RL: Please use 'reset'. 
extern RETURN_TYPE_T decimal__make_b          (decimal_env_t * this, const int buffer_size, uint8_t * buffer, int * buffer_size_used_r); 

extern RETURN_TYPE_T decimal__reset_r         (const decimal_env_t * this, decimal_t * d_r); 

extern RETURN_TYPE_T decimal__zero_r            (const decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__max_value_r       (const decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__min_value_r       (const decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__pos_epsilon_r     (const decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__neg_epsilon_r     (const decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__pos_infini_r      (const decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__neg_infini_r      (const decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__invalid_r         (const decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__cast_from_int_r    (      decimal_env_t * this, decimal_t * d_r, const int           int_given); 
extern RETURN_TYPE_T decimal__cast_from_uint_r   (      decimal_env_t * this, decimal_t * d_r, const uint         uint_given); 
extern RETURN_TYPE_T decimal__cast_from_uint8_r  (      decimal_env_t * this, decimal_t * d_r, const uint8_t     uint8_given); 
extern RETURN_TYPE_T decimal__cast_from_uint16_r (      decimal_env_t * this, decimal_t * d_r, const uint16_t   uint16_given); 
extern RETURN_TYPE_T decimal__cast_from_uint32_r (      decimal_env_t * this, decimal_t * d_r, const uint32_t   uint32_given); 
extern RETURN_TYPE_T decimal__cast_from_uint64_r (      decimal_env_t * this, decimal_t * d_r, const uint64_t   uint64_given); 
extern RETURN_TYPE_T decimal__cast_from_uintmax_r(      decimal_env_t * this, decimal_t * d_r, const uintmax_t uintmax_given); 
extern RETURN_TYPE_T decimal__cast_from_int8_r   (      decimal_env_t * this, decimal_t * d_r, const int8_t       int8_given); 
extern RETURN_TYPE_T decimal__cast_from_int16_r  (      decimal_env_t * this, decimal_t * d_r, const int16_t     int16_given); 
extern RETURN_TYPE_T decimal__cast_from_int32_r  (      decimal_env_t * this, decimal_t * d_r, const int32_t     int32_given); 
extern RETURN_TYPE_T decimal__cast_from_int64_r  (      decimal_env_t * this, decimal_t * d_r, const int64_t     int64_given); 
extern RETURN_TYPE_T decimal__cast_from_intmax_r (      decimal_env_t * this, decimal_t * d_r, const intmax_t   intmax_given); 
extern RETURN_TYPE_T decimal__cast_from_float_r      (      decimal_env_t * this, decimal_t * d_r, const float       f_given); 
extern RETURN_TYPE_T decimal__cast_from_double_r     (      decimal_env_t * this, decimal_t * d_r, const double      f_given); 
extern RETURN_TYPE_T decimal__cast_from_long_double_r(      decimal_env_t * this, decimal_t * d_r, const long double f_given); 
extern RETURN_TYPE_T decimal__cast_from_string_int_r (      decimal_env_t * this, decimal_t * d_r, const char * int_cstr, const uint8_t int_cstr_base); 

extern RETURN_TYPE_T decimal__shift_right_by_r(decimal_env_t * this, decimal_t * d_r, const int16_t int16_shift_n); 
extern RETURN_TYPE_T decimal__shift_left_by_r (decimal_env_t * this, decimal_t * d_r, const int16_t int16_shift_n); 
extern RETURN_TYPE_T decimal__add_r           (decimal_env_t * this, decimal_t * d_r, const decimal_t * e_r); 
extern RETURN_TYPE_T decimal__tilde_r         (decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__sub_r           (decimal_env_t * this, decimal_t * d_r, const decimal_t * e_r); 
extern RETURN_TYPE_T decimal__inc_r           (decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__neg_r           (decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__dec_r           (decimal_env_t * this, decimal_t * d_r); 
extern RETURN_TYPE_T decimal__mult_r          (decimal_env_t * this, decimal_t * d_r, const decimal_t * e_r); 
extern RETURN_TYPE_T decimal__div_r           (decimal_env_t * this, decimal_t * d_r, const decimal_t * e_r); 
extern RETURN_TYPE_T decimal__inverse_r(decimal_env_t * decimal_env, decimal_t * d_r); 

extern int         decimal__print_r       (const int stduser_d, decimal_env_t * this, const decimal_t * d_r); 
extern int         decimal__print_ln_r    (const int stduser_d, decimal_env_t * this, const decimal_t * d_r); 
extern int         decimal__print_raw_r   (const int stduser_d, decimal_env_t * this, const decimal_t * d_r); 
extern int         decimal__print_raw_ln_r(const int stduser_d, decimal_env_t * this, const decimal_t * d_r); 

extern int decimal__print__int_and_float_separator_char__r(const int stduser_d, decimal_env_t * decimal_env, const decimal_t * d_r, const char separator); 
extern int decimal__print__base__int_and_float_separator_char__r(const int stduser_d, decimal_env_t * decimal_env, const decimal_t * d_r, const uint8_t printing_base, const char separator); 

extern int_decimal_error_t test_decimal__unit(const int stduser_d, decimal_env_t * decimal_env, const uint16_t a, const uint16_t b); 
extern int_decimal_error_t test_decimal_division__uint16_diag(const int stduser_d, decimal_env_t * decimal_env); 
extern int_decimal_error_t test_decimal_division__uint16_quad(const int stduser_d, decimal_env_t * decimal_env); 


#endif /* DECIMAL_H */
