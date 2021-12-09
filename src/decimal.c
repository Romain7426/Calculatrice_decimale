#include "decimal_global.h"
#include "decimal.h" 

#define X(ident, value) const uint8_t ident##__compiled_value value; 
DECIMAL_VERSION__LIST 
#undef X 

const char       decimal_version[] = { DIGIT_TO_CHAR(DECIMAL_VERSION_MAJOR), '.', DIGIT_TO_CHAR(DECIMAL_VERSION_MINOR), '.', DIGIT_TO_CHAR(DECIMAL_VERSION_REVISION), '\0' }; 
enum {           decimal_version__strlen__const_value = ARRAY_SIZE(decimal_version) - 1 }; 
const uint16_t   decimal_version__strlen = decimal_version__strlen__const_value; 
const char     * decimal_version__get(void) { return decimal_version; }; 
void             decimal_version__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, decimal_version, decimal_version__strlen__const_value); write(stduser_d, "\n", 1); }; };

const char       decimal_example[] = "1 + 2"; 
enum {           decimal_example__strlen__const_value = ARRAY_SIZE(decimal_example) - 1 }; 
const uint16_t   decimal_example__strlen = decimal_example__strlen__const_value; 
const char     * decimal_example__get(void) { return decimal_example; }; 
void             decimal_example__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, decimal_example, decimal_example__strlen__const_value); write(stduser_d, "\n", 1); }; }; 

#define PROGRAM_NAME "Decimal number lib & calculator" 
static const char program_name[] = PROGRAM_NAME; 
enum {  program_name__cstrlen    = ARRAY_SIZE(program_name) - 1 }; 
#define PROGRAM_COPYRIGHT_YEAR1 "2021" 
#define PROGRAM_COPYRIGHT_YEAR2 "2021" 
#define PROGRAM_URL             "https://github.com/Romain7426/Calculatrice_decimale" 
#define PROGRAM_AUTHOR          "https://github.com/Romain7426" 

const char       decimal_url[] = PROGRAM_URL; 
enum {           decimal_url__strlen__const_value = ARRAY_SIZE(decimal_url) - 1 }; 
const uint16_t   decimal_url__strlen = decimal_url__strlen__const_value; 
const char     * decimal_url__get(void) { return decimal_url; }; 
void             decimal_url__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, decimal_url, decimal_url__strlen__const_value); write(stduser_d, "\n", 1); }; }; 

const char decimal_copyright[] = 
"_Software_       : " PROGRAM_NAME "                       " "\n"
"_License_        : " "ISC-like license                                  " "\n" 
"                   " "https://en.wikipedia.org/wiki/ISC_license          " "\n"
"_URL_            : " PROGRAM_URL "         " "\n"
"_Copyright years_: " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 "\n"
"                                                                        " "\n"
PROGRAM_NAME "                         " "\n"
"Copyright (c) " PROGRAM_COPYRIGHT_YEAR1 " - " PROGRAM_COPYRIGHT_YEAR2 " " "\n"
"                                                                        " "\n"
"Permission to use, copy, modify, and distribute this software for any   " "\n"
"purpose with or without fee is hereby granted without any restrictions. " "\n"
"                                                                        " "\n"
"THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL WARRANTIES" "\n"
"WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF        " "\n"
"MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR " "\n"
"ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES  " "\n"
"WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN   " "\n"
"ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF " "\n"
"OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.          " "\n"
"                                                                        " "\n" 
"NB: We do not care of what you do with this code as long as             " "\n" 
"    you do not prevent us nor others from using it.                     " "\n" 
;

enum {           decimal_copyright__strlen__const_value = ARRAY_SIZE(decimal_copyright) - 1 }; 
const uint16_t   decimal_copyright__strlen = (uint16_t) decimal_copyright__strlen__const_value; 
const char     * decimal_copyright__get(void) { return decimal_copyright; }; 
void             decimal_copyright__print(const int stduser_d) { if (stduser_d > 0) { write(stduser_d, decimal_copyright, decimal_copyright__strlen__const_value); if ('\n' != *(decimal_copyright + decimal_copyright__strlen__const_value - 1)) write(stduser_d, "\n", 1); }; }; 



// --- DECIMAL_ERROR --- 

#define X(ident, value) const int_decimal_error_t ident##__compiled_value = ident; 
DECIMAL_ERROR__LIST 
#undef X 

#define X(ident, value) #ident, 
const char * int_decimal_error__id_cstr[DECIMAL_ERROR__COUNT + 1] = { 
DECIMAL_ERROR__LIST 
  NULL
}; 
#undef X 
 
const uint8_t int_decimal_error__id_cstr__size__compiled_value = ARRAY_SIZE(int_decimal_error__id_cstr); 

#define X(ident, value) ident, 
const int_decimal_error_t int_decimal_error__id_value[DECIMAL_ERROR__COUNT] = { 
DECIMAL_ERROR__LIST 
}; 
#undef X 

const uint8_t int_decimal_error__id_value__size__compiled_value = ARRAY_SIZE(int_decimal_error__id_value); 

const char * int_decimal_error__get_cstr(const int_decimal_error_t error_id) { 
  const char * error_id__cstr = NULL; 
  switch (error_id) { 
#define X(ident, value) case ident: error_id__cstr = #ident; break; 
  DECIMAL_ERROR__LIST
#undef X 
  }; 
  return error_id__cstr; 
}; 


// --- DECIMAL_ENV_T --- 

#define X(ident, value) const uint16_t ident##__compiled_value value; 
DECIMAL_ENV_CONST__LIST 
#undef X 

struct decimal_env_t { 
  uint8_t malloced_flag; // 0 if not, 1 if yes. 
  
  int stdlog_d; // Foreign — we don't own it; valid only if 'stdlog_d > 0' 
  
  int_decimal_error_t error_id; // 0: none; …<0: error; …>0: warning 
  char                error_str[DECIMAL_ENV__ERROR_BUFFER_SIZE]; 
  uint16_t            error_size; 
  
  char     string_stack[DECIMAL_ENV__STRING_STACK_SIZE]; 
  uint16_t string_stack_nb; 
  
  const char * copyright; 
  
  const char * filename; 

  char print__int_and_float_separator_char; 
  
}; 

enum { DECIMAL_ENV__SIZEOF__E = sizeof(struct decimal_env_t) }; 
const uint16_t decimal_env__sizeof = sizeof(struct decimal_env_t); 

#define DECIMAL__DEFAULT_PRINTING_INT_AND_FLOAT_SEPARATOR_CHAR '.' 

decimal_env_t * decimal_env__make_m(const int stdlog_d) { 
  decimal_env_t * this; 
  this = (decimal_env_t *) malloc(DECIMAL_ENV__SIZEOF__E); 
  if (NULL == this) return NULL; 
  decimal_env__make_r(this, stdlog_d); 
  this -> malloced_flag = 1; 
  return this; 
}; 

decimal_env_t * decimal_env__make_r(decimal_env_t * this, const int stdlog_d) { 
  bzero(this, sizeof(*this)); 
  this -> stdlog_d = stdlog_d; 
  this -> error_size = DECIMAL_ENV__ERROR_BUFFER_SIZE; 
  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb = 1; 
  this -> copyright = decimal_copyright; 
  this -> print__int_and_float_separator_char = DECIMAL__DEFAULT_PRINTING_INT_AND_FLOAT_SEPARATOR_CHAR; 
  return this; 
}; 

decimal_env_t * decimal_env__make_b(const int buffer_size, uint8_t * buffer, int * buffer_size_used_r, const int stdlog_d) { 
  decimal_env_t * this; 
  if (buffer_size < ((int)(sizeof(*this)))) return NULL; 
  if (NULL == buffer) return NULL; 
  this = (decimal_env_t *) buffer; 
  if (NULL != buffer_size_used_r) { 
    *buffer_size_used_r = (sizeof(*this)); 
  }; 
  return decimal_env__make_r(this, stdlog_d); 
}; 

void decimal_env__delete_r(decimal_env_t * this) { 
  const int malloced_flag = this -> malloced_flag; 
  bzero(this, sizeof(*this)); 
  this -> malloced_flag = malloced_flag; 
  this -> error_size    = DECIMAL_ENV__ERROR_BUFFER_SIZE; 
}; 

void decimal_env__delete(decimal_env_t * this) { 
  decimal_env__delete_r(this); 
  if (1 == this -> malloced_flag) { 
    free(this); 
  }; 
}; 

void decimal_env__bzero(decimal_env_t * this) { 
  const int malloced_flag = this -> malloced_flag; 
  const int stdlog_d      = this -> stdlog_d; 
  //const int error_size    = this -> error_size; 
  bzero(this, sizeof(*this)); 
  this -> malloced_flag = malloced_flag; 
  this -> stdlog_d      = stdlog_d; 
  this -> error_size    = DECIMAL_ENV__ERROR_BUFFER_SIZE; //error_size; 
  this -> string_stack[0] = '\0'; 
  this -> string_stack_nb = 1; 
  this -> copyright = decimal_copyright; 
  this -> print__int_and_float_separator_char = DECIMAL__DEFAULT_PRINTING_INT_AND_FLOAT_SEPARATOR_CHAR; 
}; 

const char * decimal_env__strcopy(decimal_env_t * this, const char * str) { 
  if (NULL ==  str) { return NULL; }; 
  if ('\0' == *str) { return this -> string_stack; }; 
  const int len1 = 1 + strlen(str); 
  if (this -> string_stack_nb + len1 > DECIMAL_ENV__STRING_STACK_SIZE) { 
    this -> error_id = DECIMAL__STRCOPY; 
    snprintf(this -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Not enough space available in the decimal_env buffer to copy the string (mem needed: %d ; mem available: %d ; str: '%s')", len1, DECIMAL_ENV__STRING_STACK_SIZE - this -> string_stack_nb, str); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return NULL; 
  }; 
  char * new_str = this -> string_stack + this -> string_stack_nb; 
  bcopy(str, new_str, len1); 
  this -> string_stack_nb += len1; 
  return new_str; 
}; 

void decimal_env__printing_int_and_float_separator_char__set(decimal_env_t * this, const char separator) { 
  this -> print__int_and_float_separator_char = separator; 
}; 

char decimal_env__printing_int_and_float_separator_char__get(const decimal_env_t * this) { 
  return this -> print__int_and_float_separator_char; 
}; 


// --- DECIMAL_STATUS --- 

#define X(ident, value) const uint8_t ident##__compiled_value = ident; 
DECIMAL_STATUS__LIST 
#undef X 

#define X(ident, value) #ident, 
const char * decimal_status__id_cstr[DECIMAL_STATUS__COUNT + 1] = { 
DECIMAL_STATUS__LIST 
  NULL
}; 
#undef X 
 
const uint8_t decimal_status__id_cstr__size__compiled_value = ARRAY_SIZE(decimal_status__id_cstr); 

#define X(ident, value) ident, 
const uint8_t decimal_status__id_value[DECIMAL_STATUS__COUNT] = { 
DECIMAL_STATUS__LIST 
}; 
#undef X 

const uint8_t decimal_status__id_value__size__compiled_value = ARRAY_SIZE(decimal_status__id_value); 



const char * decimal_status__cstr(const uint8_t status) { 
  const char * status_cstr = NULL; 
  switch (status) { 
#define X(ident, value) case ident: status_cstr = #ident; break; 
  DECIMAL_STATUS__LIST 
#undef X 
  }; 
  return status_cstr; 
}; 

uint8_t decimal_status__id(const uint8_t status) { 
  uint8_t status_id; // = DECIMAL_STATUS__COUNT; 
  switch (status) { 
#define X(ident, value) case ident: status_id = ident##___ID; break; 
  DECIMAL_STATUS__LIST 
#undef X 
  }; 
  return status_id; 
}; 

int decimal_status__value_is_a_status_huh(const uint8_t status) { 
  int value_is_a_status_huh; // = false; status_id; // = DECIMAL_STATUS__COUNT; 
  switch (status) { 
#define X(ident, value) case ident: value_is_a_status_huh = true; break; 
  DECIMAL_STATUS__LIST 
#undef X 
    default: value_is_a_status_huh = false; break; 
  }; 
  return value_is_a_status_huh; 
}; 




// --- DECIMAL STRUCT --- 

enum { DECIMAL_STATUS_INDEX              = 0 }; 
enum { DECIMAL_STATUS_SIZE               = 1 }; 
enum { DECIMAL_DIGITS_INDEX              = DECIMAL_STATUS_INDEX + DECIMAL_STATUS_SIZE }; 
enum { DECIMAL_DIGITS_SIZE               = DECIMAL_SIZE - DECIMAL_STATUS_SIZE }; 
enum { DECIMAL_DIGITS_INDEX_XLAST        = DECIMAL_DIGITS_INDEX + DECIMAL_DIGITS_SIZE }; 
enum { DECIMAL_DIGITS_INDEX_ELAST        = DECIMAL_DIGITS_INDEX_XLAST - 1 }; 
enum { DECIMAL_DIGITS_INDEX_FIRST        = DECIMAL_DIGITS_INDEX }; 
enum { DECIMAL_DIGITS_INDEX_FIRST_MINUS1 = DECIMAL_DIGITS_INDEX_FIRST - 1 }; 
enum { DECIMAL_DIGITS_INDEX_LAST         = DECIMAL_DIGITS_INDEX_ELAST }; 
enum { DECIMAL_DIGITS_INDEX_LAST_PLUS1   = DECIMAL_DIGITS_INDEX_LAST + 1 }; 
enum { DECIMAL_FIXED_POINT_INDEX         = DECIMAL_DIGITS_INDEX + DECIMAL_FIXED_POINT_SIZE }; 
enum { DECIMAL_FIXED_POINT_INDEX_MINUS1  = DECIMAL_FIXED_POINT_INDEX - 1 }; 
enum { DECIMAL_FIXED_POINT_SIZE_MINUS1   = DECIMAL_FIXED_POINT_SIZE - 1 }; 
enum { DECIMAL_ZERO_INDEX                = DECIMAL_FIXED_POINT_INDEX }; 
enum { DECIMAL_INT_INDEX                 = DECIMAL_FIXED_POINT_INDEX }; 
enum { DECIMAL_INT_SIZE                  = DECIMAL_DIGITS_SIZE - DECIMAL_FIXED_POINT_SIZE }; 
enum { DECIMAL_EOF_BYTE                  = 255 }; 
enum { DECIMAL_SIZE_MINUS1               = DECIMAL_SIZE - 1 }; 
enum { DECIMAL_SIZE_DOUBLE               = DECIMAL_SIZE << 1 }; 
enum { DECIMAL_SIZE_DOUBLE_MINUS1        = DECIMAL_SIZE_DOUBLE - 1 }; 
enum { DECIMAL_BASE_MINUS1               = DECIMAL_BASE - 1 }; 

const uint16_t DECIMAL_SIZE__compiled_value             = DECIMAL_SIZE; 
const uint8_t  DECIMAL_FIXED_POINT_SIZE__compiled_value = DECIMAL_FIXED_POINT_SIZE; 
const uint8_t  DECIMAL_BASE__compiled_value             = DECIMAL_BASE; 

 
#define LOG2_OF_DECIMAL_BASE_AS_MACRO (GET_LOG2_VALUE_AS_MACRO(DECIMAL_BASE)) 
//enum { LOG2_OF_DECIMAL_BASE = LOG2_OF_DECIMAL_BASE_AS_MACRO }; 
enum { LOG2_OF_DECIMAL_BASE_AS_ENUM = GET_LOG2_VALUE_AS_ENUM(DECIMAL_BASE) }; 

#define LOG2_OF_DECIMAL_BASE LOG2_OF_DECIMAL_BASE_AS_ENUM 
//#define LOG2_OF_DECIMAL_BASE LOG2_OF_DECIMAL_BASE_AS_MACRO

static const uint8_t LOG_2_OF_DECIMAL_BASE__compiled_value = LOG2_OF_DECIMAL_BASE; 

enum { ONE_THIRD_OF_DECIMAL_BASE = (DECIMAL_BASE >> 2) + (DECIMAL_BASE >> 4) + (DECIMAL_BASE >> 6) }; 


static void decimal_struct__check_and_assert_compile_d76384342(void) { 
  ASSERT_COMPILE(DECIMAL_DIGITS_SIZE >= 1); 
  ASSERT_COMPILE(DECIMAL_INT_SIZE >= 2); // To have a quick & simple way to check if a mantisse is zero, we assume that the size is always greater or equal than two. // TODO XXX FIXME: Could be improved though. I'll see that later. 
  ASSERT_COMPILE(DECIMAL_FIXED_POINT_SIZE >= 2); // To have a quick & simple way to check if a number is greater or equal to 4/3. 
}; 


// --- DECIMAL EXPR --- 

const uint8_t DECIMAL__EXPRESSION_NESTEDNESS_MAX__compiled_value = (uint8_t) DECIMAL__EXPRESSION_NESTEDNESS_MAX; 
const uint8_t DECIMAL__LONGEST_INFIX_EXPRESSION__compiled_value  = (uint8_t) DECIMAL__LONGEST_INFIX_EXPRESSION; 


// --- DECIMAL METHODS --- 

#define RETURN_ERROR 1

#ifdef RETURN_ERROR 
#  define RETURN_TYPE_T int_decimal_error_t 
#else 
#  define RETURN_TYPE_T decimal_t * 
#endif 


#include "decimal_print_raw.ci" 


static void decimal_mantisse__set_eof_r(decimal_t * d_r) { 
  for (int i = DECIMAL_DIGITS_INDEX; i < DECIMAL_DIGITS_INDEX_XLAST; i++) { 
    (*d_r)[i] = DECIMAL_EOF_BYTE; 
  }; 
}; 

static void decimal_mantisse__set_all_digits_r(uint8_t * d_mantisse_r, const uint8_t d_mantisse_len, const uint8_t digit) { 
  uint8_t * p;
  p = d_mantisse_r; 
  for (int i = 0; i < d_mantisse_len; i++) { 
    *p = digit; 
    p++; 
  }; 
}; 

static void decimal_mantisse__set_zero_r(decimal_t * d_r) { 
  int i; 
  for (i = DECIMAL_DIGITS_INDEX; i <= DECIMAL_FIXED_POINT_SIZE; i++) { 
    (*d_r)[i] = DECIMAL_EOF_BYTE; 
  }; 
  (*d_r)[i] = 0; 
  i++; 
  for (; i < DECIMAL_SIZE; i++) { 
    (*d_r)[i] = DECIMAL_EOF_BYTE; 
  }; 
}; 

static void decimal_mantisse__EOF2ZERO_r(decimal_t * d_r) { 
  for (int i = 1; i < DECIMAL_SIZE; i++) { 
    if ((*d_r)[i] != DECIMAL_EOF_BYTE) continue; 
    (*d_r)[i] = 0; 
  }; 
}; 

static void decimal_mantisse__EOF2ZERO_right_r(decimal_t * d_r) { 
  for (int i = 1; i < DECIMAL_SIZE; i++) { 
    if ((*d_r)[i] != DECIMAL_EOF_BYTE) break; 
    (*d_r)[i] = 0; 
  }; 
}; 

static void decimal_mantisse__ZERO2EOF_right_r(decimal_t * d_r) { 
  int index = DECIMAL_DIGITS_INDEX_FIRST_MINUS1; 
  for (;;) { 
    index++; 
    if (index >= DECIMAL_FIXED_POINT_INDEX) break; 
    if ((*d_r)[index] == DECIMAL_EOF_BYTE) continue; 
    if ((*d_r)[index] != 0) break; 
    (*d_r)[index] = DECIMAL_EOF_BYTE; 
  }; 
}; 

static void decimal_mantisse__ZERO2EOF_left_r(decimal_t * d_r) { 
  int index = DECIMAL_DIGITS_INDEX_LAST_PLUS1; 
  for (;;) { 
    index--; 
    if (index <= DECIMAL_FIXED_POINT_INDEX) break; 
    if ((*d_r)[index] == DECIMAL_EOF_BYTE) continue; 
    if ((*d_r)[index] != 0) break; 
    (*d_r)[index] = DECIMAL_EOF_BYTE; 
  }; 
}; 

static void decimal_status__if_ZERO_then_set_status_r(decimal_t * d_r) { 
  if (((*d_r)[DECIMAL_FIXED_POINT_SIZE + 1] == 0) && 
      ((*d_r)[DECIMAL_FIXED_POINT_SIZE + 2] == DECIMAL_EOF_BYTE) && 
      ((*d_r)[DECIMAL_FIXED_POINT_SIZE    ] == DECIMAL_EOF_BYTE)) { 
    (*d_r)[0] = DECIMAL_STATUS__ZERO; 
  }; 
}; 

static void decimal_status__if_ZERO_then_set_EPSILON_status_r(decimal_t * d_r) { 
  if (((*d_r)[DECIMAL_FIXED_POINT_SIZE + 1] == 0) && 
      ((*d_r)[DECIMAL_FIXED_POINT_SIZE + 2] == DECIMAL_EOF_BYTE) && 
      ((*d_r)[DECIMAL_FIXED_POINT_SIZE    ] == DECIMAL_EOF_BYTE)) { 
    (*d_r)[0] = ((*d_r)[0] == DECIMAL_STATUS__POS) ? DECIMAL_STATUS__POS_EPSILON : DECIMAL_STATUS__NEG_EPSILON; 
  }; 
}; 

uint8_t decimal_status__neg(decimal_env_t * decimal_env, const uint8_t d_status) { 
  uint8_t d_status_neg; 
  d_status_neg = d_status; 
  switch (d_status) { 
  case DECIMAL_STATUS__INVALID                        : goto label__exit; 
  case DECIMAL_STATUS__ZERO                           : goto label__exit; 
  case DECIMAL_STATUS__INFINI                         : goto label__exit; 
  case DECIMAL_STATUS__POS                            : d_status_neg = DECIMAL_STATUS__NEG        ; goto label__exit;
  case DECIMAL_STATUS__NEG                            : d_status_neg = DECIMAL_STATUS__POS        ; goto label__exit; 
  case DECIMAL_STATUS__POS_INFINI                     : d_status_neg = DECIMAL_STATUS__NEG_INFINI ; goto label__exit;
  case DECIMAL_STATUS__NEG_INFINI                     : d_status_neg = DECIMAL_STATUS__POS_INFINI ; goto label__exit;
  case DECIMAL_STATUS__POS_EPSILON                    : d_status_neg = DECIMAL_STATUS__NEG_EPSILON; goto label__exit;
  case DECIMAL_STATUS__NEG_EPSILON                    : d_status_neg = DECIMAL_STATUS__POS_EPSILON; goto label__exit;
  case DECIMAL_STATUS__DEVELOPPEMENT_LIMITE_NECESSAIRE: goto label__exit;  
  default: goto error_label__not_listed_status; 
  }; 
  
  assert(false); 
  
 label__exit: { 
    decimal_env -> error_id = DECIMAL__OK; 
    return d_status_neg; 
  }; 

 error_label__not_listed_status: { 
    const char * status_cstr = decimal_status__cstr(d_status); 
    decimal_env -> error_id = DECIMAL__STATUS_NOT_LISTED_IN_SWITCH; 
    snprintf(decimal_env -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Status not listed in switch: %d [%s]", ((int)d_status), status_cstr); 
    if (decimal_env -> stdlog_d > 0) { dprintf(decimal_env -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, decimal_env -> error_str); }; 
    return DECIMAL_STATUS__INVALID; 
  }; 
  
}; 


enum { MANTISSE_ENDS__ZERO__IGNORE_HIGH__MASK = 2 }; 
enum { MANTISSE_ENDS__ZERO__IGNORE_LOW__MASK  = 1 }; 
enum { MANTISSE_ENDS__ZERO__IGNORE_BOTH__MASK = MANTISSE_ENDS__ZERO__IGNORE_HIGH__MASK + MANTISSE_ENDS__ZERO__IGNORE_LOW__MASK }; 
enum { MANTISSE_ENDS__ZERO__IGNORE_NONE__MASK = 0 }; 

#define MANTISSE_ENDS__ZERO__IGNORE_HIGH_HUH(__s__) ((__s__) & MANTISSE_ENDS__ZERO__IGNORE_HIGH__MASK) 
#define MANTISSE_ENDS__ZERO__IGNORE_LOW_HUH(__s__) ((__s__) & MANTISSE_ENDS__ZERO__IGNORE_LOW__MASK) 

#if 1 
static void decimal_mantisse__get_last_and_first_indexes(const uint8_t * mantisse, const uint8_t mantisse_size, const uint8_t what_about_zeroes, uint8_t * d_last_index_r, uint8_t * d_first_index_r, uint8_t * empty_huh_r) { 
  goto label__start; 

  label__empty: { 
    if (NULL != empty_huh_r) *empty_huh_r = true; 
    return; 
  }; 
  
  
  label__start: {}; 
  
  if (0 == mantisse_size) { goto label__empty; }; 
  
  uint8_t d_last_index; 
  if (MANTISSE_ENDS__ZERO__IGNORE_HIGH_HUH(what_about_zeroes)) { 
    uint16_t d_index = mantisse_size; 
    for (;;) { 
      d_index--; 
      if (d_index < 0) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value == 0) continue; 
      break; 
    }; 
    d_last_index = d_index; 
  } 
  else { 
    uint16_t d_index = mantisse_size; 
    for (;;) { 
      d_index--; 
      if (d_index < 0) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      //if (d_value == 0) continue; 
      break; 
    }; 
    d_last_index = d_index; 
    // Now, check if empty. 
    d_index++; 
    for (;;) { 
      d_index--; 
      if (d_index < 0) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value == 0) continue; 
      break; 
    }; 
  }; 
  
  uint8_t d_first_index;  
  if (MANTISSE_ENDS__ZERO__IGNORE_LOW_HUH(what_about_zeroes)) { 
    uint16_t d_index = -1; 
    for (;;) { 
      d_index++; 
      if (d_index >= mantisse_size) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value == 0) continue; 
      break; 
    }; 
    d_first_index = d_index;  
  } 
  else { 
    uint16_t d_index = -1; 
    for (;;) { 
      d_index++; 
      if (d_index >= mantisse_size) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      //if (d_value == 0) continue; 
      break; 
    }; 
    d_first_index = d_index;  
    // Now, check if empty. 
    d_index--; 
    for (;;) { 
      d_index++; 
      if (d_index >= mantisse_size) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value == 0) continue; 
      break; 
    }; 
  }; 
  
  if (NULL !=  d_last_index_r) * d_last_index_r =  d_last_index; 
  if (NULL != d_first_index_r) *d_first_index_r = d_first_index; 
  if (NULL !=     empty_huh_r) *    empty_huh_r =         false; 
}; 
#else
static void decimal_mantisse__get_last_and_first_indexes(const decimal_t * d_r, uint8_t * d_last_index_r, uint8_t * d_first_index_r, uint8_t * malformed_number_huh_r) { 
  uint8_t d_last_index; 
  { 
    uint16_t d_index = DECIMAL_DIGITS_INDEX_LAST_PLUS1; 
    for (;;) { 
      if (d_index <= DECIMAL_DIGITS_INDEX_FIRST) goto label__error__malformed_number; 
      d_index--; 
      const uint8_t d_value = (*d_r)[d_index]; 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value != 0) break; 
      //*(shifted_d_ptr + d_index) = DECIMAL_EOF_BYTE; 
    }; 
    d_last_index = d_index; 
  }; 
  uint8_t d_first_index; 
  { 
    uint16_t d_index = DECIMAL_DIGITS_INDEX_FIRST_MINUS1; 
    for (;;) { 
      if (d_index >= DECIMAL_DIGITS_INDEX_LAST) goto label__error__malformed_number; 
      d_index++; 
      const uint8_t d_value = (*d_r)[d_index]; 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value != 0) break; 
      //*(shifted_d_ptr + d_index) = DECIMAL_EOF_BYTE; 
    }; 
    d_first_index = d_index;  
  }; 
  //const uint8_t d_len = d_last_index - d_first_index + 1; 
  

  if (NULL != d_last_index_r) *d_last_index_r = d_last_index; 
  if (NULL != d_first_index_r) *d_first_index_r = d_first_index; 
  if (NULL != malformed_number_huh_r) *malformed_number_huh_r = false; 
  return; 
  
  label__error__malformed_number: { 
    if (NULL != malformed_number_huh_r) *malformed_number_huh_r = true; 
    return; 
  }; 
}; 
#endif 


// Used by mult/div/etc. functions that store intermediate results in a larger array (usually, twice the size). 
static void decimal_mantisse__get_last_and_first_indexes__uint16(const uint8_t * mantisse, const uint16_t mantisse_size, const uint8_t what_about_zeroes, uint16_t * d_last_index_r, uint16_t * d_first_index_r, uint8_t * empty_huh_r) { 
  goto label__start; 

  label__empty: { 
    if (NULL != empty_huh_r) *empty_huh_r = true; 
    return; 
  }; 
  
  
  label__start: {}; 
  
  if (0 == mantisse_size) { goto label__empty; }; 
  
  uint16_t d_last_index; 
  if (MANTISSE_ENDS__ZERO__IGNORE_HIGH_HUH(what_about_zeroes)) { 
    uint16_t d_index = mantisse_size; 
    for (;;) { 
      d_index--; 
      if (d_index < 0) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value == 0) continue; 
      break; 
    }; 
    d_last_index = d_index; 
  } 
  else { 
    uint16_t d_index = mantisse_size; 
    for (;;) { 
      d_index--; 
      if (d_index < 0) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      //if (d_value == 0) continue; 
      break; 
    }; 
    d_last_index = d_index; 
    // Now, check if empty. 
    d_index++; 
    for (;;) { 
      d_index--; 
      if (d_index < 0) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value == 0) continue; 
      break; 
    }; 
  }; 
  
  uint16_t d_first_index; 
  if (MANTISSE_ENDS__ZERO__IGNORE_LOW_HUH(what_about_zeroes)) { 
    uint16_t d_index = -1; 
    for (;;) { 
      d_index++; 
      if (d_index >= mantisse_size) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value == 0) continue; 
      break; 
    }; 
    d_first_index = d_index;  
  } 
  else { 
    uint16_t d_index = -1; 
    for (;;) { 
      d_index++; 
      if (d_index >= mantisse_size) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      //if (d_value == 0) continue; 
      break; 
    }; 
    d_first_index = d_index;  
    // Now, check if empty. 
    d_index--; 
    for (;;) { 
      d_index++; 
      if (d_index >= mantisse_size) goto label__empty; 
      const uint8_t d_value = *(mantisse + d_index); 
      if (d_value == DECIMAL_EOF_BYTE) continue; 
      if (d_value == 0) continue; 
      break; 
    }; 
  }; 
  
  if (NULL !=  d_last_index_r) * d_last_index_r =  d_last_index; 
  if (NULL != d_first_index_r) *d_first_index_r = d_first_index; 
  if (NULL !=     empty_huh_r) *    empty_huh_r =         false; 
}; 









RETURN_TYPE_T decimal__make_b(decimal_env_t * decimal_env, const int buffer_size, uint8_t * buffer, int * buffer_size_used_r) { 
  decimal_t * d_ptr; 
  if (buffer_size < ((int)(sizeof(*d_ptr)))) goto error_label__buffer_size_too_small; 
  if (NULL == buffer) goto error_label__buffer_is_null; 
  d_ptr = (decimal_t *) buffer; 
  if (NULL != buffer_size_used_r) { 
    *buffer_size_used_r = (sizeof(*d_ptr)); 
  }; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_ptr; 
#endif 

 error_label__buffer_size_too_small: { 
    decimal_env -> error_id = DECIMAL__MAKE_B_BUFFER_SIZE_TOO_SMALL; 
    snprintf(decimal_env -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Not enough space available in the provided buffer (mem needed: %d ; mem available: %d)", ((int)(sizeof(*d_ptr))), buffer_size); 
    if (decimal_env -> stdlog_d > 0) { dprintf(decimal_env -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, decimal_env -> error_str); }; 
#ifdef RETURN_ERROR 
    return decimal_env -> error_id; 
#else 
    return NULL; 
#endif 
  }; 

 error_label__buffer_is_null: { 
    decimal_env -> error_id = DECIMAL__MAKE_B_BUFFER_IS_NULL; 
    snprintf(decimal_env -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Provided buffer is NULL"); 
    if (decimal_env -> stdlog_d > 0) { dprintf(decimal_env -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, decimal_env -> error_str); }; 
#ifdef RETURN_ERROR 
    return decimal_env -> error_id; 
#else 
    return NULL; 
#endif 
  }; 
  
}; 

RETURN_TYPE_T decimal__reset_r(const decimal_env_t * decimal_env, decimal_t * d_r) { 
  decimal_mantisse__set_eof_r(d_r); 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__zero_r(const decimal_env_t * this, decimal_t * d_r) {
  decimal_mantisse__set_eof_r(d_r); 
  (*d_r)[DECIMAL_INT_INDEX] = 0; 
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__ZERO; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__invalid_r(const decimal_env_t * this, decimal_t * d_r) { 
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__INVALID; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__pos_epsilon_r(const decimal_env_t * this, decimal_t * d_r) { 
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__POS_EPSILON; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__neg_epsilon_r(const decimal_env_t * this, decimal_t * d_r) { 
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__NEG_EPSILON; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__pos_infini_r(const decimal_env_t * this, decimal_t * d_r) { 
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__POS_INFINI; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__neg_infini_r(const decimal_env_t * this, decimal_t * d_r) { 
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__NEG_INFINI; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__max_value_r(const decimal_env_t * this, decimal_t * d_r) { 
  decimal_mantisse__set_all_digits_r((*d_r) + DECIMAL_INT_INDEX, DECIMAL_DIGITS_SIZE, DECIMAL_BASE_MINUS1); 
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__POS; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__min_value_r(const decimal_env_t * this, decimal_t * d_r) { 
  decimal_mantisse__set_all_digits_r((*d_r) + DECIMAL_INT_INDEX, DECIMAL_DIGITS_SIZE, DECIMAL_BASE_MINUS1); 
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__NEG; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__cast_from_uintmax_r(decimal_env_t * this, decimal_t * d_r, const uintmax_t uintmax_given) { 
  //dprintf(STDERR_FILENO, "uintmax_given = " "%" __UINTMAX_FMTu__ "\n", uintmax_given); 
  if (0 == uintmax_given) return decimal__zero_r(this, d_r); 
  
  decimal_mantisse__set_eof_r(d_r); 
  
  uint8_t * d_mantisse_r = (*d_r) + DECIMAL_INT_INDEX; 
  const uint8_t d_mantisse_len = DECIMAL_INT_SIZE; 
  uint8_t * p = d_mantisse_r; 
  uintmax_t quotient = uintmax_given; 
  for (uint8_t i = 0; i < d_mantisse_len; i++) { 
    //dprintf(STDERR_FILENO, "quotient = " "%" __UINTMAX_FMTu__ "\n", quotient); 
    *p = DECIMAL_BASE__GET_REMAINDER(quotient); 
    quotient = DECIMAL_BASE__GET_QUOTIENT(quotient); 
    p++; 
    if (0 == quotient) break; 
  }; 
  if (0 != quotient) { 
    (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__POS_INFINI; 
    return DECIMAL__INTEGER_TOO_LARGE; 
  }; 
  
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__POS; 
  return DECIMAL__OK; 
}; 

extern RETURN_TYPE_T decimal__cast_from_uint64_r(decimal_env_t * this, decimal_t * d_r, const uint64_t uint64_given) { 
  return decimal__cast_from_uintmax_r(this, d_r, uint64_given); 
}; 

extern RETURN_TYPE_T decimal__cast_from_uint32_r(decimal_env_t * this, decimal_t * d_r, const uint32_t uint32_given) { 
  return decimal__cast_from_uintmax_r(this, d_r, uint32_given); 
}; 

extern RETURN_TYPE_T decimal__cast_from_uint16_r(decimal_env_t * this, decimal_t * d_r, const uint16_t uint16_given) { 
  return decimal__cast_from_uintmax_r(this, d_r, uint16_given); 
}; 

extern RETURN_TYPE_T decimal__cast_from_uint8_r(decimal_env_t * this, decimal_t * d_r, const uint8_t uint8_given) { 
  return decimal__cast_from_uintmax_r(this, d_r, uint8_given); 
}; 

extern RETURN_TYPE_T decimal__cast_from_uint_r(decimal_env_t * this, decimal_t * d_r, const uint_t uint_given) { 
  return decimal__cast_from_uintmax_r(this, d_r, uint_given); 
}; 

extern RETURN_TYPE_T decimal__cast_from_intmax_r(decimal_env_t * this, decimal_t * d_r, const intmax_t intmax_given) { 
  if (0 == intmax_given) return decimal__zero_r(this, d_r); 
  if (0  < intmax_given) return decimal__cast_from_uintmax_r(this, d_r, intmax_given); 
  
  const int_decimal_error_t error_id = decimal__cast_from_uintmax_r(this, d_r, -intmax_given); 
  if (error_id < 0) return error_id; 
  
  const uint8_t d_status       = (*d_r)[DECIMAL_STATUS_INDEX]; 
  const uint8_t d_status_neg   = decimal_status__neg(this, d_status); 
  (*d_r)[DECIMAL_STATUS_INDEX] = d_status_neg; 
#ifdef RETURN_ERROR 
  return error_id; 
#else 
  return (0 <= error_id) ? d_r : NULL; 
#endif 
}; 

extern RETURN_TYPE_T decimal__cast_from_int64_r(decimal_env_t * this, decimal_t * d_r, const int64_t int64_given) { 
  return decimal__cast_from_intmax_r(this, d_r, int64_given); 
}; 

extern RETURN_TYPE_T decimal__cast_from_int32_r(decimal_env_t * this, decimal_t * d_r, const int32_t int32_given) { 
  return decimal__cast_from_intmax_r(this, d_r, int32_given); 
}; 

extern RETURN_TYPE_T decimal__cast_from_int16_r(decimal_env_t * this, decimal_t * d_r, const int16_t int16_given) { 
  return decimal__cast_from_intmax_r(this, d_r, int16_given); 
}; 

extern RETURN_TYPE_T decimal__cast_from_int8_r(decimal_env_t * this, decimal_t * d_r, const int8_t int8_given) { 
  return decimal__cast_from_intmax_r(this, d_r, int8_given); 
}; 

extern RETURN_TYPE_T decimal__cast_from_int_r(decimal_env_t * this, decimal_t * d_r, const int int_given) { 
  return decimal__cast_from_intmax_r(this, d_r, int_given); 
}; 


#if 0 
//RETURN_TYPE_T decimal__make_int_r(decimal_t * d_r, const int n_given) { 
static RETURN_TYPE_T decimal__cast_from_int_r__old001(decimal_env_t * decimal_env, decimal_t * d_r, const int n_given) { 
  decimal_mantisse__set_eof_r(d_r); 
  
  if (n_given == 0) { 
    (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__ZERO; 
    (*d_r)[DECIMAL_INT_INDEX] = 0; 
    return DECIMAL__OK; 
  }; 
  
  int n; 
  if (n_given < 0) { n = - n_given; (*d_r)[0] = DECIMAL_STATUS__NEG; } 
  else { n = n_given; (*d_r)[0] = DECIMAL_STATUS__POS; } 
  
  int index = DECIMAL_INT_INDEX; 
  
  for (;;) { 
#if 1 
    (*d_r)[index] = DECIMAL_BASE__GET_REMAINDER(n); 
    n             = DECIMAL_BASE__GET_QUOTIENT(n); 
#else 
    (*d_r)[index] = n % DECIMAL_BASE; 
    n /= DECIMAL_BASE; 
#endif 
    index++; 
    if (0 == n) break; 
  }; 
  
  return DECIMAL__OK; 
}; 
#endif 


RETURN_TYPE_T decimal__cast_from_float_r(decimal_env_t * this, decimal_t * d_r, const float f_given) { 
  const float  f_pos       = (f_given < 0) ? -f_given : f_given; 
  const int    f_pos_class = fpclassify(f_pos); 
  if (FP_ZERO     == f_pos_class) return decimal__zero_r(this, d_r); 
  const int8_t f_sign      = (f_given < 0) ? -1 : 1; 
  if (f_pos <= __FLT_EPSILON__) return (f_sign > 0) ? decimal__pos_epsilon_r(this, d_r) : decimal__neg_epsilon_r(this, d_r); 
  if (FP_INFINITE == f_pos_class) return (f_sign > 0) ? decimal__pos_infini_r(this, d_r) : decimal__neg_infini_r(this, d_r); 
  if (FP_NAN      == f_pos_class) return decimal__invalid_r(this, d_r); 
  
  assert(isfinite(f_pos)); 
  
  //dprintf(STDERR_FILENO, "f_pos = " "%Lf" "\n", (long double) f_pos); 
  const uintmax_t f_int_part = (uintmax_t) f_pos; 
  //dprintf(STDERR_FILENO, "f_int_part = " "%" __UINTMAX_FMTu__ "\n", f_int_part); 
  const int_decimal_error_t error_id = decimal__cast_from_uintmax_r(this, d_r, f_int_part); 
  if (error_id < 0) return error_id; 
  
  int8_t all_digits_null_huh = (0 == f_int_part); 

  float f_iter = f_pos - (float)f_int_part; 
  float f_epsilon = __FLT_EPSILON__; 
  int index = DECIMAL_INT_INDEX; 
  for (;;) { 
    //dprintf(STDERR_FILENO, "f_iter = " "%Lf" "\n", (long double) f_iter); 
    //dputs_array(STDERR_FILENO, __func__, ": ", "index = ", int_string__stack(index), "\n"); 
    if (FP_ZERO == fpclassify(f_iter)) break; 
    //if (f_iter <= __FLT_EPSILON__) break; 
    if (f_iter <= f_epsilon) break; 
    index--; 
    if (index < DECIMAL_DIGITS_INDEX_FIRST) break; 
    f_iter    *= DECIMAL_BASE; 
    f_epsilon *= DECIMAL_BASE; 
    //dprintf(STDERR_FILENO, "*f_iter = " "%Lf" "\n", (long double) f_iter); 
    //const uintmax_t f_iter_int = (uintmax_t) f_iter; 
    //const int digit = (int) floorf(f_iter); 
    //const uint8_t digit = f_iter_int; 
    const uint8_t digit = (uint8_t) f_iter; 
    //dprintf(STDERR_FILENO, "digit = " "%" __UINT8_FMTu__ "\n", digit); 
    all_digits_null_huh &= (0 == digit); 
    //dputs_array(STDERR_FILENO, __func__, ": ", "digit = ", int_string__stack(digit), "\n"); 
    (*d_r)[index] = digit; 
    f_iter -= digit; 
  }; 
  
  if (all_digits_null_huh) { 
    (*d_r)[DECIMAL_STATUS_INDEX] = (f_sign < 0) ? DECIMAL_STATUS__NEG_EPSILON : DECIMAL_STATUS__POS_EPSILON; 
  } 
  else { 
    (*d_r)[DECIMAL_STATUS_INDEX] = (f_sign < 0) ? DECIMAL_STATUS__NEG : DECIMAL_STATUS__POS; 
  }; 
  
  return DECIMAL__OK; 
}; 

RETURN_TYPE_T decimal__cast_from_double_r(decimal_env_t * this, decimal_t * d_r, const double f_given) { 
  const double  f_pos       = (f_given < 0) ? -f_given : f_given; 
  const int    f_pos_class = fpclassify(f_pos); 
  if (FP_ZERO     == f_pos_class) return decimal__zero_r(this, d_r); 
  const int8_t f_sign      = (f_given < 0) ? -1 : 1; 
  if (f_pos <= __DBL_EPSILON__) return (f_sign > 0) ? decimal__pos_epsilon_r(this, d_r) : decimal__neg_epsilon_r(this, d_r); 
  if (FP_INFINITE == f_pos_class) return (f_sign > 0) ? decimal__pos_infini_r(this, d_r) : decimal__neg_infini_r(this, d_r); 
  if (FP_NAN      == f_pos_class) return decimal__invalid_r(this, d_r); 
  
  assert(isfinite(f_pos)); 
  
  //dprintf(STDERR_FILENO, "f_pos = " "%Lf" "\n", (long double) f_pos); 
  const uintmax_t f_int_part = (uintmax_t) f_pos; 
  //dprintf(STDERR_FILENO, "f_int_part = " "%" __UINTMAX_FMTu__ "\n", f_int_part); 
  const int_decimal_error_t error_id = decimal__cast_from_uintmax_r(this, d_r, f_int_part); 
  if (error_id < 0) return error_id; 
  
  int8_t all_digits_null_huh = (0 == f_int_part); 

  double f_iter = f_pos - (double)f_int_part; 
  double f_epsilon = __DBL_EPSILON__; 
  int index = DECIMAL_INT_INDEX; 
  for (;;) { 
    //dprintf(STDERR_FILENO, "f_iter = " "%Lf" "\n", (long double) f_iter); 
    //dputs_array(STDERR_FILENO, __func__, ": ", "index = ", int_string__stack(index), "\n"); 
    if (FP_ZERO == fpclassify(f_iter)) break; 
    //if (f_iter <= __DBL_EPSILON__) break; 
    if (f_iter <= f_epsilon) break; 
    index--; 
    if (index < DECIMAL_DIGITS_INDEX_FIRST) break; 
    f_iter    *= DECIMAL_BASE; 
    f_epsilon *= DECIMAL_BASE; 
    //dprintf(STDERR_FILENO, "*f_iter = " "%Lf" "\n", (long double) f_iter); 
    //const uintmax_t f_iter_int = (uintmax_t) f_iter; 
    //const int digit = (int) floorf(f_iter); 
    //const uint8_t digit = f_iter_int; 
    const uint8_t digit = (uint8_t) f_iter; 
    //dprintf(STDERR_FILENO, "digit = " "%" __UINT8_FMTu__ "\n", digit); 
    all_digits_null_huh &= (0 == digit); 
    //dputs_array(STDERR_FILENO, __func__, ": ", "digit = ", int_string__stack(digit), "\n"); 
    (*d_r)[index] = digit; 
    f_iter -= digit; 
  }; 
  
  if (all_digits_null_huh) { 
    (*d_r)[DECIMAL_STATUS_INDEX] = (f_sign < 0) ? DECIMAL_STATUS__NEG_EPSILON : DECIMAL_STATUS__POS_EPSILON; 
  } 
  else { 
    (*d_r)[DECIMAL_STATUS_INDEX] = (f_sign < 0) ? DECIMAL_STATUS__NEG : DECIMAL_STATUS__POS; 
  }; 
  
  return DECIMAL__OK; 
}; 

RETURN_TYPE_T decimal__cast_from_long_double_r(decimal_env_t * this, decimal_t * d_r, const long double f_given) { 
  const long double  f_pos       = (f_given < 0) ? -f_given : f_given; 
  const int    f_pos_class = fpclassify(f_pos); 
  if (FP_ZERO     == f_pos_class) return decimal__zero_r(this, d_r); 
  const int8_t f_sign      = (f_given < 0) ? -1 : 1; 
  if (f_pos <= __LDBL_EPSILON__) return (f_sign > 0) ? decimal__pos_epsilon_r(this, d_r) : decimal__neg_epsilon_r(this, d_r); 
  if (FP_INFINITE == f_pos_class) return (f_sign > 0) ? decimal__pos_infini_r(this, d_r) : decimal__neg_infini_r(this, d_r); 
  if (FP_NAN      == f_pos_class) return decimal__invalid_r(this, d_r); 
  
  assert(isfinite(f_pos)); 
  
  //dprintf(STDERR_FILENO, "f_pos = " "%Lf" "\n", (long double) f_pos); 
  const uintmax_t f_int_part = (uintmax_t) f_pos; 
  //dprintf(STDERR_FILENO, "f_int_part = " "%" __UINTMAX_FMTu__ "\n", f_int_part); 
  const int_decimal_error_t error_id = decimal__cast_from_uintmax_r(this, d_r, f_int_part); 
  if (error_id < 0) return error_id; 
  
  int8_t all_digits_null_huh = (0 == f_int_part); 

  long double f_iter = f_pos - (long double)f_int_part; 
  long double f_epsilon = __LDBL_EPSILON__; 
  int index = DECIMAL_INT_INDEX; 
  for (;;) { 
    //dprintf(STDERR_FILENO, "f_iter = " "%Lf" "\n", (long double) f_iter); 
    //dputs_array(STDERR_FILENO, __func__, ": ", "index = ", int_string__stack(index), "\n"); 
    if (FP_ZERO == fpclassify(f_iter)) break; 
    //if (f_iter <= __LDBL_EPSILON__) break; 
    if (f_iter <= f_epsilon) break; 
    index--; 
    if (index < DECIMAL_DIGITS_INDEX_FIRST) break; 
    f_iter    *= DECIMAL_BASE; 
    f_epsilon *= DECIMAL_BASE; 
    //dprintf(STDERR_FILENO, "*f_iter = " "%Lf" "\n", (long double) f_iter); 
    //const uintmax_t f_iter_int = (uintmax_t) f_iter; 
    //const int digit = (int) floorf(f_iter); 
    //const uint8_t digit = f_iter_int; 
    const uint8_t digit = (uint8_t) f_iter; 
    //dprintf(STDERR_FILENO, "digit = " "%" __UINT8_FMTu__ "\n", digit); 
    all_digits_null_huh &= (0 == digit); 
    //dputs_array(STDERR_FILENO, __func__, ": ", "digit = ", int_string__stack(digit), "\n"); 
    (*d_r)[index] = digit; 
    f_iter -= digit; 
  }; 
  
  if (all_digits_null_huh) { 
    (*d_r)[DECIMAL_STATUS_INDEX] = (f_sign < 0) ? DECIMAL_STATUS__NEG_EPSILON : DECIMAL_STATUS__POS_EPSILON; 
  } 
  else { 
    (*d_r)[DECIMAL_STATUS_INDEX] = (f_sign < 0) ? DECIMAL_STATUS__NEG : DECIMAL_STATUS__POS; 
  }; 
  
  return DECIMAL__OK; 
}; 


#if 0 
static RETURN_TYPE_T decimal__cast_from_float_r__old001(decimal_env_t * this, decimal_t * d_r, const float f_given) { 
  if (0.0f == f_given) return decimal__zero_r(this, d_r); 
  const int8_t f_sign = (f_given < 0) ? -1 : 1; 
  const float  f_pos  = (f_given < 0) ? -f_given : f_given; 
  const float  ff = floorf(f_pos); 
  const int   n  = (f_given < 0) ? -(int) ff : (int) ff; 
  //dputs_array(STDERR_FILENO, __func__, ": ", "n = ", int_string__stack(n), "\n"); 
  int_decimal_error_t error_id; 
  error_id = decimal__cast_from_int_r(this, d_r, n); 
  if (error_id != DECIMAL__OK) return error_id; 

  //dputs_array(STDERR_FILENO, __func__, ": ", "HERE ", "\n"); 
  
  float f_iter = f_pos - ff; 
  int index = DECIMAL_INT_INDEX; 
  for (;;) { 
    //dputs_array(STDERR_FILENO, __func__, ": ", "index = ", int_string__stack(index), "\n"); 
    if (fpclassify(f_iter) == FP_ZERO) break; 
    index--; 
    if (index < DECIMAL_DIGITS_INDEX_FIRST) break; 
    f_iter *= DECIMAL_BASE; 
    const int digit = (int) floorf(f_iter); 
    //dputs_array(STDERR_FILENO, __func__, ": ", "digit = ", int_string__stack(digit), "\n"); 
    (*d_r)[index] = digit; 
    f_iter -= floorf(f_iter); 
  };
  
  if (0 == n && index < DECIMAL_INT_INDEX) { 
    (*d_r)[DECIMAL_STATUS_INDEX] = (f_given < 0) ? DECIMAL_STATUS__NEG : DECIMAL_STATUS__POS; 
  }; 
  
  return DECIMAL__OK; 
}; 
#endif 




#include "decimal_matrix_base_conversion.ci" 


extern RETURN_TYPE_T decimal__cast_from_string_int_r(decimal_env_t * this, decimal_t * d_r, const char * int_cstr, const uint8_t int_cstr_base) { 
  const unsigned char * p; 
  goto label__start; 

 label__exit_ok: { 
#ifdef RETURN_ERROR 
    return DECIMAL__OK; 
#else 
    return d_r; 
#endif 
  }; 

 error_label__first_digit_is_null: { 
    this -> error_id = DECIMAL__FIRST_DIGIT_IS_NULL; 
    snprintf(this -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "First digit of 'digits' array is null while it should not: %c (in: [%p] %s)", *p, int_cstr, int_cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 

  error_label__digits_len_is_null: {
    this -> error_id = DECIMAL__DIGITS_LEN_IS_NULL; 
    snprintf(this -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Digits len is null while it should not: %c (in: [%p] %s)", *p, int_cstr, int_cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  }; 

  error_label__unexpected_digit: {
    this -> error_id = DECIMAL__UNEXPECTED_DIGIT; 
    snprintf(this -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "String contains an unexpected digit: %c (in: [%p] %s)", *p, int_cstr, int_cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
    }; 

  error_label__only_neg_sign_cstr: { 
    this -> error_id = DECIMAL__ONLY_NEG_SIGN_CSTR; 
    snprintf(this -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "String contains only a negative sign: [%p] %s", int_cstr, int_cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
    }; 
    
  error_label__zero_base: { 
    this -> error_id = DECIMAL__NULL_BASE_CSTR; 
    snprintf(this -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Base of int-string is null: %u", int_cstr_base); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
    }; 
    
  error_label__null_cstr: { 
    this -> error_id = DECIMAL__NULL_CSTR; 
    snprintf(this -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "String is null: [%p]", int_cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  };

 error_label__empty_cstr: { 
    this -> error_id = DECIMAL__EMPTY_CSTR; 
    snprintf(this -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "String is empty: [%p] '%s'", int_cstr, int_cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  };

 error_label__only_white_spaces_cstr: { 
    this -> error_id = DECIMAL__ONLY_WHITE_SPACES_CSTR; 
    snprintf(this -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "String contains only white-spaces: [%p] '%s'", int_cstr, int_cstr); 
    if (this -> stdlog_d > 0) { dprintf(this -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, this -> error_str); }; 
    return this -> error_id; 
  };


  label__start: {}; 
  if (NULL == int_cstr) goto error_label__null_cstr; 
  if ('\0' == *int_cstr) goto error_label__empty_cstr; 
  if (0 == int_cstr_base) goto error_label__zero_base; 

  decimal__zero_r(this, d_r); 
 
  const size_t int_cstr_len = strlen(int_cstr); 
  uint8_t digits[int_cstr_len]; 
  size_t  digits_len = 0; 
  p = int_cstr; 
  
  // Skip whites-spaces if any. 
  while (' ' == *p) p++; 
  if ('\0' == *p) goto error_label__only_white_spaces_cstr;
  
  // Check if there is a sign character. 
  const int8_t negative_huh = ('-' == *p); 
  if (negative_huh) { 
    p++; 
    while (' ' == *p) p++; 
    if ('\0' == *p) goto error_label__only_neg_sign_cstr; 
  }; 
  
  // Skip the first zeroes (if any). 
  const int8_t has_leading_zeroes_huh = ('0' == *p); 
  if (has_leading_zeroes_huh) { 
    p++; 
    while ('0' == *p) p++; 
    if ('\0' == *p) goto label__exit_ok; 
  }; 

  
  
  if (int_cstr_base <= 10) goto label__regular_digits; 
  goto label__complicated_digits; 

  label__regular_digits: { 
    for (;;) { 
      const char c = *p; 
      if (c == ' ') { 
	p++; 
	while (' ' == *p) p++; 
	if ('\0' != *p) goto error_label__unexpected_digit; 
	break; 
      }; 
      if (c == '\0') break; 
      if (c < '0') goto error_label__unexpected_digit; 
      if (c > '9') goto error_label__unexpected_digit; 
      const uint8_t digit = c - '0'; 
      if (digit >= int_cstr_base) goto error_label__unexpected_digit; 
      //(*d_r)[DECIMAL_INT_INDEX] = digit; 
      *(digits + digits_len) = digit; 
      digits_len++; 
      p++; 
    }; 
    if (0 == digits_len) { 
      if (has_leading_zeroes_huh) { 
	digits[digits_len] = '0'; 
	digits_len++;
      };
    }; 

    goto label__digits_filled; 
  }; 
  
 label__complicated_digits: { 
    assert(false); 
  }; 


 label__digits_filled: { 
#if 1
    { 
      dputs_array(STDERR_FILENO, "DEBUG: ", "digits[", int_string__stack(digits_len), "] = ["); 
      for (uint8_t i = 0; i < digits_len; i++) { 
	dputs_array(STDERR_FILENO, int_string__stack(digits[i]), ", "); 
      }; 
      dputs_array(STDERR_FILENO, "]", "\n"); 
    }; 
#endif 
    if (0 == digits_len) goto error_label__digits_len_is_null; 
    if (0 == *digits) goto error_label__first_digit_is_null; 
    if (DECIMAL_BASE == int_cstr_base) goto label__bases_are_equal; 
    goto label__bases_are_different; 
    assert(false); 
  }; 
  
 label__bases_are_equal: { 
    if (digits_len > DECIMAL_INT_SIZE) { 
      (*d_r)[DECIMAL_STATUS_INDEX] = negative_huh ? DECIMAL_STATUS__NEG_INFINI : DECIMAL_STATUS__POS_INFINI; 
      goto label__exit_ok; 
    }; 
    for (uint8_t i = 0; i < digits_len; i++) { 
      (*d_r)[DECIMAL_INT_INDEX + i] = digits[digits_len - 1 - i]; 
    }; 
    (*d_r)[DECIMAL_STATUS_INDEX] = negative_huh ? DECIMAL_STATUS__NEG : DECIMAL_STATUS__POS; 
    goto label__exit_ok;     
  }; 


 label__bases_are_different: { 
    decimal__conversion_matrix_from_internal_base_to_printing_base__compute(this, /*printing_base*/int_cstr_base); 
    goto label__exit_ok; 
  }; 

  assert(false); 
}; 







#include "decimal_print.ci" 


#define DEBUG_LEVEL 0 
#define DEBUG_STATEMENT_DO(u) { u; }; 
#define DEBUG_STATEMENT_NOTHING(u) 
#if (DEBUG_LEVEL < 0) 
#  define DEBUG_STATEMENT_LEVEL_0 DEBUG_STATEMENT_NOTHING
#else 
#  define DEBUG_STATEMENT_LEVEL_0 DEBUG_STATEMENT_DO
#endif 
#if (DEBUG_LEVEL < 1) 
#  define DEBUG_STATEMENT_LEVEL_1 DEBUG_STATEMENT_NOTHING
#else 
#  define DEBUG_STATEMENT_LEVEL_1 DEBUG_STATEMENT_DO
#endif 
#if (DEBUG_LEVEL < 10) 
#  define DEBUG_STATEMENT_LEVEL_10 DEBUG_STATEMENT_NOTHING
#else 
#  define DEBUG_STATEMENT_LEVEL_10 DEBUG_STATEMENT_DO
#endif 
#if (DEBUG_LEVEL < 100) 
#  define DEBUG_STATEMENT_LEVEL_100 DEBUG_STATEMENT_NOTHING
#else 
#  define DEBUG_STATEMENT_LEVEL_100 DEBUG_STATEMENT_DO
#endif 
#if (DEBUG_LEVEL < 1000) 
#  define DEBUG_STATEMENT_LEVEL_1000 DEBUG_STATEMENT_NOTHING
#else 
#  define DEBUG_STATEMENT_LEVEL_1000 DEBUG_STATEMENT_DO
#endif 
#if (DEBUG_LEVEL < 10000) 
#  define DEBUG_STATEMENT_LEVEL_10000 DEBUG_STATEMENT_NOTHING
#else 
#  define DEBUG_STATEMENT_LEVEL_10000 DEBUG_STATEMENT_DO
#endif 

#define DEBUG_STATEMENT(l,u) DEBUG_STATEMENT_LEVEL_##l(u)


#include "decimal_inc_and_dec.ci" 

#include "decimal_shift.ci" 

#include "decimal_tilde.ci" 

#include "decimal_add.ci" 

#include "decimal_sub_and_neg.ci" 

#include "decimal_mult.ci" 

#include "decimal_div.ci" 



// ============================================= 
#if 0 
#endif 

#include "decimal_tests.ci" 



