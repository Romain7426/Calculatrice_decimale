#ifndef DECIMAL_TOKEN_PARSER_H
#define DECIMAL_TOKEN_PARSER_H

extern int_decimal_error_t decimal_token__parser(decimal_token_env_t * token_env, decimal_token_input_env_t * input_env, const int input_i, int_decimal_error_t * error_id_r, const uint16_t error_size, char * error_str); 

#endif /* DECIMAL_TOKEN_PARSER_H */
