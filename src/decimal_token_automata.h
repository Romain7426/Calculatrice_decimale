#ifndef DECIMAL_TOKEN_AUTOMATA_H
#define DECIMAL_TOKEN_AUTOMATA_H


enum { DECIMAL_TOKEN_AUTOMATA__TYPE__NULL, DECIMAL_TOKEN_AUTOMATA__TYPE__STRING, DECIMAL_TOKEN_AUTOMATA__TYPE__FUNCTION, DECIMAL_TOKEN_AUTOMATA__TYPE__MASTER, DECIMAL_TOKEN_AUTOMATA__TYPE__SYNTAX_KEYWORD }; 

#ifndef DECIMAL_TOKEN_AUTOMATA_T 
#define DECIMAL_TOKEN_AUTOMATA_T 
struct decimal_token_automata_t; 
typedef struct decimal_token_automata_t decimal_token_automata_t; 
#endif  
struct decimal_token_automata_t { uint8_t token_type; int8_t automata_type; int8_t value1; const char * value_ptr1; const void * automata; }; 
extern decimal_token_automata_t decimal_token_automata[]; 
extern const uint8_t decimal_token_automata__size; 
 
enum {  DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE = (1 << 6) }; //(INT8_MAX >> 1) }; 
#define DECIMAL_TOKEN_AUTOMATA__STATE_FINAL_HUH(s) ((s) >= DECIMAL_TOKEN_AUTOMATA__FINAL_STATE_BASE)

extern  int8_t decimal_token_automata__read_symbol   (const decimal_token_automata_t * automata, const uint8_t automaton_i, const int8_t current_state, const int16_t char_to_be_read); 

extern uint8_t decimal_token_automata__get_token_type(const decimal_token_automata_t * automata, const uint8_t automaton_i); 

extern void    decimal_token_automata__set_master(decimal_token_automata_t * automata, const decimal_token_env_t * token_env); 

extern int8_t  decimal_token_automaton__get__master(const int master__nb, const int master__len[], const char * master__array[], const int8_t current_state0); 






#endif /* DECIMAL_TOKEN_AUTOMATA_H */
