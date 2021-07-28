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
  
}; 

enum { DECIMAL_ENV__SIZEOF__E = sizeof(struct decimal_env_t) }; 
const uint16_t decimal_env__sizeof = sizeof(struct decimal_env_t); 

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

static void decimal_mantisse__set_eof_r(decimal_t * d_r) { 
  for (int i = DECIMAL_DIGITS_INDEX; i < DECIMAL_DIGITS_INDEX_XLAST; i++) { 
    (*d_r)[i] = DECIMAL_EOF_BYTE; 
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

RETURN_TYPE_T decimal__reset_r(decimal_env_t * decimal_env, decimal_t * d_r) { 
  decimal_mantisse__set_eof_r(d_r); 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

extern RETURN_TYPE_T decimal__zero_r(decimal_env_t * this, decimal_t * d_r) {
  decimal_mantisse__set_eof_r(d_r); 
  (*d_r)[DECIMAL_INT_INDEX] = 0; 
  (*d_r)[DECIMAL_STATUS_INDEX] = DECIMAL_STATUS__ZERO; 
#ifdef RETURN_ERROR 
  return DECIMAL__OK; 
#else 
  return d_r; 
#endif 
}; 

//RETURN_TYPE_T decimal__make_int_r(decimal_t * d_r, const int n_given) { 
RETURN_TYPE_T decimal__cast_from_int_r(decimal_env_t * decimal_env, decimal_t * d_r, const int n_given) { 
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


RETURN_TYPE_T decimal__cast_from_float_r(decimal_env_t * this, decimal_t * d_r, const float f_given) { 
  const float f  = (f_given < 0) ? -f_given : f_given; 
  const float ff = floorf(f); 
  const int   n  = (f_given < 0) ? -(int) ff : (int) ff; 
  //dputs_array(STDERR_FILENO, __func__, ": ", "n = ", int_string__stack(n), "\n"); 
  int_decimal_error_t error_id; 
  error_id = decimal__cast_from_int_r(this, d_r, n); 
  if (error_id != DECIMAL__OK) return error_id; 

  //dputs_array(STDERR_FILENO, __func__, ": ", "HERE ", "\n"); 
  
  float f_iter = f - ff; 
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



