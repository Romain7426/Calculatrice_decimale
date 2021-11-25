#include "decimal_global.h"
#include "decimal_token_type.h"
#include "decimal_token.h"
#include "decimal_token_automata.h"





int8_t decimal_token_automaton__get__master(const int master__nb, const int master__len[], const char * master__array[], const int8_t current_state0) { 
  const int8_t current_state = (~DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE) & current_state0; 
#if 0 
  dputs_array(stderr, __func__, ": ", "DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE: ", int_to_str_base2__stack(DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE), "\n"); 
  dputs_array(stderr, __func__, ": ", "current_state0: ", int_string__stack(current_state0), "; current_state = ", int_string__stack(current_state), "\n"); 
#endif 
  if (current_state < 0) { return -1; }; 
  for (int i = 0; i < master__nb; i++) { 
    if (current_state == master__len[i]) { return i; }; 
  }; 
  return -1; 
}; 



//static int8_t token_automaton__match__master(const int const decimal_token_env_t * token_env, const int8_t current_state0, const int16_t char_given) { 
static int8_t token_automaton__match__master(const int master__nb, const int master__len[], const char * master__array[], const int8_t current_state0, const int16_t char_given) { 
  const int8_t current_state = (~DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE) & current_state0; 
#if 0 
  dputs_array(stderr, __func__, ": ", "DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE: ", int_to_str_base2__stack(DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE), "\n"); 
  dputs_array(stderr, __func__, ": ", "current_state0: ", int_string__stack(current_state0), "; current_state = ", int_string__stack(current_state), "\n"); 
#endif 
  if (current_state < 0) { return -1; }; 
  const int char_to_be_read = tolower(char_given); 
  for (int i = 0; i < master__nb; i++) { 
    if (current_state >= master__len[i]) { continue; }; 
    if (master__array[i][current_state] != char_to_be_read) { continue; }; 
    const int next_state = current_state + 1; 
    if (next_state == master__len[i]) { return next_state | DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; } 
    else { return next_state; }; 
  }; 
  return -1; 
}; 

static int8_t token_automaton__match__string__case_insensitive(const int cstr_to_be_matched_len, const char * cstr_to_be_matched, const int8_t current_state, const int16_t char_given) { 
  if (current_state <                       0) { return -1; }; 
  if (current_state >= cstr_to_be_matched_len) { return -1; }; 
  const int char_to_be_read = tolower(char_given); 
  if (cstr_to_be_matched[current_state] != char_to_be_read) { return -1; }; 
  const int next_state = current_state + 1; 
  if (next_state == cstr_to_be_matched_len) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
  return next_state; 
}; 

static int8_t token_automaton__match__string__case_sensitive(const int cstr_to_be_matched_len, const char * cstr_to_be_matched, const int8_t current_state, const int16_t char_given) { 
  if (current_state <                       0) { return -1; }; 
  if (current_state >= cstr_to_be_matched_len) { return -1; }; 
  const int char_to_be_read = (char_given); 
  if (cstr_to_be_matched[current_state] != char_to_be_read) { return -1; }; 
  const int next_state = current_state + 1; 
  if (next_state == cstr_to_be_matched_len) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
  return next_state; 
}; 


static int8_t token_automaton__spaces(const int8_t current_state, const int16_t char_read) { 
  //const char spaces[] = { ' ', '\r', '\n', '\v', '\t', '\0' }; // Null-ended array. 
  const char spaces[] = { ' ', '\r', '\v', '\t', '\0' }; // Null-ended array. 
  // There are two states: 0 and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  assert((0 == current_state) || (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state)); 
  int is_space_huh = (0 != 0); 
  for (int i = 0; spaces[i] != '\0'; i++) {
    if (char_read == spaces[i]) { is_space_huh = (0 == 0); break; }; 
  };
  if (!(is_space_huh)) { return -1; }; 
  return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; 
}; 

static int8_t token_automaton__number(const int8_t current_state, const int16_t char_read) { 
  const char numbers[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0' }; // Null-ended array. 
  // There are three states: 0, 1, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  // RL: We can't accept '-' in numbers as we must be able to parse "2 -1". 
  int is_number_huh = (0 != 0); 
  for (int i = 0; numbers[i] != '\0'; i++) {
    if (char_read == numbers[i]) { is_number_huh = (0 == 0); break; }; 
  };
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    if (is_number_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  if (0 == current_state) {
    //if ('-' == char_read) { return 1; }; 
    if (is_number_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  if (1 == current_state) {
    if (is_number_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__number_dot(const int8_t current_state, const int16_t char_read) { 
  const char numbers[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0' }; // Null-ended array. 
  // There are three states: 0, 1, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  // RL: We can't accept '-' in numbers as we must be able to parse "1 -1.2". 
  // RL: We can't have very liberal literal fixed point numbers as we have to be able to parse the type "1..2", 
  //     type expression that could be recognizing as two consecutive real numbers instead of an integer range. 
  int is_number_huh = (0 != 0); 
  for (int i = 0; numbers[i] != '\0'; i++) {
    if (char_read == numbers[i]) { is_number_huh = (0 == 0); break; }; 
  };
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    if (is_number_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  if (0 == current_state) {
    //if ('-' == char_read) { return 3; }; 
    //if ('.' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if ('.' == char_read) { return 2; }; 
    if (is_number_huh) { return 1; }; 
    return -1; 
  }; 
  
  if (1 == current_state) { 
    //if ('.' == char_read) { return 2; }; 
    if ('.' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if (is_number_huh) { return 1; }; 
    return -1; 
  }; 
  
  if (2 == current_state) {
    if (is_number_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
#if 0 
  if (3 == current_state) {
    if (is_number_huh) { return 1; }; 
    if ('.' == char_read) { return 1; }; 
    return -1; 
  }; 
#endif 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__number_virg(const int8_t current_state, const int16_t read_char) { 
  return -1; // RL: It's too confusing as the comma is used as a separator as well. 
             //     Then, what would be the meaning of 
             //         f(1,2)
             //     A function call with one argument (a real number?), or a function call with two arguments (two integers)? 
  const char numbers[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0' }; // Null-ended array. 
  // There are three states: 0, 1, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  int is_number_huh = (0 != 0); 
  for (int i = 0; numbers[i] != '\0'; i++) {
    if (read_char == numbers[i]) { is_number_huh = (0 == 0); break; }; 
  };
  
  if (0 == current_state) {
    if ('-' == read_char) { return 1; }; 
    //if (',' == read_char) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if (is_number_huh) { return 2; }; 
    return -1; 
  }; 
  
  if (1 == current_state) {
    if (is_number_huh) { return 2; }; 
    return -1; 
  }; 
  
  if (2 == current_state) { 
    if (',' == read_char) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if (is_number_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    if (is_number_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__number_with_e(const int8_t current_state, const int16_t char_read) { 
  const char numbers[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0' }; // Null-ended array. 
  // There are three states: 0, 1, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  int is_number_huh = (0 != 0); 
  for (int i = 0; numbers[i] != '\0'; i++) {
    if (char_read == numbers[i]) { is_number_huh = (0 == 0); break; }; 
  };
  
  if (0 == current_state) {
    if ('-' == char_read) { return 1; }; 
    if (is_number_huh) { return 2; }; 
    return -1; 
  }; 
  
  if (1 == current_state) {
    if (is_number_huh) { return 2; }; 
    return -1; 
  }; 
  
  if (2 == current_state) {
    if (is_number_huh) { return 2; }; 
    if ('e' == char_read) { return 3; }; 
    return -1; 
  }; 
  
  if (2 == current_state) {
    if (is_number_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    if (is_number_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__eof(const int8_t current_state, const int16_t char_read) { 
  // There are two states: 0 and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  if (EOF != char_read)    { return -1; }; 
  if (0 == current_state)  { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) { return -1; }; 
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__eof__wrapper(const int8_t current_state, const int16_t char_read) { 
  const int8_t new_state = token_automaton__eof(current_state, char_read); 
  dputs_array(stderr_d, __func__, ": ", "new_state = ", int_string__stack(new_state), "\n"); 
  return new_state; 
}; 


static int8_t token_automaton__comment_oneline_cpp(const int8_t current_state, const int16_t char_read) { 
  // When one '/' is read, shifting from 0 to 1. 
  // When one '/' is read, shifting from 1 to DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  // Then cycling on DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE except if EOF or EOL. 
  // If EOL or EOF, shifting to -1. 
  // So three states: 0, 1, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    return (('/' == char_read) ? 1 : -1); 
  }; 
  
  if (1 == current_state) {
    return (('/' == char_read) ? DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE : -1); 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    if ('\n' == char_read) { return -1; }; 
    if (EOF == char_read) { return -1; }; 
    return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; // Looping! 
  }; 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__comment_oneline_script(const int8_t current_state, const int16_t char_read) { 
  // When one '#' is read, shifting from 0 to DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  // Then cycling on DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE except if EOF or EOL. 
  // If EOL or EOF, shifting to -1. 
  // So two states: 0, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    return (('#' == char_read) ? DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE : -1); 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    if ('\n' == char_read) { return -1; }; 
    if (EOF == char_read) { return -1; }; 
    return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; // Looping! 
  }; 
  
  assert(false); 
  return -3; 
}; 



static int8_t token_automaton__ident(const int8_t current_state, const int16_t char_read) { 
  //dputs(stderr, "token_automaton__ident"); 
  //dputn(stderr, current_state); 
  //dputn(stderr, char_read); 
  //dputc(stderr, 'A'); 
  // When one 'a..z' is read, shifting from 0 to DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  // So two states: 0, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 

  //const char accepted_char[] = { '_', '-', '+', '/', '*', '<', '>', '=', '!', '\\', '&', '@', '$', '^', '|', '~', '%', ':', ';', ',', /* '(', ')', '{', '}', '[', ']', */ '?', '\0' }; 
  const char accepted_char[] = { '_', '\0' }; 
  int is_accepted_char_huh = (0 != 0); 
  for (int i = 0; accepted_char[i] != '\0'; i++) {
    if (char_read == accepted_char[i]) { is_accepted_char_huh = (0 == 0); break; }; 
  };

  //dputn(stderr, ('A' <= char_read)); 
  if (0 == current_state) {
    if (('a' <= char_read) && ('z' >= char_read)) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if (('A' <= char_read) && ('Z' >= char_read)) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if (is_accepted_char_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    if (('a' <= char_read) && ('z' >= char_read)) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if (('A' <= char_read) && ('Z' >= char_read)) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if (is_accepted_char_huh) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if (('0' <= char_read) && ('9' >= char_read)) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__cstring(const int8_t current_state, const int16_t char_read) { 
  // When one '"' is read, shifting from 0 to 1. 
  // When any is read, looping, except '"', '\\', and EOF. 
  // If EOF, then -1; 
  // If '"', then DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; 
  // If '\\', then 2. 
  // So four states: 0, 1, 2, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    if ('"' != char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (1 == current_state) {
    if (EOF == char_read) { return -1; }; 
    if ('\n' == char_read) { return -1; }; 
    if ('"' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if ('\\' == char_read) { return 2; }; 
    return 1; // looping 
  }; 
  
  if (2 == current_state) {
    if (EOF == char_read) { return -1; }; 
    if ('\n' == char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__cstring__eol(const int8_t current_state, const int16_t char_read) { 
  // When one '"' is read, shifting from 0 to 1. 
  // When any is read, looping, except '"', '\\', and EOF. 
  // If EOF, then -1; 
  // If '"', then DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; 
  // If '\\', then 2. 
  // So four states: 0, 1, 2, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    if ('"' != char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (1 == current_state) {
    if (EOF == char_read) { return -1; }; 
    if ('"' == char_read) { return -1; }; 
    if ('\n' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if ('\\' == char_read) { return 2; }; 
    return 1; // looping 
  }; 
  
  if (2 == current_state) {
    if (EOF == char_read) { return -1; }; 
    if ('\n' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return 1; 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__cstring__eof(const int8_t current_state, const int16_t char_read) { 
  // When one '"' is read, shifting from 0 to 1. 
  // When any is read, looping, except '"', '\\', and EOF. 
  // If EOF, then -1; 
  // If '"', then DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; 
  // If '\\', then 2. 
  // So four states: 0, 1, 2, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    if ('"' != char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (1 == current_state) {
    if ('\n' == char_read) { return -1; }; 
    if ('"' == char_read) { return -1; }; 
    if (EOF == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if ('\\' == char_read) { return 2; }; 
    return 1; // looping 
  }; 
  
  if (2 == current_state) {
    if (EOF == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if ('\n' == char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__pstring(const int8_t current_state, const int16_t char_read) { 
  // When one "'" is read, shifting from 0 to 1. 
  // When any is read, looping, except "'", '\\', and EOF. 
  // If EOF, then -1; 
  // If "'", then DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; 
  // If '\\', then 2. 
  // So four states: 0, 1, 2, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    if ('\'' != char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (1 == current_state) {
    if (EOF == char_read) { return -1; }; 
    if ('\n' == char_read) { return -1; }; 
    if ('\'' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if ('\\' == char_read) { return 2; }; 
    return 1; 
  }; 
  
  if (2 == current_state) {
    if (EOF == char_read) { return -1; }; 
    if ('\n' == char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    if ('\'' == char_read) { return 1; }; 
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 



static int8_t token_automaton__pstring__eol(const int8_t current_state, const int16_t char_read) { 
  // When one "'" is read, shifting from 0 to 1. 
  // When any is read, looping, except "'", '\\', and EOF. 
  // If EOF, then -1; 
  // If "'", then DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; 
  // If '\\', then 2. 
  // So four states: 0, 1, 2, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    if ('\'' != char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (1 == current_state) {
    if (EOF == char_read) { return -1; }; 
    if ('\n' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if ('\'' == char_read) { return 3; }; 
    if ('\\' == char_read) { return 2; }; 
    return 1; 
  }; 
  
  if (2 == current_state) {
    if (EOF == char_read) { return -1; }; 
    if ('\n' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return 1; 
  }; 
  
  if (3 == current_state) {
    if ('\'' == char_read) { return 1; }; 
    return -1; 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 



static int8_t token_automaton__pstring__eof(const int8_t current_state, const int16_t char_read) { 
  // When one "'" is read, shifting from 0 to 1. 
  // When any is read, looping, except "'", '\\', and EOF. 
  // If EOF, then -1; 
  // If "'", then DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; 
  // If '\\', then 2. 
  // So four states: 0, 1, 2, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    if ('\'' != char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (1 == current_state) {
    if (EOF == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; };  
    if ('\n' == char_read) { return -1; }; 
    if ('\'' == char_read) { return 3; }; 
    if ('\\' == char_read) { return 2; }; 
    return 1; 
  }; 
  
  if (2 == current_state) {
    if (EOF == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if ('\n' == char_read) { return -1; }; 
    return 1; 
  }; 
  
  if (3 == current_state) {
    if ('\'' == char_read) { return 1; }; 
    return -1; 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) {
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 



static int8_t token_automaton__comment_oneline_middle(const int8_t current_state, const int16_t char_read) { 
  // When one '/' is read, shifting from 0 to 1. 
  // When one '*' is read, shifting from 1 to 2. 
  // Then cycling on 2 except if EOF or '*' or EOL. 
  // If EOF or EOL, shifting to -1. 
  // If '*', shifting to 3. 
  // When one '*' is read, cycling on 3. 
  // When one '/' is read, shifting from 3 to DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  // So five states: 0, 1, 2, 3, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    return (('/' == char_read) ? 1 : -1); 
  }; 
  
  if (1 == current_state) {
    return (('*' == char_read) ? 2 : -1); 
  }; 
  
  if (2 == current_state) {
    if ('*' == char_read) { return 3; }; 
    if (EOF == char_read) { return -1; }; 
    if (EOL == char_read) { return -1; }; 
    return 2; // Looping! 
  }; 
  
  if (3 == current_state) {
    if ('*' == char_read) { return 3; }; // Looping! 
    if (EOF == char_read) { return -1; }; 
    if ('/' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return 2; // Going backward. 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) { 
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 


static int8_t token_automaton__comment_oneline_middle_start(const int8_t current_state, const int16_t char_read) { 
  // When one '/' is read, shifting from 0 to 1. 
  // When one '*' is read, shifting from 1 to DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  // So three states: 0, 1, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    return (('/' == char_read) ? 1 : -1); 
  }; 
  
  if (1 == current_state) {
    return (('*' == char_read) ? DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE : -1); 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) { 
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 


static int8_t token_automaton__comment_multines(const int8_t current_state, const char char_read) { 
  // When one '/' is read, shifting from 0 to 1. 
  // When one '*' is read, shifting from 1 to 2. 
  // Then cycling on 2 except if EOF or '*'. 
  // If EOF, shifting to -1. 
  // If '*', shifting to 3. 
  // When one '*' is read, cycling on 3. 
  // When one '/' is read, shifting from 3 to DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  // So five states: 0, 1, 2, 3, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    return (('/' == char_read) ? 1 : -1); 
  }; 
  
  if (1 == current_state) {
    return (('*' == char_read) ? 2 : -1); 
  }; 
  
  if (2 == current_state) {
    if ('*' == char_read) { return 3; }; 
    if (EOF == char_read) { return -1; }; 
    return 2; // Looping! 
  }; 
  
  if (3 == current_state) {
    if ('*' == char_read) { return 3; }; // Looping! 
    if (EOF == char_read) { return -1; }; 
    if ('/' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return 2; // Going backward. 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) { 
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 

static int8_t token_automaton__comment_multines_eof(const int8_t current_state, const char char_read) { 
  // When one '/' is read, shifting from 0 to 1. 
  // When one '*' is read, shifting from 1 to 2. 
  // Then cycling on 2 except if EOF or '*'. 
  // If EOF, shifting to -1. 
  // If '*', shifting to 3. 
  // When one '*' is read, cycling on 3. 
  // When one '/' is read, shifting from 3 to DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  // So five states: 0, 1, 2, 3, and DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE. 
  if (-1 == current_state) { return -1; }; 
  
  if (0 == current_state) {
    return (('/' == char_read) ? 1 : -1); 
  }; 
  
  if (1 == current_state) {
    return (('*' == char_read) ? 2 : -1); 
  }; 
  
  if (2 == current_state) {
    if ('*' == char_read) { return 3; }; 
    if (EOF == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return 2; // Looping! 
  }; 
  
  if (3 == current_state) {
    if ('*' == char_read) { return 3; }; // Looping! 
    if (EOF == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    if ('/' == char_read) { return DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE; }; 
    return 2; // Going backward. 
  }; 
  
  if (DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE == current_state) { 
    return -1; 
  }; 
  
  assert(false); 
  return -3; 
}; 






int8_t decimal_token_automata__read_symbol(const decimal_token_automata_t * automata, const uint8_t automaton_i, const int8_t current_state, const int16_t char_to_be_read) { 
#if 0 
  dputs_array(stderr, __func__, ": ", "automaton_i: ", int_string__stack(automaton_i), "; current_state = ", int_string__stack(current_state), "\n"); 
#endif 
  
  if (current_state < 0) { return -1; }; 
  const decimal_token_automata_t * this = &(automata[automaton_i]); 
  
  int8_t next_state; 

  switch (this -> automata_type) { 
  default: assert(false); break; 
  case DECIMAL_TOKEN_AUTOMATA__TYPE__NULL: return -1; break; 
  case DECIMAL_TOKEN_AUTOMATA__TYPE__STRING: { 
    int8_t (* p)(const int cstr_to_be_matched_len, const char * cstr_to_be_matched, const int8_t current_state, const int16_t char_given);
    p = (const void *)this -> automata; 
    next_state = p(this -> value1, this -> value_ptr1, current_state, char_to_be_read); 
  }; break; 
  case DECIMAL_TOKEN_AUTOMATA__TYPE__FUNCTION: { 
    int8_t (* p)(const int8_t current_state, const char char_read); // = this -> automata; 
    p = (const void *)this -> automata; 
    next_state = p(current_state, char_to_be_read); 
  }; break; 
  case DECIMAL_TOKEN_AUTOMATA__TYPE__MASTER: { 
    int8_t (* p)(const int master__nb, const int master__len[], const char * master__array[], const int8_t current_state0, const int16_t char_given); // = (void *)this -> automata; 
    p = (const void *)this -> automata; 
    const decimal_token_env_t * token_env; // = (const void *) this -> value_ptr1; 
    token_env = (const void *) this -> value_ptr1; 
    if (NULL == token_env) { return -1; }; 
    const int      master__nb   = decimal_token__master_count(token_env); 
    const int  *   master__len  = decimal_token__master_len  (token_env); 
    const char * * master__cstr = decimal_token__master_cstr (token_env); 

    next_state = p(master__nb, master__len, master__cstr, current_state, char_to_be_read); 

#if 0 
  dputs_array(stderr, __func__, ": ", "next_state = ", int_string__stack(next_state), "\n"); 
#endif 
  }; break; 
  case DECIMAL_TOKEN_AUTOMATA__TYPE__SYNTAX_KEYWORD: { 
    int8_t (* p)(const int syntax_keyword__nb, const int syntax_keyword__len[], const char * syntax_keyword__array[], const int8_t current_state0, const int16_t char_given); // = this -> automata; 
    p = (const void *) this -> automata; 
    const decimal_token_env_t * token_env = (const void *) this -> value_ptr1; 
    if (NULL == token_env) { return -1; }; 
    const int      syntax_keyword__nb   = decimal_token__syntax_keyword_count(token_env); 
    const int  *   syntax_keyword__len  = decimal_token__syntax_keyword_len  (token_env); 
    const char * * syntax_keyword__cstr = decimal_token__syntax_keyword_cstr (token_env); 

    next_state = p(syntax_keyword__nb, syntax_keyword__len, syntax_keyword__cstr, current_state, char_to_be_read); 

#if 0 
  dputs_array(stderr, __func__, ": ", "next_state = ", int_string__stack(next_state), "\n"); 
#endif 
  }; break; 
  }; 


#if 0 
  dputs_array(stderr, __func__, ": ", "next_state = ", int_string__stack(next_state), "\n"); 
#endif 
  
  return next_state; 
}; 

uint8_t decimal_token_automata__get_token_type(const decimal_token_automata_t * automata, const uint8_t automaton_i) { 
  const decimal_token_automata_t * this = &(automata[automaton_i]); 
  return this -> token_type; 
}; 






void decimal_token_automata__set_master(decimal_token_automata_t * automata, const decimal_token_env_t * token_env) { 
  for (int automaton_i = 0; automaton_i < decimal_token_automata__size; automaton_i++) { 
    decimal_token_automata_t * this = &(automata[automaton_i]); 
    if (this -> automata_type != DECIMAL_TOKEN_AUTOMATA__TYPE__MASTER && this -> automata_type != DECIMAL_TOKEN_AUTOMATA__TYPE__SYNTAX_KEYWORD) { continue; }; 
    this -> value_ptr1 = (const void *)token_env; 
  }; 
}; 












#define TOKEN_AUTOMATA__NULL(tt)                          { tt, DECIMAL_TOKEN_AUTOMATA__TYPE__NULL,     0, NULL, NULL } 
#define TOKEN_AUTOMATA__STRING__CASE_SENSITIVE(tt,cstr)   { tt, DECIMAL_TOKEN_AUTOMATA__TYPE__STRING,   ARRAY_SIZE(cstr)-1, cstr, token_automaton__match__string__case_sensitive   } 
#define TOKEN_AUTOMATA__STRING__CASE_INSENSITIVE(tt,cstr) { tt, DECIMAL_TOKEN_AUTOMATA__TYPE__STRING,   ARRAY_SIZE(cstr)-1, cstr, token_automaton__match__string__case_insensitive } 
#define TOKEN_AUTOMATA__FUNCTION(tt,cfun)                 { tt, DECIMAL_TOKEN_AUTOMATA__TYPE__FUNCTION, 0, NULL, cfun } 
#define TOKEN_AUTOMATA__MASTER(tt)                        { tt, DECIMAL_TOKEN_AUTOMATA__TYPE__MASTER,   0, NULL, token_automaton__match__master } 
#define TOKEN_AUTOMATA__SYNTAX_KEYWORD(tt)                { tt, DECIMAL_TOKEN_AUTOMATA__TYPE__SYNTAX_KEYWORD,   0, NULL, token_automaton__match__master } 
#define TOKEN_AUTOMATA__STRING  TOKEN_AUTOMATA__STRING__CASE_SENSITIVE
#define TOKEN_AUTOMATA__ISTRING TOKEN_AUTOMATA__STRING__CASE_INSENSITIVE










#if 1 
// RL: The philosophy changed. Beforehand, one token had exactly one automaton. 
//     Now on, one token can have zero, one, or more automaton. 
//     That implies that the size of that array could be different from the number of token-types. 
//     That said, the order of automata is still meaningful. 

decimal_token_automata_t decimal_token_automata[] = { 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_EOF, token_automaton__eof), 
  // RL: EXPR 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION,           ":="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_SIMPLE,     "="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_IADD,      "+="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_RADD,     "+.="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_ISUB,      "-="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_RSUB,     "-.="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_IMULT,     "*="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_RMULT,    "*.="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_IDIV,   "div="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_RDIV,      "/="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_IMOD,   "mod="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_L_AND,  "and="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_L_OR,    "or="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_L_XOR,  "xor="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_L_NOT,  "not="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_AND,     "&="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_OR,      "|="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_XOR,     "^="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_NOT,     "~="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_RSHIFT, ">>="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_LSHIFT, "<<="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_AND, "and"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_AND,  "&&"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_OR,   "or"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_OR,   "||"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_XOR, "xor"), // RL: BITWISE_XOR is definitely different. 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_XOR,  "^^"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_NOT, "not"), // RL: BITWISE_NOT is definitely different. 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_NOT,  "!!"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_NOT,  "~~"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_EQUAL,  "=="), // RL: The question is the interpretation of "a == b and d != e". 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_DIFF,   "<>"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_DIFF,   "!="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_INF,     "<"), // RL: The question is the interpretation of "a < b and d >= e". 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_SUP,     ">"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_INFEQ,  "<="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_SUPEQ,  ">="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_IDIV, "div"), // RL: This thing has definitely a low priority: "1 + 2 div 4 + 3" 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_IMOD, "mod"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_AND, "&"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_OR,  "|"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_XOR, "^"), // RL: BOOL_XOR is definitely different. 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_NOT, "~"), // RL: BOOL_NOT is definitely different. 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_NOT, "!"), // RL: BOOL_NOT is definitely different. 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_SHIFT_LEFT,  "<<"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_SHIFT_RIGHT, ">>"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_IPLUS,  "+" ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_RPLUS,  "+."), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_IMOINS, "-" ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_RMOINS, "-."), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_IMULT,  "*" ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_RMULT,  "*."), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_RDIV,   "/" ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_POINT,  "." ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_FLECHE, "->"), 
  //TOKEN_AUTOMATA__NULL(DECIMAL_TOKEN_PTR), 
  //TOKEN_AUTOMATA__NULL(DECIMAL_TOKEN_REF), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_INC, "++"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_DEC, "--"), 
  // RL: Constant values, ""), which have the upmost priorities. 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_TRUE,  "true"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FALSE, "false"), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_ENTIER,     token_automaton__number), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_REEL__VIRG, token_automaton__number_virg), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_REEL__DOT,  token_automaton__number_dot), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_REEL__E,    token_automaton__number_with_e), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_STRING_C,   token_automaton__cstring), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_STRING_C__EOL,   token_automaton__cstring__eol), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_STRING_C__EOF,   token_automaton__cstring__eof), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_STRING_P,   token_automaton__pstring), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_STRING_P__EOL,   token_automaton__pstring__eol), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_STRING_P__EOF,   token_automaton__pstring__eof), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_NIL, "nil"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_NULL_PTR, "null"), 
  // RL: LL(1) type 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_TYPE,        "type"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_TYPE_ALIAS, "alias"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_BOOLEAN,  "boolean"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_INTEGER,  "integer"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FLOAT,      "float"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_STRING,    "string"), 
  TOKEN_AUTOMATA__STRING (DECIMAL_TOKEN_SUBRANGE,      ".."), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_ARRAY,      "array"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_RECORD,    "record"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_VARIANT,  "variant"), 
  // RL: LL(1) control flow 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_IF,               "if"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_WHEN,           "when"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_UNLESS,       "unless"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_WHILE,         "while"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FOR,             "for"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_REPEAT,       "repeat"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_BEGIN,         "begin"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_PROCEDURE, "procedure"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_PROCEDURE,      "proc"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FONCTION,   "function"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FONCTION,   "fonction"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FONCTION,        "fun"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_METHODE,      "method"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_METHODE,     "methode"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LAMBDA,       "lambda"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_CONST,         "const"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_VAR,             "var"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_VAR,             "dim"), 
  //TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_REC,             "rec"), 
  // RL: control flow others 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_DONE,   "done"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_DO,       "do"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_THEN,   "then"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_ELSE,   "else"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FI,       "fi"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_UNTIL, "until"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_END,     "end"), 
  // RL: Other qualifying keywords 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_BYREF, "byref"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_BYVAL, "byval"), 
  // RL: Syntatic sugar 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_OF,         "of"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_TO,         "to"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_DOWNTO, "downto"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_STEP,     "step"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_PTVIRG,       ";"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_OPENPAR,      "("), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_CLOSEPAR,     ")"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_OPENBRACKET,  "["), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_CLOSEBRACKET, "]"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_OPENBRACE,    "{"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_CLOSEBRACE,   "}"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_DEUXPOINTS,   ":"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_VIRGULE,      ","), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AS,         "as"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_HUH,         "?"), 
  // RL: Ident 
  TOKEN_AUTOMATA__MASTER(DECIMAL_TOKEN_SYNTAX_MASTER), 
  TOKEN_AUTOMATA__SYNTAX_KEYWORD(DECIMAL_TOKEN_SYNTAX_KEYWORD), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_IDENT,      token_automaton__ident), 
  // RL: Ignored tokens 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_EOL, "\n"), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_BLANC, token_automaton__spaces), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_COMMENT__ONE_LINE_CPP, token_automaton__comment_oneline_cpp), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_COMMENT__ONE_LINE_SCRIPT, token_automaton__comment_oneline_script), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_COMMENT__MULTI_LINES_C_STYLE, token_automaton__comment_multines), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_COMMENT__MULTI_LINES_C_STYLE__EOF, token_automaton__comment_multines_eof), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_COMMENT__MULTI_LINES_C_STYLE__LONELY_ENDING,      "*/"), 
}; 
 

enum { decimal_token_automata__size_ = ARRAY_SIZE(decimal_token_automata) }; 

const uint8_t decimal_token_automata__size = decimal_token_automata__size_; 

static void assert_compile__dkushdsuf2387645kjh4r(void) {
  ASSERT_COMPILE(decimal_token_automata__size_ <= 255); 
}; 


#elif 0 
// RL: The philosophy changed. Beforehand, one token had exactly one automaton. 
//     Now on, one token can have zero, one, or more automaton. 
//     That said, the order of automata is still meaningful. 

decimal_token_automata_t decimal_token_automata[] = { 
  TOKEN_AUTOMATA__NULL(DECIMAL_TOKEN_NULL), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_EOF, token_automaton__eof), 
  // RL: EXPR 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION,           ":="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_SIMPLE,     "="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_IADD,      "+="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_RADD,     "+.="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_ISUB,      "-="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_RSUB,     "-.="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_IMULT,     "*="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_RMULT,    "*.="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_IDIV,   "div="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_RDIV,      "/="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_IMOD,   "mod="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_L_AND,  "and="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_L_OR,    "or="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_L_XOR,  "xor="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AFFECTATION_L_NOT,  "not="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_AND,     "&="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_OR,      "|="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_XOR,     "^="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_NOT,     "~="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_RSHIFT, ">>="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_AFFECTATION_B_LSHIFT, "<<="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_AND, "and"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_OR,   "or"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_XOR, "xor"), // RL: BITWISE_XOR is definitely different. 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LOGICAL_NOT, "not"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_EQUAL,  "=="), // RL: The question is the interpretation of "a == b and d != e". 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_DIFF,   "<>"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_INF,     "<"), // RL: The question is the interpretation of "a < b and d >= e". 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_SUP,     ">"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_INFEQ,  "<="), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_SUPEQ,  ">="), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_IDIV, "div"), // RL: This thing has definitely a low priority: "1 + 2 div 4 + 3" 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_IMOD, "mod"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_AND, "&"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_OR,  "|"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_XOR, "^"), // RL: BOOL_XOR is definitely different. 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_NOT, "~"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_SHIFT_LEFT,  "<<"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_BITWISE_SHIFT_RIGHT, ">>"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_IPLUS,  "+" ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_RPLUS,  "+."), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_IMOINS, "-" ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_RMOINS, "-."), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_IMULT,  "*" ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_RMULT,  "*."), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_RDIV,   "/" ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_POINT,  "." ), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_FLECHE, "->"), 
  TOKEN_AUTOMATA__NULL(DECIMAL_TOKEN_PTR), 
  TOKEN_AUTOMATA__NULL(DECIMAL_TOKEN_REF), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_INC, "++"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_DEC, "--"), 
  // RL: Constant values, ""), which have the upmost priorities. 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_TRUE,  "true"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FALSE, "false"), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_ENTIER,     token_automaton__number), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_REEL__VIRG, token_automaton__number_virg), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_REEL__DOT,  token_automaton__number_dot), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_REEL__E,    token_automaton__number_with_e), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_STRING_C,   token_automaton__cstring), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_STRING_P,   token_automaton__pstring), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_NIL, "nil"), 
  // RL: LL(1) type 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_TYPE,        "type"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_TYPE_ALIAS, "alias"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_BOOLEAN,  "boolean"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_INTEGER,  "integer"), 
  TOKEN_AUTOMATA__STRING (DECIMAL_TOKEN_SUBRANGE,      ".."), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_ARRAY,      "array"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_RECORD,    "record"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_VARIANT,  "variant"), 
  // RL: LL(1) control flow 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_IF,               "if"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_WHEN,           "when"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_UNLESS,       "unless"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_WHILE,         "while"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FOR,             "for"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_REPEAT,       "repeat"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_BEGIN,         "begin"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_PROCEDURE, "procedure"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FONCTION,   "function"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_METHODE,      "method"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_LAMBDA,       "lambda"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_CONST,         "const"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_VAR,             "var"), 
  // RL: control flow others 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_DONE,   "done"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_DO,       "do"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_THEN,   "then"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_ELSE,   "else"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_FI,       "fi"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_UNTIL, "until"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_END,     "end"), 
  // RL: Other qualifying keywords 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_BYREF, "byref"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_BYVAL, "byval"), 
  // RL: Syntatic sugar 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_OF,         "of"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_TO,         "to"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_DOWNTO, "downto"), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_STEP,     "step"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_PTVIRG,       ";"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_OPENPAR,      "("), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_CLOSEPAR,     ")"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_OPENBRACKET,  "["), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_CLOSEBRACKET, "]"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_DEUXPOINTS,   ":"), 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_VIRGULE,      ","), 
  TOKEN_AUTOMATA__ISTRING(DECIMAL_TOKEN_AS,         "as"), 
  // RL: Ident 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_IDENT,      token_automaton__ident), 
  // RL: Ignored tokens 
  TOKEN_AUTOMATA__STRING(DECIMAL_TOKEN_EOL, "\n"), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_BLANC, token_automaton__spaces), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_COMMENT__ONE_LINE_CPP, token_automaton__comment_oneline_cpp), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_COMMENT__ONE_LINE_SCRIPT, token_automaton__comment_oneline_script), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_COMMENT__MULTI_LINES_C_STYLE, token_automaton__comment_multines), 
  TOKEN_AUTOMATA__FUNCTION(DECIMAL_TOKEN_COMMENT__MULTI_LINES_C_STYLE__EOF, token_automaton__comment_multines_eof), 
}; 
 

enum { decimal_token_automata__size_ = ARRAY_SIZE(decimal_token_automata) }; 

const int decimal_token_automata__size = decimal_token_automata__size_; 


static void assert_compile__dkushdsuf2387645kjhsddsfr(void) {
  ASSERT_COMPILE(decimal_token_automata__size_ == DECIMAL_TOKEN_COUNT); 

  ASSERT_COMPILE(decimal_token_automata[DECIMAL_TOKEN_NULL].token_type == DECIMAL_TOKEN_NULL); 
  
#define AUTOMATA_CHECK_INDEX(index) ASSERT_COMPILE(decimal_token_automata[index].token_type == index); 
  
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_NULL); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_EOF); 
  // RL: EXPR 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_SIMPLE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_IADD); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_RADD); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_ISUB); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_RSUB); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_IMULT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_RMULT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_IDIV); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_RDIV); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_IMOD); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_L_AND); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_L_OR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_L_XOR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_L_NOT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_B_AND); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_B_OR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_B_XOR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_B_NOT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_B_RSHIFT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AFFECTATION_B_LSHIFT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_LOGICAL_AND); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_LOGICAL_OR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_LOGICAL_XOR); // RL: BITWISE_XOR is definitely different. 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_LOGICAL_NOT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_EQUAL); // RL: The question is the interpretation of "a == b and d != e". 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_DIFF); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_INF); // RL: The question is the interpretation of "a < b and d >= e". 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_SUP); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_INFEQ); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_SUPEQ); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_IDIV); // RL: This thing has definitely a low priority: "1 + 2 div 4 + 3" 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_IMOD); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BITWISE_AND); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BITWISE_OR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BITWISE_XOR); // RL: BOOL_XOR is definitely different. 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BITWISE_NOT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BITWISE_SHIFT_LEFT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BITWISE_SHIFT_RIGHT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_IPLUS); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_RPLUS); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_IMOINS); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_RMOINS); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_IMULT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_RMULT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_RDIV); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_POINT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_FLECHE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_PTR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_REF); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_INC); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_DEC); 
  // RL: Constant values); which have the upmost priorities. 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_TRUE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_FALSE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_ENTIER); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_REEL__VIRG); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_REEL__DOT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_REEL__E); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_STRING_C); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_STRING_P); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_NIL); 
  // RL: LL(1) type 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_TYPE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_TYPE_ALIAS); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BOOLEAN); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_INTEGER); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_SUBRANGE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_ARRAY); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_RECORD); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_VARIANT); 
  // RL: LL(1) control flow 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_IF); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_WHEN); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_UNLESS); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_WHILE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_FOR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_REPEAT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BEGIN); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_PROCEDURE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_FONCTION); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_METHODE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_LAMBDA); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_CONST); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_VAR); 
  // RL: control flow others 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_DONE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_DO); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_THEN); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_ELSE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_FI); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_UNTIL); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_END); 
  // RL: Other qualifying keywords 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BYREF); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BYVAL); 
  // RL: Syntatic sugar 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_OF); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_TO); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_DOWNTO); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_STEP); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_PTVIRG); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_OPENPAR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_CLOSEPAR); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_OPENBRACKET); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_CLOSEBRACKET); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_DEUXPOINTS); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_VIRGULE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_AS); 
  // RL: Ident 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_IDENT); 
  // RL: Ignored tokens 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_EOL); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_BLANC); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_COMMENT__ONE_LINE_CPP); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_COMMENT__ONE_LINE_SCRIPT); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_COMMENT__MULTI_LINES_C_STYLE); 
  AUTOMATA_CHECK_INDEX(DECIMAL_TOKEN_COMMENT__MULTI_LINES_C_STYLE__EOF); 




}; 


#endif 


