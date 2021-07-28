#ifndef DECIMAL_DATA_GENERATION_003_FROM_SYNTAX_FILTERING_H 
#define DECIMAL_DATA_GENERATION_003_FROM_SYNTAX_FILTERING_H 
 
 
//extern int_decimal_error_t decimal_data_generation_003_from_syntax_filtering(decimal_token_env_t * token_env, decimal_t * decimal_data, const int stduser_d); 
extern int_decimal_error_t decimal_data_generation_003_from_syntax_filtering(decimal_token_env_t * token_env, uint8_t * directive_or_expr_huh_r, uint8_t * bytecode_data, const uint16_t bytecode_size, uint16_t * bytecode_len_r, char * const_string_array, const uint16_t const_string_sizeof, /*To talk to the user about parsing errors*/const int stduser_d, const int stdlog_d); 
 
 
#endif 
 
