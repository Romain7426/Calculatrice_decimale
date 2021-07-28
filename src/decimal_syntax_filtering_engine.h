#ifndef DECIMAL_TOKEN_SYNTAX_FILTERING_ENGINE_H 
#define DECIMAL_TOKEN_SYNTAX_FILTERING_ENGINE_H 

#ifndef DECIMAL_SYNTAX_FILTERING_T 
#define DECIMAL_SYNTAX_FILTERING_T
struct decimal_syntax_filtering_t; 
typedef struct decimal_syntax_filtering_t decimal_syntax_filtering_t; 
#endif /* DECIMAL_SYNTAX_FILTERING_T */

extern const int32_t                      decimal_syntax_filtering__sizeof; 
extern       decimal_syntax_filtering_t * decimal_syntax_filtering__make     (const int stdlog_d); 
extern       decimal_syntax_filtering_t * decimal_syntax_filtering__make_b   (const int bsize, void * bvalue, int * used_size_ref, const int stdlog_d); 
extern       decimal_syntax_filtering_t * decimal_syntax_filtering__make_r   (      decimal_syntax_filtering_t * this, const int stdlog_d); 
extern       void                         decimal_syntax_filtering__bzero    (      decimal_syntax_filtering_t * this); 
extern       void                         decimal_syntax_filtering__delete   (      decimal_syntax_filtering_t * this); 
extern       void                         decimal_syntax_filtering__delete_r (      decimal_syntax_filtering_t * this); 
extern       int_decimal_error_t          decimal_syntax_filtering__error_id (const decimal_syntax_filtering_t * this); 
extern const char                       * decimal_syntax_filtering__error_str(const decimal_syntax_filtering_t * this); 
extern const char                       * decimal_syntax_filtering__strcopy  (      decimal_syntax_filtering_t * this, const char * cstr); 

extern int_decimal_error_t decimal_syntax_filtering__switch_to_lalr_mode    (      decimal_syntax_filtering_t * this); 
extern int                 decimal_syntax_filtering__lalr_mode_completed_huh(const decimal_syntax_filtering_t * this); 
extern int                 decimal_syntax_filtering__lalr_mode_read_all_huh (const decimal_syntax_filtering_t * this); 

extern int_decimal_error_t decimal_syntax_filtering__get_current_token    (decimal_syntax_filtering_t * this,       decimal_token_env_t * token_env, int_decimal_token_t * token_i_r); 
extern int_decimal_error_t decimal_syntax_filtering__get_next_token       (decimal_syntax_filtering_t * this,       decimal_token_env_t * token_env, int_decimal_token_t * token_i_r); 
extern int_decimal_error_t decimal_syntax_filtering__skip_to_closing_paren(decimal_syntax_filtering_t * this, const decimal_token_env_t * token_env, int_decimal_token_t * token_i_r); 
#define                    decimal_syntax_filtering__move_to_next_token    decimal_syntax_filtering__get_next_token 


#endif /* DECIMAL_TOKEN_SYNTAX_FILTERING_ENGINE_H */
