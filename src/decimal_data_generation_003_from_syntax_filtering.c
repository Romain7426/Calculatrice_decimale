#include "decimal_global.h"
#include "decimal.h"
#include "decimal_token.h"
#include "decimal_token_type.h"
//#include "decimal_token_input_buffering.h"
//#include "decimal_token_parser.h"
#include "decimal_syntax_filtering_engine.h"
#include "decimal_data_generation_003_from_syntax_filtering.h"
#include "decimal_bytecode_type.h" 


#define GET_CURRENT_TOKEN_R() {						\
    error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 

#define MOVE_TO_NEXT_TOKEN_R() {						\
    error_id = decimal_syntax_filtering__move_to_next_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 


static uint16_t const_string__push(char * const_string_array, const uint16_t const_string_sizeof, uint16_t * const_string_len_r, const char * cstr) { 
  if (NULL == cstr) return 0; 
  if (*cstr == '\0') return 0; 
  const int cstr_sizeof = 1 + strlen(cstr); 
  uint16_t const_string_len = *const_string_len_r; 
  const uint16_t available_sizeof = const_string_sizeof - const_string_len; 
  if (cstr_sizeof >= available_sizeof) { 
    return UINT16_MAX; 
  }; 
  bcopy(cstr, const_string_array + const_string_len, cstr_sizeof); 
  *const_string_len_r += cstr_sizeof; 
  return const_string_len; 
}; 

static int_decimal_error_t decimal_bytecode__push_bytecode(uint8_t * bytecode_data, const uint16_t bytecode_size, uint16_t * bytecode_len_r, const int_decimal_bytecode_type_t bytecode_type, const int stdlog_d) { 
  const uint16_t bytecode_len = *bytecode_len_r; 
  const uint16_t available_sizeof = bytecode_size - bytecode_len; 
  const uint16_t needed_sizeof = sizeof(int_decimal_bytecode_type_t); 
  if (needed_sizeof > available_sizeof) goto label__error__not_enough_available_space; 
  *((int_decimal_bytecode_type_t *)(((uint8_t *)bytecode_data) + bytecode_len)) = bytecode_type; 
  *bytecode_len_r += sizeof(int_decimal_bytecode_type_t); 
  return DECIMAL__OK; 
  
  assert(false); 
  
 label__error__not_enough_available_space: { 
    const char error_str[] = "Not enough space available in the bytecode array to push the bytecode"; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
    return DECIMAL__BYTECODE_GENERATION__NOT_ENOUGH_AVAILABLE_SPACE; 
  }; 
  
  assert(false); 
}; 

static int_decimal_error_t decimal_bytecode__push_uint16(uint8_t * bytecode_data, const uint16_t bytecode_size, uint16_t * bytecode_len_r, const uint16_t int_data, const int stdlog_d) { 
  const uint16_t bytecode_len = *bytecode_len_r; 
  const uint16_t available_sizeof = bytecode_size - bytecode_len; 
  const uint16_t needed_sizeof = sizeof(uint16_t); 
  if (needed_sizeof > available_sizeof) goto label__error__not_enough_available_space; 
  *((uint16_t *)(((uint8_t *)bytecode_data) + bytecode_len)) = int_data; 
  *bytecode_len_r += sizeof(uint16_t); 
  return DECIMAL__OK; 
  
  assert(false); 
  
 label__error__not_enough_available_space: { 
    const char error_str[] = "Not enough space available in the bytecode array to push the bytecode"; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: Error: " "%s" "\n", __func__, error_str); }; 
    return DECIMAL__BYTECODE_GENERATION__NOT_ENOUGH_AVAILABLE_SPACE; 
  }; 
  
  assert(false); 
}; 

static int_decimal_error_t decimal_bytecode__read_postfix_tokens(decimal_syntax_filtering_t * this, decimal_token_env_t * token_env, uint8_t * bytecode_data, const uint16_t bytecode_size, uint16_t * bytecode_len_r, char * const_string_array, const uint16_t const_string_sizeof, uint16_t * const_string_len_r, const int stduser_d, const int stdlog_d) { 
  // That function assumes that tokens are postfixly ordered. 
  if (NULL ==               this) { return DECIMAL__DATA_GENERATION__NULL_SYNTAX_FILTERING  ; }; 
  if (NULL ==          token_env) { return DECIMAL__DATA_GENERATION__NULL_TOKEN_ENV         ; }; 
  if (NULL ==      bytecode_data) { return DECIMAL__DATA_GENERATION__NULL_BYTECODE_DATA     ; }; 
  if (NULL ==     bytecode_len_r) { return DECIMAL__DATA_GENERATION__NULL_BYTECODE_LEN_R    ; }; 
  if (NULL == const_string_array) { return DECIMAL__DATA_GENERATION__NULL_CONST_STRING_ARRAY; }; 
  if (NULL == const_string_len_r) { return DECIMAL__DATA_GENERATION__NULL_CONST_STRING_LEN_R; }; 
  
  int_decimal_error_t error_id;
  char error_str[256]; 
  enum { error_size = sizeof(error_str) }; 
  
  //uint16_t bytecode_len = *bytecode_len_r; 
  
  int_decimal_token_t token_i; 
  //const int_decimal_token_t token_nb = decimal_token__get_count(token_env); 
  
  GET_CURRENT_TOKEN_R(); 
  
  for (;;) { 
    const int_decimal_token_type_t token_type = decimal_token__get_type(token_env, token_i); 
    //dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, decimal_token__type_get_cstr(token_type)); 

    switch (token_type) { 
    case DECIMAL_TOKEN_ENTIER    : goto label__push_entier_from_string; 
    case DECIMAL_TOKEN_REEL__VIRG: goto label__push_reel_virg_from_string; 
    case DECIMAL_TOKEN_REEL__DOT : goto label__push_reel_dot_from_string; 
    case DECIMAL_TOKEN_REEL__E   : goto label__push_reel_e_from_string; 
      
    case DECIMAL_TOKEN_IPLUS_UNAIRE: goto label__push_plus_unaire; 
    case DECIMAL_TOKEN_RPLUS_UNAIRE: goto label__push_plus_unaire; 
      
    case DECIMAL_TOKEN_IMOINS_UNAIRE: goto label__push_moins_unaire;  
    case DECIMAL_TOKEN_RMOINS_UNAIRE: goto label__push_moins_unaire;  
      
    case DECIMAL_TOKEN_IPLUS: goto label__push_plus_binaire; 
    case DECIMAL_TOKEN_RPLUS: goto label__push_plus_binaire; 
      
    case DECIMAL_TOKEN_IMOINS: goto label__push_moins_binaire; 
    case DECIMAL_TOKEN_RMOINS: goto label__push_moins_binaire; 
      
    case DECIMAL_TOKEN_IMULT: goto label__push_mult_binaire; 
    case DECIMAL_TOKEN_RMULT: goto label__push_mult_binaire; 
      
    case DECIMAL_TOKEN_RDIV: goto label__push_div_binaire; 
      
    default: goto error_label__unexpected_token; 
    }; 
    
    assert(false); 

  completed_huh: { 
      //if (decimal_syntax_filtering__lalr_mode_completed_huh(this)) goto completed; 
      MOVE_TO_NEXT_TOKEN_R(); 
      if (decimal_syntax_filtering__lalr_mode_read_all_huh(this)) goto all_was_read; // Exit the loop. 
      continue; 
    }; 

    assert(false); 

#define PUSH_BYTECODE(__bytecode__) {					\
      error_id = decimal_bytecode__push_bytecode(bytecode_data, bytecode_size, bytecode_len_r, (__bytecode__), stdlog_d); \
      if (error_id != DECIMAL__OK) { goto label__error__error_in_bytecode_generation; }; \
    }; 

#define PUSH_UINT16(__uint16_data__) {					\
      error_id = decimal_bytecode__push_uint16(bytecode_data, bytecode_size, bytecode_len_r, (__uint16_data__), stdlog_d); \
      if (error_id != DECIMAL__OK) { goto label__error__error_in_bytecode_generation; }; \
    }; 

  label__push_entier_from_string: { 
      const char *   srcval = decimal_token__get_srcval_cstr(token_env, token_i); 
      const uint16_t str_id = const_string__push(const_string_array, const_string_sizeof, const_string_len_r, srcval); 
      PUSH_BYTECODE(DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__INT); 
      PUSH_UINT16(str_id); 
      goto completed_huh; 
    }; 
    
  label__push_reel_virg_from_string: { 
      const char * srcval = decimal_token__get_srcval_cstr(token_env, token_i); 
      const uint16_t str_id = const_string__push(const_string_array, const_string_sizeof, const_string_len_r, srcval); 
      PUSH_BYTECODE(DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__FLOAT_V); 
      PUSH_UINT16(str_id); 
      goto completed_huh; 
    }; 

  label__push_reel_dot_from_string: { 
      const char * srcval = decimal_token__get_srcval_cstr(token_env, token_i); 
      const uint16_t str_id = const_string__push(const_string_array, const_string_sizeof, const_string_len_r, srcval); 
      PUSH_BYTECODE(DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__FLOAT_D); 
      PUSH_UINT16(str_id); 
      goto completed_huh; 
    }; 

  label__push_reel_e_from_string: { 
      const char * srcval = decimal_token__get_srcval_cstr(token_env, token_i); 
      const uint16_t str_id = const_string__push(const_string_array, const_string_sizeof, const_string_len_r, srcval); 
      PUSH_BYTECODE(DECIMAL__BYTECODE__PUSH_FROM_CONST_STRING__FLOAT_E); 
      PUSH_UINT16(str_id); 
      goto completed_huh; 
    }; 

  label__push_plus_unaire: { 
      // Do nothing. 
      goto completed_huh; 
    }; 

  label__push_moins_unaire: { 
      PUSH_BYTECODE(DECIMAL__BYTECODE__NEG); 
      goto completed_huh; 
    }; 

  label__push_plus_binaire: { 
      // As we are postfix, the two operands are on the top of the stack. 
      PUSH_BYTECODE(DECIMAL__BYTECODE__ADD); 
      goto completed_huh; 
    }; 

  label__push_moins_binaire: { 
      // As we are postfix, the two operands are on the top of the stack. 
      PUSH_BYTECODE(DECIMAL__BYTECODE__SUB); 
      goto completed_huh; 
    }; 

  label__push_mult_binaire: { 
      // As we are postfix, the two operands are on the top of the stack. 
      PUSH_BYTECODE(DECIMAL__BYTECODE__MULT); 
      goto completed_huh; 
    }; 

  label__push_div_binaire: { 
      // As we are postfix, the two operands are on the top of the stack. 
      PUSH_BYTECODE(DECIMAL__BYTECODE__DIV); 
      goto completed_huh; 
    }; 
    
    assert(false); 
  }; // for (;;) 
  
  
 all_was_read: 
  //*bytecode_len_r = bytecode_len; 
  //PUSH_BYTECODE(DECIMAL__BYTECODE__HALT); 
  return DECIMAL__OK; 
  
  assert(false);   
  
 
 label__error__error_in_bytecode_generation: { 
    return error_id; 
  }; 
  
  assert(false);   
  
 error_label__error_in_syntax_filtering: { 
    //dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, "error_label__error_in_syntax_filtering"); 
    //strlcpy(error_str, decimal_syntax_filtering__error_str(this), error_size); 
    const char * this_error_str = decimal_syntax_filtering__error_str(this); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", this_error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, this_error_str); }; 
    return error_id; 
  }; 
  
  assert(false);   
  
 error_label__unexpected_token: { 
    error_id = DECIMAL__DATA_GENERATION__STACK_UNEXPECTED_TOKEN; 
    const int_decimal_token_type_t token_type = decimal_token__get_type(token_env, token_i); 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: Unexpected token %s", decimal_token__type_get_cstr(token_type)); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return error_id; 
  }; 
  
  assert(false);   
  
}; 


#if 0 
enum { EXPR_STACK_SIZE = DECIMAL__EXPRESSION_NESTEDNESS_MAX }; 

// That function actually computes. I want a function that produces bytecode. 
static int_decimal_error_t decimal_data__read_postfix_float(int_decimal_error_t * error_id_r, const uint16_t error_size, char * error_str, const int stdlog_d, decimal_syntax_filtering_t * this, decimal_token_env_t * token_env, float * floatval_r, const int stduser_d) { 
  if (NULL == error_id_r) { return DECIMAL__DATA_GENERATION__NULL_ERROR_ID_R; }; 
  if (1     > error_size) { *error_id_r = DECIMAL__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1; return *error_id_r; }; 
  if (NULL ==       this) { *error_id_r = DECIMAL__DATA_GENERATION__NULL_SYNTAX_FILTERING; snprintf(error_str, error_size, "syntax_filtering argument is null."); return *error_id_r; }; 
  if (NULL ==  token_env) { *error_id_r = DECIMAL__DATA_GENERATION__NULL_TOKEN_ENV       ; snprintf(error_str, error_size, "token_env argument is null."); return *error_id_r; }; 
  if (NULL == floatval_r) { *error_id_r = DECIMAL__DATA_GENERATION__NULL_FLOATVAL_R      ; snprintf(error_str, error_size, "floatval_r argument is null."); return *error_id_r; }; 
  
  float stack__array[EXPR_STACK_SIZE]; 
  int   stack__nb; 
  stack__nb = 0; 
  
  int_decimal_token_t token_i; 
  //const int_decimal_token_t token_nb = decimal_token__get_count(token_env); 
  
  GET_CURRENT_TOKEN_R(); 
  
  for (;;) { 
    const int_decimal_token_type_t token_type = decimal_token__get_type(token_env, token_i); 
    //dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, decimal_token__type_get_cstr(token_type)); 
    switch (token_type) { 
    case DECIMAL_TOKEN_ENTIER: 
    case DECIMAL_TOKEN_REEL__VIRG: 
    case DECIMAL_TOKEN_REEL__DOT: 
    case DECIMAL_TOKEN_REEL__E: { 
      const char * srcval = decimal_token__get_srcval_cstr(token_env, token_i); 
      if (stack__nb >= EXPR_STACK_SIZE) { goto error_label__stack_overflow; }; 
      stack__array[stack__nb] = (atof(srcval)); 
#if 0 
      dprintf(stderr_d, "srcval = %s" "\n", srcval); 
      dprintf(stderr_d, "stack__array[%d] = %f" "\n", stack__nb, stack__array[stack__nb]); 
#endif 
      stack__nb++; 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IPLUS_UNAIRE: 
    case DECIMAL_TOKEN_RPLUS_UNAIRE: 
      goto completed_huh; 
      
    case DECIMAL_TOKEN_IMOINS_UNAIRE: 
    case DECIMAL_TOKEN_RMOINS_UNAIRE: { 
      if (stack__nb < 1) { goto error_label__stack_underflow; }; 
      const int stack__i = stack__nb - 1; 
#if 0 
      dprintf(stderr_d, "stack__array[%d] = %f" "\n", stack__i, stack__array[stack__i]); 
#endif 
      stack__array[stack__i] = - stack__array[stack__i]; 
#if 0 
      dprintf(stderr_d, "stack__array[%d] = %f" "\n", stack__i, stack__array[stack__i]); 
#endif 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IPLUS: 
    case DECIMAL_TOKEN_RPLUS: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const float op_left  = stack__array[stack__nb - 2]; 
      const float op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left + op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IMOINS: 
    case DECIMAL_TOKEN_RMOINS: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const float op_left  = stack__array[stack__nb - 2]; 
      const float op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left - op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IMULT: 
    case DECIMAL_TOKEN_RMULT: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const float op_left  = stack__array[stack__nb - 2]; 
      const float op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left * op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_RDIV: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const float op_left  = stack__array[stack__nb - 2]; 
      const float op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left / op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    default: goto error_label__unexpected_token; 
    }; 
    
  completed_huh: 
    //if (decimal_syntax_filtering__lalr_mode_completed_huh(this)) goto completed; 
    MOVE_TO_NEXT_TOKEN_R(); 
    if (decimal_syntax_filtering__lalr_mode_read_all_huh(this)) goto all_was_read; 
  }; 
  
 //completed: 
 all_was_read: 
#if 0 
      dprintf(stderr_d, "stack__nb = %d" "\n", stack__nb); 
#endif 
  if (stack__nb < 1) { goto error_label__stack_not_enough_items; }; 
  if (stack__nb > 1) { goto error_label__stack_too_many_items  ; }; 
  *floatval_r  = stack__array[0]; 
#if 0 
      dprintf(stderr_d, "stack__array[0] = %f" "\n", stack__array[0]); 
      dprintf(stderr_d, "*floatval_r     = %f" "\n", *floatval_r); 
#endif 
  *error_id_r  = DECIMAL__OK; 
  *error_str   = '\0'; 
  return *error_id_r; 
  
  
  
 error_label__error_in_syntax_filtering: { 
    //dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, "error_label__error_in_syntax_filtering");  
    strlcpy(error_str, decimal_syntax_filtering__error_str(this), error_size); 
    return *error_id_r; 
  }; 
  
 error_label__stack_too_many_items: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_TOO_MANY_ITEMS; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: No value to return as there is nothing on the stack"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
 error_label__stack_not_enough_items: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_NOT_ENOUGH_ITEMS; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: No value to return as there is nothing on the stack"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__stack_overflow: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_OVERFLOW; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: Stack underflow"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__stack_underflow: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_UNDERFLOW; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: Stack underflow"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
 
 error_label__unexpected_token: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_UNEXPECTED_TOKEN; 
    const int_decimal_token_type_t token_type = decimal_token__get_type(token_env, token_i); 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Float stack]: Unexpected token %s", decimal_token__type_get_cstr(token_type)); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
}; 
#endif 

#if 0 
static int_decimal_error_t decimal_data__read_postfix_entier(int_decimal_error_t * error_id_r, const uint16_t error_size, char * error_str, const int stdlog_d, decimal_syntax_filtering_t * this, decimal_token_env_t * token_env, int * intval_r, const int stduser_d) { 
  if (NULL == error_id_r) { return DECIMAL__DATA_GENERATION__NULL_ERROR_ID_R; }; 
  if (1     > error_size) { *error_id_r = DECIMAL__DATA_GENERATION__ERROR_SIZE_LOWER_THAN_1; return *error_id_r; }; 
  if (NULL ==       this) { *error_id_r = DECIMAL__DATA_GENERATION__NULL_SYNTAX_FILTERING; snprintf(error_str, error_size, "syntax_filtering argument is null."); return *error_id_r; }; 
  if (NULL ==  token_env) { *error_id_r = DECIMAL__DATA_GENERATION__NULL_TOKEN_ENV       ; snprintf(error_str, error_size, "token_env argument is null."); return *error_id_r; }; 
  if (NULL ==   intval_r) { *error_id_r = DECIMAL__DATA_GENERATION__NULL_INTVAL_R        ; snprintf(error_str, error_size, "intval_r argument is null."); return *error_id_r; }; 

  
  int stack__array[EXPR_STACK_SIZE]; 
  int stack__nb; 
  stack__nb = 0; 
  
  int_decimal_token_t token_i; 
  //const int_decimal_token_t token_nb = decimal_token__get_count(token_env); 
  
  GET_CURRENT_TOKEN_R(); 
  
  for (;;) { 
    const int_decimal_token_type_t token_type = decimal_token__get_type(token_env, token_i); 
    //dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, decimal_token__type_get_cstr(token_type)); 
    switch (token_type) { 
    case DECIMAL_TOKEN_ENTIER: 
    case DECIMAL_TOKEN_REEL__VIRG: 
    case DECIMAL_TOKEN_REEL__DOT: 
    case DECIMAL_TOKEN_REEL__E: { 
      const char * srcval = decimal_token__get_srcval_cstr(token_env, token_i); 
      if (stack__nb >= EXPR_STACK_SIZE) { goto error_label__stack_overflow; }; 
      stack__array[stack__nb] = (atoi(srcval)); 
#if 0 
      dprintf(stderr_d, "srcval = %s" "\n", srcval); 
      dprintf(stderr_d, "stack__array[%d] = %d" "\n", stack__nb, stack__array[stack__nb]); 
#endif 
      stack__nb++; 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IPLUS_UNAIRE: 
    case DECIMAL_TOKEN_RPLUS_UNAIRE: 
      goto completed_huh; 

    case DECIMAL_TOKEN_IMOINS_UNAIRE: 
    case DECIMAL_TOKEN_RMOINS_UNAIRE: { 
      if (stack__nb < 1) { goto error_label__stack_underflow; }; 
      const int stack__i = stack__nb - 1; 
#if 0 
      dprintf(stderr_d, "stack__array[%d] = %d" "\n", stack__i, stack__array[stack__i]); 
#endif 
      stack__array[stack__i] = - stack__array[stack__i]; 
#if 0 
      dprintf(stderr_d, "stack__array[%d] = %d" "\n", stack__i, stack__array[stack__i]); 
#endif 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IPLUS: 
    case DECIMAL_TOKEN_RPLUS: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left + op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IMOINS: 
    case DECIMAL_TOKEN_RMOINS: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left - op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IMULT: 
    case DECIMAL_TOKEN_RMULT: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left * op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IDIV: 
    case DECIMAL_TOKEN_RDIV: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left / op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    case DECIMAL_TOKEN_IMOD: { 
      if (stack__nb < 2) { goto error_label__stack_underflow; }; 
      const int op_left  = stack__array[stack__nb - 2]; 
      const int op_right = stack__array[stack__nb - 1]; 
      stack__array[stack__nb - 2] = op_left % op_right; 
      stack__nb--; 
      goto completed_huh; 
    }; 
      
    default: goto error_label__unexpected_token; 
    }; 
    
  completed_huh: 
    //if (decimal_syntax_filtering__lalr_mode_completed_huh(this)) goto completed; 
    MOVE_TO_NEXT_TOKEN_R(); 
    if (decimal_syntax_filtering__lalr_mode_read_all_huh(this)) goto all_was_read; 
  }; 
  
 //completed: 
 all_was_read: 
#if 0 
      dprintf(stderr_d, "stack__nb = %d" "\n", stack__nb); 
#endif 
  if (stack__nb < 1) { goto error_label__stack_not_enough_items; }; 
  if (stack__nb > 1) { goto error_label__stack_too_many_items  ; }; 
  *intval_r  = stack__array[0]; 
#if 0 
      dprintf(stderr_d, "stack__array[0] = %d" "\n", stack__array[0]); 
      dprintf(stderr_d, "*intval_r       = %d" "\n", *intval_r); 
#endif 
  *error_id_r  = DECIMAL__OK; 
  *error_str   = '\0'; 
  return *error_id_r; 
  
  
  
 error_label__error_in_syntax_filtering: { 
    //dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, "error_label__error_in_syntax_filtering");  
    strlcpy(error_str, decimal_syntax_filtering__error_str(this), error_size); 
    return *error_id_r; 
  }; 
  
 error_label__stack_too_many_items: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_TOO_MANY_ITEMS; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: No value to return as there is nothing on the stack"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
 error_label__stack_not_enough_items: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_NOT_ENOUGH_ITEMS; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: No value to return as there is nothing on the stack"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__stack_overflow: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_OVERFLOW; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: Stack underflow"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 

 error_label__stack_underflow: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_UNDERFLOW; 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: Stack underflow"); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
 
 error_label__unexpected_token: { 
    *error_id_r = DECIMAL__DATA_GENERATION__STACK_UNEXPECTED_TOKEN; 
    const int_decimal_token_type_t token_type = decimal_token__get_type(token_env, token_i); 
    const int error_location_len = snprintf(error_str, error_size, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(error_size - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, error_size - error_location_written_len, "[Int stack]: Unexpected token %s", decimal_token__type_get_cstr(token_type)); 
    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return *error_id_r; 
  }; 
  
}; 
#endif 






#define MOVE_TO_NEXT_TOKEN() {						\
    error_id = decimal_syntax_filtering__move_to_next_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 
 
#define GET_CURRENT_TOKEN() {						\
    error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 

#define SWITCH_TO_LALR_MODE() {						\
    error_id = decimal_syntax_filtering__switch_to_lalr_mode(this); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
  }; 


#define CHECK_IDENT(_ident_) {						\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    srcval     = decimal_token__get_srcval_cstr(token_env, token_i);	\
    if (DECIMAL_TOKEN_IDENT != token_type)    { error__expected_token_type  = DECIMAL_TOKEN_IDENT; goto error_label__non_matching_token_type;   }; \
    if (0 != strcasecmp((_ident_), srcval)) { error__expected_token_value = (_ident_);         goto error_label__non_matching_token_value;  }; \
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define CHECK_SUGAR(_expected_token_type_) {				\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    if ((_expected_token_type_) != token_type) { error__expected_token_type = (_expected_token_type_); goto error_label__non_matching_token_type; }; \
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define LOOKAHEAD_THEN_READ_SIGN() {					\
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    srcval     = decimal_token__get_srcval_cstr(token_env, token_i);	\
    int move_forward_huh = false;					\
    if      (DECIMAL_TOKEN_IMOINS        == token_type) { signval = -1; move_forward_huh = true; } \
    else if (DECIMAL_TOKEN_RMOINS        == token_type) { signval = -1; move_forward_huh = true; } \
    else if (DECIMAL_TOKEN_IMOINS_UNAIRE == token_type) { signval = -1; move_forward_huh = true; } \
    else if (DECIMAL_TOKEN_RMOINS_UNAIRE == token_type) { signval = -1; move_forward_huh = true; } \
    else { signval = 1; };						\
    if (move_forward_huh) {						\
      MOVE_TO_NEXT_TOKEN();						\
    };									\
  }; 

#define READ_FLOAT() {							\
    error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    srcval     = decimal_token__get_srcval_cstr(token_env, token_i);	\
    if      (DECIMAL_TOKEN_ENTIER     == token_type) { floatval = (float) (atoi(srcval)); } \
    else if (DECIMAL_TOKEN_REEL__VIRG == token_type) { floatval = (float) (atof(srcval)); } \
    else if (DECIMAL_TOKEN_REEL__DOT  == token_type) { floatval = (float) (atof(srcval)); } \
    else if (DECIMAL_TOKEN_REEL__E    == token_type) { floatval = (float) (atof(srcval)); } \
    else { error__expected_token_type = DECIMAL_TOKEN_REEL__DOT; goto error_label__non_matching_token_type; }; \
    if (signval < 0) floatval = -floatval;				\
    MOVE_TO_NEXT_TOKEN();						\
  };

#define READ_LALR_FLOAT() {						\
    SWITCH_TO_LALR_MODE();						\
    error_id = decimal_data__read_postfix_float(&decimal_data -> error_id, decimal_data -> error_size, decimal_data -> error_str, decimal_data -> stdlog_d, this, token_env, &floatval, stduser_d); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_postfix_computation; }; \
    /*dprintf(stderr_d, "floatval = %f" "\n", floatval);*/		\
    GET_CURRENT_TOKEN();						\
  }; 

#define READ_ENTIER() {							\
    error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    srcval     = decimal_token__get_srcval_cstr(token_env, token_i);	\
    if      (DECIMAL_TOKEN_ENTIER     == token_type) { intval =       (atoi(srcval)); } \
    else if (DECIMAL_TOKEN_REEL__VIRG == token_type) { intval = (int) (atof(srcval)); } \
    else if (DECIMAL_TOKEN_REEL__DOT  == token_type) { intval = (int) (atof(srcval)); } \
    else if (DECIMAL_TOKEN_REEL__E    == token_type) { intval = (int) (atof(srcval)); } \
    else { error__expected_token_type = DECIMAL_TOKEN_ENTIER; goto error_label__non_matching_token_type; }; \
    if (signval < 0) intval = -intval;					\
    MOVE_TO_NEXT_TOKEN();						\
  };

#define READ_LALR_ENTIER() {						\
    SWITCH_TO_LALR_MODE();						\
    error_id = decimal_data__read_postfix_entier(&decimal_data -> error_id, decimal_data -> error_size, decimal_data -> error_str, decimal_data -> stdlog_d, this, token_env, &intval, stduser_d); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_postfix_computation; }; \
    /*dprintf(stderr_d, "intval = %d" "\n", intval);*/			\
    GET_CURRENT_TOKEN();						\
  }; 

#define READ_BOOLEEN() {						\
    error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    srcval     = decimal_token__get_srcval_cstr(token_env, token_i);	\
    if      (DECIMAL_TOKEN_TRUE       == token_type) { boolval =                 true; } \
    else if (DECIMAL_TOKEN_FALSE      == token_type) { boolval =                false; } \
    else if (DECIMAL_TOKEN_ENTIER     == token_type) { boolval =       (atoi(srcval)); } \
    else if (DECIMAL_TOKEN_REEL__VIRG == token_type) { boolval = (int) (atof(srcval)); } \
    else if (DECIMAL_TOKEN_REEL__DOT  == token_type) { boolval = (int) (atof(srcval)); } \
    else if (DECIMAL_TOKEN_REEL__E    == token_type) { boolval = (int) (atof(srcval)); } \
    else if (DECIMAL_TOKEN_IDENT      == token_type) {			\
      if      ((0 == strcasecmp("vrai", srcval)) || (0 == strcasecmp("true" , srcval))) { boolval =  true; } \
      else if ((0 == strcasecmp("faux", srcval)) || (0 == strcasecmp("false", srcval))) { boolval = false; } \
      else { goto error_label__expecting_boolean; };			\
    }									\
    else { goto error_label__expecting_boolean; };			\
    MOVE_TO_NEXT_TOKEN();						\
  };

#define READ_IDENT() {							\
    error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    srcval     = decimal_token__get_srcval_cstr(token_env, token_i);	\
    if (DECIMAL_TOKEN_IDENT != token_type) { error__expected_token_type = DECIMAL_TOKEN_IDENT; goto error_label__non_matching_token_type; }; \
    identval = srcval;							\
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define READ_STRING() {							\
    error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    srcval     = decimal_token__get_srcval_cstr(token_env, token_i);	\
    if (DECIMAL_TOKEN_STRING_C != token_type) { error__expected_token_type = DECIMAL_TOKEN_STRING_C; goto error_label__non_matching_token_type; }; \
    strval = srcval;							\
    MOVE_TO_NEXT_TOKEN();						\
  }; 

#define LOOKAHEAD_IDENT(_ident_) {					\
    error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    srcval     = decimal_token__get_srcval_cstr(token_env, token_i);	\
    lookahead_match_huh = (DECIMAL_TOKEN_IDENT == token_type) && (0 == strcasecmp((_ident_), srcval)); \
  }; 

#define LOOKAHEAD_SUGAR(_expected_token_type_) {			\
    error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); \
    if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; \
    if (token_i >= token_nb) { goto error_label__not_enough_tokens; };	\
    token_type = decimal_token__get_type       (token_env, token_i);	\
    lookahead_match_huh = ((_expected_token_type_) == token_type);	\
  }; 

 


int_decimal_error_t decimal_data_generation_003_from_syntax_filtering(decimal_token_env_t * token_env, uint8_t * directive_or_expr_huh_r, uint8_t * bytecode_data, const uint16_t bytecode_size, uint16_t * bytecode_len_r, char * const_string_array, const uint16_t const_string_sizeof, const int stduser_d, const int stdlog_d) { 
  if (NULL ==               token_env) { return DECIMAL__DATA_GENERATION__NULL_TOKEN_ENV   ; }; 
  if (NULL == directive_or_expr_huh_r) { return DECIMAL__DATA_GENERATION__NULL_DIRECTIVE_OR_EXPR_HUH_R; }; 
  if (NULL ==           bytecode_data) { return DECIMAL__DATA_GENERATION__NULL_BYTECODE_DATA; }; 
  if (NULL ==          bytecode_len_r) { return DECIMAL__DATA_GENERATION__NULL_BYTECODE_LEN_R; }; 
  *directive_or_expr_huh_r = false; 
  int_decimal_error_t error_id; 
  error_id = DECIMAL__DATA_GENERATION__ERROR_ID_NOT_ASSIGNED; 
  char error_str[DECIMAL_ENV__ERROR_BUFFER_SIZE]; 
  enum { error_size = sizeof(error_str) }; 
  //const uint8_t error_size = sizeof(error_str); 
  int_decimal_token_t token_i = 0; 
  goto label__start; 

 label__exit: { 
    return error_id; 
  }; 

 error_label__error_in_syntax_filtering: { 
#if 0 
    dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, "error_label__error_in_syntax_filtering"); 
    dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, decimal_syntax_filtering__error_str(this)); 
#endif 
    //decimal_data -> error_id = error_id; 
    //strlcpy(decimal_data -> error_str, decimal_syntax_filtering__error_str(this), decimal_data -> error_size); 
#if 0 
    dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%d" "\n", __func__, decimal_data -> error_size); 
    dprintf(stderr_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, decimal_data -> error_str); 
#endif 
    return error_id; 
  }; 

 error_label__error_in_postfix_computation: { 
    return error_id; 
  }; 

  assert(false);   
  
 label__error__error_in_bytecode_generation: { 
    return error_id; 
  }; 
  
  assert(false);   
  
 error_label__not_enough_tokens: { 
    //const int token_count_left = token_nb - token_i; 
    error_id = DECIMAL__DATA_GENERATION__NOT_ENOUGH_TOKENS; 
    const int error_location_len = token_i <= 0 ? 0 : snprintf(error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i - 1), decimal_token__get_line1(token_env, token_i - 1), decimal_token__get_column0(token_env, token_i - 1)); 
    const int error_location_written_len = MIN(DECIMAL_ENV__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(error_str + error_location_written_len, DECIMAL_ENV__ERROR_BUFFER_SIZE - error_location_written_len, "End-of-file reached, while parsing not completed"); 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return error_id; 
  }; 

  assert(false);   
  
#if 0   
 error_label__too_many_tokens: { 
    const int token_count_left = token_nb - token_i; 
    decimal_data -> error_id = DECIMAL__DATA_GENERATION__TOO_MANY_TOKENS;   
    const int error_location_len = snprintf(decimal_data -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(DECIMAL_ENV__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(decimal_data -> error_str + error_location_written_len, DECIMAL_ENV__ERROR_BUFFER_SIZE - error_location_written_len, "Parsing done, but still non-read tokens (%d too many tokens)", token_count_left); 
    if (decimal_data -> stdlog_d > 0) { dprintf(decimal_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, decimal_data -> error_str); }; 
    return decimal_data -> error_id; 
  }; 

 error_label__expecting_boolean:  {
    const char * error__expected_token_type_cstr = "BOOLEAN"; 
    const char * error__got_token_type_cstr      = decimal_token__type_get_cstr(token_type); 
    decimal_data -> error_id = DECIMAL__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE; 
    const int error_location_len = snprintf(decimal_data -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(DECIMAL_ENV__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(decimal_data -> error_str + error_location_written_len, DECIMAL_ENV__ERROR_BUFFER_SIZE - error_location_written_len, "Non-matching token type — Expecting: %s ; Got: %s", error__expected_token_type_cstr, error__got_token_type_cstr); 
    if (decimal_data -> stdlog_d > 0) { dprintf(decimal_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, decimal_data -> error_str); }; 
    return decimal_data -> error_id; 
  };

 error_label__non_matching_token_type: {
    const char * error__expected_token_type_cstr = decimal_token__type_get_cstr(error__expected_token_type); 
    const char * error__got_token_type_cstr      = decimal_token__type_get_cstr(                token_type); 
    decimal_data -> error_id = DECIMAL__DATA_GENERATION__NON_MATCHING_TOKEN_TYPE; 
    const int error_location_len = snprintf(decimal_data -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(DECIMAL_ENV__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(decimal_data -> error_str + error_location_written_len, DECIMAL_ENV__ERROR_BUFFER_SIZE - error_location_written_len, "Non-matching token type — Expecting: %s ; Got: %s", error__expected_token_type_cstr, error__got_token_type_cstr); 
    if (decimal_data -> stdlog_d > 0) { dprintf(decimal_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, decimal_data -> error_str); }; 
    return decimal_data -> error_id; 
  };

 error_label__non_matching_token_value: {
    decimal_data -> error_id = DECIMAL__DATA_GENERATION__NON_MATCHING_TOKEN_VALUE; 
    const int error_location_len = snprintf(decimal_data -> error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "{%s:%d:%d}: ", decimal_token__get_srcfile_cstr(token_env, token_i), decimal_token__get_line1(token_env, token_i), decimal_token__get_column0(token_env, token_i)); 
    const int error_location_written_len = MIN(DECIMAL_ENV__ERROR_BUFFER_SIZE - 1, error_location_len); 
    snprintf(decimal_data -> error_str + error_location_written_len, DECIMAL_ENV__ERROR_BUFFER_SIZE - error_location_written_len, "Non-matching token value — Expecting: '%s' ; Got: '%s'", error__expected_token_value, srcval); 
    if (decimal_data -> stdlog_d > 0) { dprintf(decimal_data -> stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, decimal_data -> error_str); }; 
    return decimal_data -> error_id; 
  };
#endif 



 label__start: {}; 
  int token_type; 
  int success_huh = false; 
  const char * srcval; 
  int signval = 1; 
  float floatval; 
  int intval; 
  int boolval; 
  const char * identval; 
  const char * strval; 
  int lookahead_match_huh = false; 
  int error__expected_token_type; 
  const char * error__expected_token_value; 
  char this_memory_space[decimal_syntax_filtering__sizeof]; 
  decimal_syntax_filtering_t * this = (decimal_syntax_filtering_t *) &this_memory_space; 
  uint16_t const_string_len; 
  
  assert(const_string_sizeof >= 1); 
  *const_string_array = '\0'; 
  const_string_len = 1; 
  
  decimal_syntax_filtering__make_r(this, stdlog_d); 
  
  const int_decimal_token_t token_nb = decimal_token__get_count(token_env); 
  if (0 >= token_nb) { goto error_label__not_enough_tokens; }; 
  //{ if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "token_nb = %d" "\n", __func__, (int)token_nb); }; }; 
  //dprintf(STDERR_FILENO, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "token_nb = %d" "\n", __func__, (int)token_nb); 
  
  error_id = decimal_syntax_filtering__get_current_token(this, token_env, &token_i); 
  if (DECIMAL__OK != error_id) { goto error_label__error_in_syntax_filtering; }; 
  
  for (;;) { 
    if (token_i == token_nb - 1) { break; }; 
    LOOKAHEAD_IDENT("exit"); if (lookahead_match_huh) { goto directive_exit; }; 
    LOOKAHEAD_IDENT("quit"); if (lookahead_match_huh) { goto directive_exit; }; 
    LOOKAHEAD_IDENT("bye" ); if (lookahead_match_huh) { goto directive_exit; }; 
    goto decimal_expression; 
    
  directive_exit: { 
      *directive_or_expr_huh_r = true; 
      break; 
    }; 
    
  decimal_expression: { 
#if 0 
      READ_LALR_FLOAT(); decimal_data -> choc_longueur = floatval; 
      READ_LALR_ENTIER(); decimal_data -> vie = intval; 
      READ_BOOLEEN(); decimal_data -> invincible = boolval; 
      READ_STRING(); decimal_data -> membres_image[decimal_data -> membres_nb] = decimal__strcopy(decimal_data, strval); 
#endif 
      SWITCH_TO_LALR_MODE(); // Sets a flag — Will actually reorder tokens on next call to 'get_next_token'. 
      // NB: In LALR mode, the parser reads & reorders as much as it can, which means until it founds an unknown token (incl. 'bye', ';', EOF, etc., or even something like '1' followed by 'cos'). 
      error_id = decimal_bytecode__read_postfix_tokens(this, token_env, bytecode_data, bytecode_size, bytecode_len_r, const_string_array, const_string_sizeof, &const_string_len, stduser_d, stdlog_d); 
      GET_CURRENT_TOKEN(); // To update 'token_i'. 
      if (error_id != DECIMAL__OK) { goto error_label__error_in_syntax_filtering; }; 
      continue; 
    }; 
  }; 
  
  PUSH_BYTECODE(DECIMAL__BYTECODE__HALT); 
  
  error_id = DECIMAL__OK; 
  goto label__exit; 
  
  assert(false); 
}; 










