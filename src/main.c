#include "decimal_global.h" 
#include "decimal.h" 
#include "main.h" 
#include "decimal_token_input_buffering.h" 
#include "decimal_token.h" 
#include "decimal_token_parser.h" 
#include "decimal_data_generation_003_from_syntax_filtering.h" 
#include "decimal_bytecode_type.h" 
#include "decimal_stack.h" 
#include "decimal_vm.h" 

#include "main_options.ci"

static int stdlog_d; 
static int stddata_d; 
 
static void main__stddata_init(void) { 
  if (-1 != fcntl(4, F_GETFL)) { 
    stddata_d = 4; 
  } 
  else { 
    stddata_d = open("/dev/null", O_WRONLY); 
  }; 
}; 

static void main__stddata_reopen(const char * filename) { 
  if (NULL ==  filename) return; 
  if ('\0' == *filename) return; 
  int new_fd; 
  if      (0 == strcasecmp("stdout", filename)) { new_fd = stdout_d; } 
  else if (0 == strcasecmp("stderr", filename)) { new_fd = stderr_d; } 
  else { 
    if (0 == strcasecmp("stdnull", filename)) { filename = "/dev/null"; }; 
    new_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600); 
    if (new_fd < 0) return; 
  }; 
  close(stddata_d); 
  stddata_d = new_fd; 
}; 
 
static void main__stdlog_init(void) { 
  //stdlog_d = 2; return;
  
  //fprintf(stderr, "fcntl(3, F_GETFL) = %d" "\n", fcntl(3, F_GETFL)); 
  //if (-1 != fcntl(3, F_GETFL) && errno == EBADF) { 
  if (-1 != fcntl(3, F_GETFL)) { 
    stdlog_d = 3; 
  } 
  else { 
    //stdlog_d = open("/dev/tty", O_WRONLY);  
    stdlog_d = open("/dev/null", O_WRONLY);  
  }; 
}; 

static void main__stdlog_reopen(const char * filename) { 
  if (NULL ==  filename) return; 
  if ('\0' == *filename) return; 
  int new_fd; 
  if      (0 == strcasecmp("stdout", filename)) { new_fd = stdout_d; } 
  else if (0 == strcasecmp("stderr", filename)) { new_fd = stderr_d; } 
  else { 
    if (0 == strcasecmp("stdnull", filename)) { filename = "/dev/null"; }; 
    new_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600); 
    if (new_fd < 0) return; 
  }; 
  close(stdlog_d); 
  stdlog_d = new_fd; 
}; 

static void main__stduser_open(int * stduser_d_r, const char * filename) { 
  if (NULL ==  filename) return; 
  if ('\0' == *filename) return; 
  if (0 == strcasecmp("stdout",  filename)) { *stduser_d_r = stdout_d; return; }; 
  if (0 == strcasecmp("stderr",  filename)) { *stduser_d_r = stderr_d; return; }; 
  if (0 == strcasecmp("stdnull", filename)) { filename = "/dev/null"; }; 
  int new_fd; 
  new_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600); 
  if (new_fd < 0) return; 
  *stduser_d_r = new_fd; 
}; 

#define main__stdprint_open main__stduser_open



//struct a_t { char u; char aa[]; }; // RL: sizeof(struct a_t) = 1 
#include "main_tests.ci" 


int main2(const int argc, const char * argv[]) { 
  int_decimal_error_t error_id; 
  char error_str[DECIMAL_ENV__ERROR_BUFFER_SIZE]; 
  error_id = DECIMAL__MAIN_ERROR_ID_NOT_ASSIGNED; 
  goto label__start; 
  
 label__exit: { 
    return error_id; 
  }; 
  
 label__error__input_error: { 
    error_id = DECIMAL__TOKEN__INPUT__ERROR; 
    //snprintf(this -> error_str, this -> error_size, "Error while initializing input buffer for tokenizing: %d", input_i); 
    snprintf(error_str, sizeof(error_str), "Error while initializing input buffer for tokenizing: %%d"); 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
    return error_id; 
  }; 
  
 label__start: {}; 
  
  if (!program_options__parse(argc, argv)) { 
    const char err_str[] = "Error while parsing options" "\n"; 
    enum { err_str_len = ARRAY_LEN(err_str) - 1 }; 
    write(stderr_d, err_str, err_str_len); 
    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s", __func__, err_str); }; 
    error_id = DECIMAL__MAIN__OPTIONS__PARSING_ERROR; 
    goto label__exit; 
  }; 
  
  error_id = program_options__run(argc, argv, /*stdprint_d*/stdout_d, /*stduser_d*/stderr_d, /*stdlog_d*/stdlog_d); 
  if (DECIMAL__OK != error_id) { goto label__exit; }; 
  
  //dprintf(stderr_d, "program_options__stdlog_new_output = %s" "\n", program_options__stdlog_new_output); 
  if (program_options__stdlog_new_output != NULL) { 
    main__stdlog_reopen(program_options__stdlog_new_output); 
  }; 
  
  if (program_options__stddata_new_output != NULL) { 
    main__stddata_reopen(program_options__stddata_new_output); 
  }; 
  
  int stduser_d = stderr_d; 
  if (program_options[PROGRAM_OPTIONS_INDEX__QUIET] > 0) { 
    stduser_d = -1; 
  }; 
  if (program_options__stduser_new_output != NULL) { 
    main__stduser_open(&stduser_d, program_options__stduser_new_output); 
  }; 
  
  int stdprint_d = stdout_d; 
  if (program_options[PROGRAM_OPTIONS_INDEX__QUIET] > 0) { 
    stdprint_d = -1; 
  }; 
  if (program_options__stdprint_new_output != NULL) { 
    main__stdprint_open(&stdprint_d, program_options__stdprint_new_output); 
  }; 
  
  
  
#if 1 
  decimal__check_and_assert(); 
#else 
  decimal_version__check_and_assert(); 
  int_decimal_error__check_and_assert(); 
  decimal_env_const__check_and_assert(); 
  decimal_status__check_and_assert(); 
  decimal_struct__check_and_assert(); 
#endif 
  int_decimal_bytecode_type__check_and_assert(); 
  decimal_vm_env__check_and_assert(); 
  
  
  if (0 != program_options[PROGRAM_OPTIONS_INDEX__TESTS]) { 
    error_id = main_tests(stdlog_d, stddata_d, stduser_d, stdprint_d); 
    goto label__exit; 
  }; 
  
  
  if (0 != program_options[PROGRAM_OPTIONS_INDEX__REPL]) { 
    const int stderr_isatty_huh = isatty(STDERR_FILENO); 
    const int stdout_isatty_huh = isatty(STDOUT_FILENO); 
    const int stdin_isatty_huh  = isatty(STDIN_FILENO); 
    
    if (!stderr_isatty_huh) { 
      error_id = DECIMAL__STDERR_IS_NOT_A_TTY; 
      snprintf(error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Cannot run in REPL mode as stderr is not a tty - aborting."); 
      if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
      if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
      goto label__exit; 
    }; 
    
    if (!stdout_isatty_huh) { 
      error_id = DECIMAL__STDOUT_IS_NOT_A_TTY; 
      snprintf(error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Cannot run in REPL mode as stdout is not a tty - aborting."); 
      if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
      if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
      goto label__exit; 
    }; 
    
    if (!stdin_isatty_huh) { 
      error_id = DECIMAL__STDIN_IS_NOT_A_TTY; 
      snprintf(error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Cannot run in REPL mode as stdin is not a tty - aborting."); 
      if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
      if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
      goto label__exit; 
    }; 

    if (0 != program_options__plain__nb) { 
      error_id = DECIMAL__REPL_EXTRA_ARGS; 
      snprintf(error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Extra arguments on command line while in in REPL mode, which one does not expect any argument - aborting."); 
      if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
      if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
      goto label__exit; 
    }; 

    { 
      int          input_file_fd   = stdin_d; 
      const char * input_file_name = "<stdin>";  


      do { 
	uint8_t decimal_env__buffer[DECIMAL_ENV__SIZEOF]; 
	decimal_env_t * decimal_env; 
	decimal_env = decimal_env__make_b(sizeof(decimal_env__buffer), decimal_env__buffer, NULL, stdlog_d); 
	
	static const char prompt[] = "> "; 
	enum { prompt_strlen = sizeof(prompt) - 1 }; 
	
	enum { one_line_sizeof = 2048 }; // = sysconf(_SC_LINE_MAX); 
	enum { one_line_len    = one_line_sizeof - 1 }; 
	static char one_line[one_line_sizeof]; 
	*(one_line + one_line_len) = '\0'; 
	
	decimal_token_input_env_t   input_env[1]; 
	char                        token_env_b[decimal_token_env__sizeof]; 
	decimal_token_env_t       * token_env; 
	decimal_token_input_env__make_r(input_env, stdlog_d); 
	token_env = decimal_token_env__make_b(sizeof(token_env_b), token_env_b, NULL, stdlog_d); 
	//const int input_i = decimal_token_input__stack_push__filedes(input_env, input_file_fd, input_file_name); 
	//if (input_i < 0) { goto label__error__input_error; }; 
	
	int line_count; 
	line_count = 1; 
	char line_count_str[12]; 
		
	//extern decimal_stack_t * decimal_stack__make_b2(const uint16_t buffer_size, uint8_t * buffer, uint16_t * buffer_size_used_r); 
	enum { decimal_stack_buffer_sizeof = (1 << 14) }; 
	uint8_t decimal_stack_buffer[decimal_stack_buffer_sizeof]; 
	decimal_stack_t * decimal_stack = decimal_stack__make_b2(decimal_stack_buffer_sizeof, decimal_stack_buffer, NULL); 
	assert(decimal_stack != NULL); 
	//dprintf(STDERR_FILENO, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "decimal_stack -> size = %d" "\n", __func__, (int)decimal_stack -> size); 

	uint8_t decimal_vm_env_buffer[DECIMAL_VM_ENV__SIZEOF]; 
	decimal_vm_env_t * decimal_vm_env = decimal_vm_env__make_b(sizeof(decimal_vm_env_buffer), decimal_vm_env_buffer, NULL, stdlog_d); 

	
	// TODO XXX FIXME: The terminal may not be in regular mode; especially, may not stop on newlines. 
	
	for (;;) { 
	  // READ 
	  write(stdprint_d, prompt, prompt_strlen); 
	  const ssize_t read_nb = read(STDIN_FILENO, one_line, one_line_len); 
	  if (-1 == read_nb) { 
	    error_id = DECIMAL__REPL_ERROR_WHILE_READING; 
	    snprintf(error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "[REPL Mode] Error while reading."); 
	    if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
	    if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
	    goto label__exit; 
	  }; 
	  
	  if (0 == read_nb) { 
	    // End of file reached. 
	    write(stdprint_d, "\n", 1); 
	    break; 
	  }; 
	  
	  if (1 == read_nb && *one_line == '\n') { 
	    // Nothing typed. 
	    line_count ++; 
	    continue; 
	  }; 
	  
	  if (stdlog_d > 0) { write(stdlog_d, one_line, read_nb); fflush(NULL); }; 
	  
	  // EVAL 
	  { 
	    // Step 1 — Break the read line it down into tokens 
	    int_string__buffer(line_count, sizeof(line_count_str), line_count_str); 
	    const char * ro_mem_description = strconcat__stack(input_file_name, ":", line_count_str); 
	    const int input_i = decimal_token_input__stack_push__memory(input_env, read_nb, one_line, ro_mem_description); 
	    if (input_i < 0) { goto label__error__input_error; }; 
	    
	    decimal_token_env__reset(token_env); 
	    error_id = decimal_token__parser(token_env, input_env, input_i, &error_id, sizeof(error_str), error_str); 
	    if (error_id != DECIMAL__OK) { goto label__exit; }; 
	    
	    if (stdlog_d > 0) { decimal_token__print_all_tokens(stdlog_d, token_env); fflush(NULL); }; 

	    uint8_t directive_or_expr_huh; 
	    uint8_t bytecode_data[256]; 
	    const uint16_t bytecode_size = sizeof(bytecode_data); 
	    uint16_t bytecode_len; 
	    char const_string_array[(1 << 14)]; 
	    const uint16_t const_string_sizeof = sizeof(const_string_array); 
	    bzero(const_string_array, const_string_sizeof); 
	    bytecode_len = 0; 
	    error_id = decimal_data_generation_003_from_syntax_filtering(token_env, &directive_or_expr_huh, bytecode_data, bytecode_size, &bytecode_len, const_string_array, const_string_sizeof, stduser_d, stdlog_d); 
	    if (error_id != DECIMAL__OK) { goto label__exit; }; 

#if 1 
	    { 
	      //const int log_d = -1; 
	      //const int log_d = STDERR_FILENO; 
	      const int log_d = stdlog_d; 
	      if (log_d > 0) { 
		//const_string_array 
		const char * p = const_string_array; 
		p++; 
		for (;;) { 
		  const int len = strlen(p); 
		  if (len <= 0) { break; }; 
		  dputs_array(log_d, "const_string_array[", int_string__stack(p - const_string_array), "] ", " = ", p, "\n"); 
		  p += len; 
		  p++; 
		};
		dprintf(log_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "bytecode_len = %d" "\n", __func__, (int)bytecode_len); 
		for (int i = 0; i < bytecode_len; i++) { 
		  dputs_array(log_d, "bytecode[", int_string__stack(i), "]", " = ", int_string__stack(bytecode_data[i]), "(",  int_decimal_bytecode_type__get_cstr(bytecode_data[i]), ")", "\n"); 
		}; 
	      };
	    }; 
#endif 
	    //dprintf(STDERR_FILENO, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "decimal_stack -> size = %d" "\n", __func__, (int)decimal_stack -> size); 
	    decimal_stack__reset(decimal_stack); 
	    //dprintf(STDERR_FILENO, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "decimal_stack -> size = %d" "\n", __func__, (int)decimal_stack -> size); 

	    //decimal_vm_env__reset(decimal_vm_env); 
	    decimal_vm_env__reset(decimal_vm_env, decimal_env, decimal_stack, bytecode_data, bytecode_size, /*bytecode_start*/0, const_string_array, const_string_sizeof); 
	    
	    decimal_vm__run(decimal_vm_env); 
	    
	    //dprintf(STDERR_FILENO, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "decimal_stack -> size = %d" "\n", __func__, (int)decimal_stack -> size); 
	    for (int i = 0; i < decimal_stack -> nb; i++) { 
	      decimal__print_ln_r(stduser_d, decimal_env, decimal_stack -> array + i); 
	    }; 
	    
#if 0 
	    error_id = decimal__consistency_check(this, stduser_d); 
	    goto label__exit; 
#endif 
	    decimal_token_input__stack_pop(input_env); 
	  }; 
	  
	  // PRINT 
	  //write(stdprint_d, one_line, read_nb); 
	  
	  
	  if (*(one_line + read_nb - 1) == '\n') { 
	    // Line discipline: reading at most one line; but the last character might be something else, like EOF. 
	    line_count ++; 
	  }; 
	  //break; 
	}; 
	
	
#if 0 	
	decimal_t a_decimal[1]; 
	decimal__make_r(a_decimal, stdlog_d); 
	//decimal__print_d(a_decimal, stduser_d); 
	
	error_id = decimal__fill_from_file(a_decimal, input_file_name, input_file_fd, stduser_d); 
	if (error_id != DECIMAL__OK) { 
	  if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "%s[%d]: " "%s" "\n", a_decimal -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_decimal -> error_str); 
	  break; 
	}; 
	
	if (program_options[PROGRAM_OPTIONS_INDEX__PRINT] > 0) { 
	  decimal__print_d(a_decimal, stdout_d); 
	}; 
	
	
	for (int i = 1; i < program_options__plain__nb; i++) { 
	  const int arg_i = program_options__plain[i]; 
	  error_id = decimal__print_field_value_by_name(a_decimal, argv[arg_i], /*stdprint_d*/stdout_d, /*stduser_d*/stduser_d, &a_decimal -> error_id, a_decimal -> error_size, a_decimal -> error_str); 
	  if (error_id != DECIMAL__OK) { 
	    if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "%s[%d]: " "%s" "\n", a_decimal -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_decimal -> error_str); 
	  }; 
	}; 
	
	if (error_id == DECIMAL__OK) { 
	  if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "OK" "\n", a_decimal -> filename); 
	  break; 
	}; 
#endif 
      } while (false); 
      
    }; 
    
    goto label__exit; 
  }; 
  


  {  
    assert(program_options__plain__nb > 0); 
    int          input_file_fd   = stdin_d; 
    const char * input_file_name = "<stdin>";  
    for (;;) { 
      const int arg_i = program_options__plain[0]; 
      const char * s = argv[arg_i];
      if ('-' == *s && '\0' == *(s+1)) break; 
      if (0 == strcasecmp(s, "stdin")) break; 
      input_file_name = s; 
      input_file_fd   = open(input_file_name, O_RDONLY); 
      if (0 > input_file_fd) { 
	error_id = DECIMAL__MAIN__CANNOT_OPEN_INPUT_FILE; 
	snprintf(error_str, DECIMAL_ENV__ERROR_BUFFER_SIZE, "Cannot open input file: %s", input_file_name); 
	if (stduser_d > 0) { dprintf(stduser_d, "%s" "\n", error_str); }; 
	if (stdlog_d  > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "%s" "\n", __func__, error_str); }; 
	goto label__exit; 
      }; 
      break; 
    }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "input_file_name = %s" "\n", __func__, input_file_name); }; 
    if (stdlog_d > 0) { dprintf(stdlog_d, "{" __FILE__ ":" STRINGIFY(__LINE__) ":<%s()>}: " "input_file_fd   = %d" "\n", __func__, input_file_fd  ); }; 
  
  
#if 0 
    dprintf(stderr_d, "DECIMAL__MAIN__CANNOT_OPEN_INPUT_FILE = %d [ %s ]" "\n", DECIMAL__MAIN__CANNOT_OPEN_INPUT_FILE, int_decimal_error__get_cstr(DECIMAL__MAIN__CANNOT_OPEN_INPUT_FILE));
    dprintf(stderr_d, "DECIMAL__OK = %d [ %s ]" "\n", DECIMAL__MAIN__CANNOT_OPEN_INPUT_FILE, int_decimal_error__get_cstr(DECIMAL__OK));
#endif 
  
#if 0 

    do { 
      decimal_t a_decimal[1]; 
      decimal__make_r(a_decimal, stdlog_d); 
      //decimal__print_d(a_decimal, stduser_d); 
    
      error_id = decimal__fill_from_file(a_decimal, input_file_name, input_file_fd, stduser_d); 
      if (error_id != DECIMAL__OK) { 
	if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "%s[%d]: " "%s" "\n", a_decimal -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_decimal -> error_str); 
	break; 
      }; 
    
      if (program_options[PROGRAM_OPTIONS_INDEX__PRINT] > 0) { 
	decimal__print_d(a_decimal, stdout_d); 
      }; 
    
  
      for (int i = 1; i < program_options__plain__nb; i++) { 
	const int arg_i = program_options__plain[i]; 
	error_id = decimal__print_field_value_by_name(a_decimal, argv[arg_i], /*stdprint_d*/stdout_d, /*stduser_d*/stduser_d, &a_decimal -> error_id, a_decimal -> error_size, a_decimal -> error_str); 
	if (error_id != DECIMAL__OK) { 
	  if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "%s[%d]: " "%s" "\n", a_decimal -> filename, error_id > 0 ? "Warning" : "Error", error_id, a_decimal -> error_str); 
	}; 
      }; 
    
      if (error_id == DECIMAL__OK) { 
	if (stduser_d > 0) dprintf(stduser_d, "<%s>: " "OK" "\n", a_decimal -> filename); 
	break; 
      }; 
    } while (false); 
#endif 
  
    if (input_file_fd != stdin_d) { 
      close(input_file_fd); 
    }; 
  
    if (stduser_d > 2) { 
      close(stduser_d); 
    }; 
  
    goto label__exit; 
  }; 


  assert(false); 
}; 




int main(const int argc, const char * argv[]) { 
  main__stdlog_init(); 
  main__stddata_init(); 
  main_arg_print(argc, argv, stdlog_d); 
  srandomdev(); 
  
  { 
    enum { STRFTIME_BUFFER_SIZE = 64 }; 
    char strftime_buffer[STRFTIME_BUFFER_SIZE]; 
    const time_t clock = time(NULL); 
    struct tm timeptr[1]; 
    
    bzero(timeptr, sizeof(timeptr)); 
    gmtime_r(&clock, timeptr); 
    strftime(strftime_buffer, sizeof(strftime_buffer), "TZ=%Z %Y_%m_%d-%Hh%Mm%Ss %A", timeptr); 
    strftime_buffer[STRFTIME_BUFFER_SIZE-1] = '\0'; 
    if (stdlog_d > 0) dprintf(stdlog_d, "%s" "\n", strftime_buffer); 
    
    bzero(timeptr, sizeof(timeptr)); 
    localtime_r(&clock, timeptr); 
    strftime(strftime_buffer, sizeof(strftime_buffer), "TZ=%Z %Y_%m_%d-%Hh%Mm%Ss %A", timeptr); 
    strftime_buffer[STRFTIME_BUFFER_SIZE-1] = '\0'; 
    if (stdlog_d > 0) dprintf(stdlog_d, "%s" "\n", strftime_buffer); 
  }; 
  
  const int_decimal_error_t error_id = main2(argc, argv); 
  
  if (stdlog_d > 0) { dprintf(stdlog_d, "Exit value = [ %d ] %s " "\n", error_id, int_decimal_error__get_cstr(error_id)); }; 
  
  return error_id; 
}; 





