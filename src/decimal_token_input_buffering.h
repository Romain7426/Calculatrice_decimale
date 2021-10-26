#ifndef DECIMAL_TOKEN_INPUT_H
#define DECIMAL_TOKEN_INPUT_H

/* 
 * Reading the input must be buffered: 
 *  - First, the buffer holds the currently recognized token. 
 *  - More than that, the token parser can back-track (or look-ahead), and back-tracking (ahead-looking) is unbounded. 
 *    Technically speaking, that means the token parser needs to tell «go backward by n» — which can only be done using a buffer. 
 * 
 * As a side note, obviously, the buffer has a size, so, in facts, back-tracking (ahead-looking) is bounded by the buffer size. 
 */ 
 
/* 
 * Also, traditionally, text files are considered as an array of lines («line discipline») — softwarely, they are read line by line. 
 * Tokenly speaking, that means no token should overlap two or more lines (no token should contain a newline character). 
 * There's nothing compulsory here, but a common implicit rule used everywhere. 
 * 
 * Considering that fact, any token must be shorter than a line. 
 * So the reading buffer must be able to contain a full line (a token + a newline char + null char). 
 * And there's no need for the buffer to contain more than one line. 
 * Therefore, basically, the buffer size is roughly the maximum size of a line. 
 * 
 * Officially, there's no bound on the size of a line. 
 * However, usually, as softwares read and buffer one line at once, thus line size is de facto limited (by the size of the buffer). 
 * 
 * Consequences of that: 
 *  - There's no need to save the line of the end char of token, as a token can't spread over multiple lines (a «len» field is enough). 
 *  - There's no need to save the position in the buffer — as the buffer holds a full line and nothing more, the «column» field is the same information. 
 *  - When back-tracking, we're necessarily on the same line — we do no get through newline chars (oherwise, they would have to be counted). 
 */ 
//enum { DECIMAL_TOKEN_INPUT__BUFFER_SIZE = UINT16_MAX               - 1 }; // RL: UINT16_MAX (~0) should be kept aside to indicate an invalid value. 
enum { DECIMAL_TOKEN_INPUT__BUFFER_SIZE = 
#include "sc_line_max.ci" 
<< 1 }; 
enum { DECIMAL_TOKEN_INPUT__LINE_MAX    = DECIMAL_TOKEN_INPUT__BUFFER_SIZE - 2 }; // RL: On top of the characters of the line, the buffer should be able to contain the newline char and the null char. 

/* 
 * As being parsed data could have "include"-like directives, multiple files may be needed to be parsed. 
 * And those directives could be nested. 
 * Therefore, we need to be able to save the current reading context before switching to the new one. 
 * However, files aren't parsed concurrently — it's a DFS traversal («depth first search») — the included 
 * file must be completely processed before returning to the including one (it's serial, not parallel). 
 * Thus, stacking these contexts matches the requirements. 
 * 
 * Nonetheless, that means, on top of a reading buffer, a context-stacking ability must be provided. 
 * 
 * Also, as a rule, the reading buffer will be used only by the top context, and thus needs not to be stacked. 
 * First, it does not make sense to switch a new context in the middle of a token analysis. 
 * Furthermore, to have a consistent line discipline, such switching directives are required to be alone on the line. Thus, any characters left on the line are discarded. 
 */ 
enum { DECIMAL_TOKEN_INPUT__STACK_SIZE = INT8_MAX - 1 }; 
typedef       uint8_t                         int_decimal_token_input_stack_t; 
extern  const int_decimal_token_input_stack_t int_decimal_token_input_stack_max; // RL: For storage, wherein data should be packed (anywhere else, 'int' is good). It ensures that an input_stack will fit into a 'int_decimal_token_input_stack_t'. 

// An input data can be provided: 
//  a. As a filename (file that has to be opened). 
//  b. As a file descriptor (already opened). 
//  c. As a in-memory data. 
// The purpose of that type is to keep track of that information. 
enum { 
  DECIMAL_TOKEN_INPUT__TYPE__NULL, 
  DECIMAL_TOKEN_INPUT__TYPE__RO_MEM, 
  DECIMAL_TOKEN_INPUT__TYPE__FILE,   // RL: Owner, as we open the file. 
  DECIMAL_TOKEN_INPUT__TYPE__FD,     // RL: Given, so we are not the owner, and we should not close it. 
  DECIMAL_TOKEN_INPUT__TYPE__COUNT, 
}; 

typedef       uint8_t                         int_decimal_token_input_type_t; 
extern  const int_decimal_token_input_type_t  int_decimal_token_input_type_max; // RL: For storage, wherein data should be packed (anywhere else, 'int' is good). It ensures that an input_type will fit into a 'int_decimal_token_input_type_t'. 

extern const int_decimal_token_input_type_t decimal_token_input_count; 
extern const char * decimal_token_input__type_get_cstr(const int_decimal_token_input_type_t decimal_token_input_type); 
#define decimal_token_input__type_cstr decimal_token_input__type_get_cstr


enum { DECIMAL_TOKEN_INPUT__ERROR_BUFFER_SIZE = (1 << 11) }; 
enum { DECIMAL_TOKEN_INPUT__STRING_STACK_SIZE = (1 << 12) }; 

enum { 
  DECIMAL_TOKEN_INPUT__OK = 0, 
  DECIMAL_TOKEN_INPUT__STRCOPY = INT8_MIN, 
  DECIMAL_TOKEN_INPUT__FD_NEG, 
  DECIMAL_TOKEN_INPUT__FDOPEN, 
}; 

#ifndef DECIMAL_TOKEN_INPUT_ENV_T 
#define DECIMAL_TOKEN_INPUT_ENV_T 
struct decimal_token_input_env_t; 
typedef struct decimal_token_input_env_t decimal_token_input_env_t; 
#endif 
struct decimal_token_input_env_t { 
  uint8_t malloced_flag; // 0 if not, 1 if yes. 
  
  int stdlog_d; // Foreign — we don't own it; valid only if 'stdlog_d > 0' 
  
  uint8_t error_id; 
  char    error_str[DECIMAL_TOKEN_INPUT__ERROR_BUFFER_SIZE]; 
  
  char     string_stack[DECIMAL_TOKEN_INPUT__STRING_STACK_SIZE]; // RL: It will hold the filenames and the repl prompt (and anything else if needed). 
  uint16_t string_stack_nb; 
  
  char     buffer[DECIMAL_TOKEN_INPUT__BUFFER_SIZE]; 
  uint16_t buffer_nb; 
  
  int08_t  eof_huh; 
  
  int_decimal_token_input_stack_t stack_nb; 
  int_decimal_token_input_type_t  input_type[DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  
  const char *   ro_mem           [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  int            ro_mem_len       [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  int            fileno           [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  const char *   filename         [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
#if 1 
  int32_t        buffer0_char0[DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  int24_packed_t buffer0_line1[DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  uint16_t       buffer_i     [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  uint16_t       buffer_j     [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
#else 
  //int32_t        cumulated_chars_nb[DECIMAL_TOKEN_INPUT__STACK_SIZE]; // RL: XXX FIXME: That looks redundant. Does it? 
  int32_t        token_char0      [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  int24_packed_t token_line1      [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  uint16_t       token_column0    [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
  uint16_t       token_len        [DECIMAL_TOKEN_INPUT__STACK_SIZE]; 
#endif 
  
  int08_t      repl_huh; 
  const char * repl_prompt_cstr; 
}; 

extern const char * decimal_token_input_env__strcopy(decimal_token_input_env_t * this, const char * cstr); 

extern decimal_token_input_env_t * decimal_token_input_env__make    (const int stdlog_d); 
extern decimal_token_input_env_t * decimal_token_input_env__make_b  (const int bsize, void * bvalue, const int stdlog_d, int * used_size_ref); 
extern decimal_token_input_env_t * decimal_token_input_env__make_r  (decimal_token_input_env_t * this, const int stdlog_d); 
extern void                decimal_token_input_env__delete  (decimal_token_input_env_t * this); 
extern void                decimal_token_input_env__delete_r(decimal_token_input_env_t * this); 

extern int decimal_token_input__stack_push__filename(decimal_token_input_env_t * this, const char * filename_cstr); 
extern int decimal_token_input__stack_push__memory  (decimal_token_input_env_t * this, const int ro_mem_len, const char * ro_mem, const char * ro_mem_description); 
extern int decimal_token_input__stack_push__filedes (decimal_token_input_env_t * this, const int fd, const char * fd_description); 
extern int decimal_token_input__stack_pop           (decimal_token_input_env_t * this); 

extern int          decimal_token_input__eof_huh        (decimal_token_input_env_t * this); 
extern int          decimal_token_input__getc           (decimal_token_input_env_t * this); 
extern void         decimal_token_input__move_backward  (decimal_token_input_env_t * this, const int chars_nb); 
extern const char * decimal_token_input__get_srcval_rstr(decimal_token_input_env_t * this); // RL: «rstr» is not a null-terminated string. 
extern int          decimal_token_input__get_srcval_len (decimal_token_input_env_t * this); 
extern void         decimal_token_input__validate       (decimal_token_input_env_t * this); 

extern const char * decimal_token_input__get_filename_cstr (const decimal_token_input_env_t * this); 
extern int          decimal_token_input__get_token_location(const decimal_token_input_env_t * this, int24_t * token_line1_ref, uint16_t * token_column0_ref, uint16_t * token_len_ref); 
extern int          decimal_token_input__get_line1         (const decimal_token_input_env_t * this); 
extern int          decimal_token_input__get_column0       (const decimal_token_input_env_t * this); 

extern void decimal_token_input__repl__turn_off  (decimal_token_input_env_t * this); 
extern void decimal_token_input__repl__turn_on   (decimal_token_input_env_t * this); 
extern int  decimal_token_input__repl__set_prompt(decimal_token_input_env_t * this, const char * prompt_cstr); 
 
#endif /* DECIMAL_TOKEN_INPUT_H */
