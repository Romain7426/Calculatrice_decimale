#ifndef DECIMAL_TOKEN_H
#define DECIMAL_TOKEN_H

// *********************** TOKEN ENV *********************** 

#ifndef DECIMAL_TOKEN_ENV_T 
#define DECIMAL_TOKEN_ENV_T 
struct         decimal_token_env_t; 
typedef struct decimal_token_env_t   decimal_token_env_t; 
#endif 
extern  const  int32_t               decimal_token_env__sizeof; 
extern         decimal_token_env_t * decimal_token_env__make    (const int stdlog_d); 
extern         decimal_token_env_t * decimal_token_env__make_b  (const int bsize, void * bvalue, int * used_size_ref, const int stdlog_d); 
extern         decimal_token_env_t * decimal_token_env__make_r  (decimal_token_env_t * this, const int stdlog_d); 
extern         decimal_token_env_t * decimal_token_env__bzero   (decimal_token_env_t * this); 
extern         decimal_token_env_t * decimal_token_env__reset   (decimal_token_env_t * this); 
extern         void                  decimal_token_env__delete  (decimal_token_env_t * this); 
extern         void                  decimal_token_env__delete_r(decimal_token_env_t * this); 
extern  const  char                * decimal_token_env__strcopy (decimal_token_env_t * this, const char * cstr); 

extern         int                   decimal_token__parser__stdlog(const decimal_token_env_t * this); 



// *********************** TOKEN *********************** 

typedef       uint16_t            int_decimal_token_t; 
extern  const int_decimal_token_t int_decimal_token_max; // RL: For storage, where data should be packed (anywhere else, 'int' is good). It ensures that a token will fit into a 'int_decimal_token_type_t'. 
enum { DECIMAL_TOKEN_I_INVALID = UINT16_MAX }; 
extern  const int_decimal_token_t DECIMAL_TOKEN_I_INVALID__compiled_value; 
enum { DECIMAL_TOKEN_I_BOF = UINT16_MAX - 1 }; 
extern  const int_decimal_token_t DECIMAL_TOKEN_I_BOF__compiled_value; 

extern int decimal_token__push(decimal_token_env_t * this, const int srcval_len, const char * srcval_rstr, const int token_type, const char * srcfile, const int offset0, const int line1, const int column0); 

extern const char * decimal_token__get_srcval_cstr (const decimal_token_env_t * this, const int token_idx); 
extern       int    decimal_token__get_type        (const decimal_token_env_t * this, const int token_idx); 
extern const char * decimal_token__get_srcfile_cstr(const decimal_token_env_t * this, const int token_idx); 
extern       int    decimal_token__get_offset0     (const decimal_token_env_t * this, const int token_idx); 
extern       int    decimal_token__get_line1       (const decimal_token_env_t * this, const int token_idx); 
extern       int    decimal_token__get_column0     (const decimal_token_env_t * this, const int token_idx); 
extern       int    decimal_token__get_count       (const decimal_token_env_t * this); 
extern       int    decimal_token__get_size        (const decimal_token_env_t * this); 

extern       void   decimal_token__syntax_filtering__adjust_type(decimal_token_env_t * this, const int token_idx, const int adjusted_type); 

extern void decimal_token__print_stats     (const int filedes, const decimal_token_env_t * this); 
extern void decimal_token__print_one_token (const int filedes, const decimal_token_env_t * this, const int token_i); 
extern void decimal_token__print_nb_tokens (const int filedes, const decimal_token_env_t * this, const int token_nb); 
extern void decimal_token__print_all_tokens(const int filedes, const decimal_token_env_t * this); 

extern int decimal_token__dump_raw   (const int filedes, const decimal_token_env_t * this); 
extern int decimal_token__restore_raw(const int filedes,       decimal_token_env_t * this); 

extern       int      decimal_token__master_push_cstr(      decimal_token_env_t * this, const char * ident_cstr); 
extern       int      decimal_token__master_push_pstr(      decimal_token_env_t * this, const int    ident_pstr); 
extern       int      decimal_token__master_count    (const decimal_token_env_t * this); 
extern const int    * decimal_token__master_len      (const decimal_token_env_t * this); 
extern const char * * decimal_token__master_cstr     (const decimal_token_env_t * this); 

extern       int      decimal_token__syntax_keyword_push_cstr(      decimal_token_env_t * this, const char * ident_cstr); 
extern       int      decimal_token__syntax_keyword_push_pstr(      decimal_token_env_t * this, const int    ident_pstr); 
extern       int      decimal_token__syntax_keyword_count    (const decimal_token_env_t * this); 
extern const int    * decimal_token__syntax_keyword_len      (const decimal_token_env_t * this); 
extern const char * * decimal_token__syntax_keyword_cstr     (const decimal_token_env_t * this); 

#endif /* DECIMAL_TOKEN_H */
