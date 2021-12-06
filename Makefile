
default: Makefile build build_ci build_i build_o build/calc.a build/calc.exe run 




SHELL:= /bin/sh
.SHELLFLAGS: -u -e  
#MAKEFLAGS:= rR -j1 --warn-undefined-variables --warn-undefined-variables 
#MAKEFLAGS:= rR -j1 
.SUFFIXES: 
#.SILENT:
.NOTPARALLEL:
.EXPORT_ALL_VARIABLES:
.SECONDARY:
.PRECIOUS:
.ONESHELL:




clean:
	rm -Rf build 2>&1

clean-all: clean
	rm -Rf destroot run rundir *~ .*~ src/*~ src/*.output src/chaman.anime.ci COPYING_at_start_of_c_files   2>&1


Makefile: Makefile-gen.mkf
	@echo "--- \"Makefile-gen.mkf\" changed. Please type './configure' (or 'romake -f Makefile-gen.mkf') to update this Makefile ---"
	@false

build:
	mkdir -p build 2>&1 


install: destroot_do

destroot_do:
	rm -Rf destroot
	mkdir -p destroot
	mkdir -p destroot/bin
	cp -fp build/*.exe destroot/bin/calc-decimal
	mkdir -p destroot/lib
	cp -fp build/calc.a destroot/lib/decimal.a
	mkdir -p destroot/include
	cp -fp src/decimal.h destroot/include/








run: build/calc.exe
	rm -f run
	ln -s build/calc.exe run


build/calc.exe: build/calc.a build/main.o 
	cc -o build/calc.exe build/main.o build/calc.a      2>&1


build/calc.a: build/decimal.o build/decimal_bytecode_type.o build/decimal_data_generation_003_from_syntax_filtering.o build/decimal_stack.o build/decimal_syntax_filtering_engine.o build/decimal_token.o build/decimal_token_automata.o build/decimal_token_input_buffering.o build/decimal_token_parser.o build/decimal_token_type.o build/decimal_vm.o
	ar -r -c build/calc.a build/decimal.o build/decimal_bytecode_type.o build/decimal_data_generation_003_from_syntax_filtering.o build/decimal_stack.o build/decimal_syntax_filtering_engine.o build/decimal_token.o build/decimal_token_automata.o build/decimal_token_input_buffering.o build/decimal_token_parser.o build/decimal_token_type.o build/decimal_vm.o 2>&1
	ranlib build/calc.a 2>&1






src/chaman.anime.ci: src/chaman.anime
	cat src/chaman.anime | ./tools/bin/text2cstring > src/chaman.anime.ci 














build/decimal.h: src/decimal.h 
	ln src/decimal.h build/decimal.h 

build/decimal_bytecode_type.h: src/decimal_bytecode_type.h 
	ln src/decimal_bytecode_type.h build/decimal_bytecode_type.h 

build/decimal_data_generation_003_from_syntax_filtering.h: src/decimal_data_generation_003_from_syntax_filtering.h 
	ln src/decimal_data_generation_003_from_syntax_filtering.h build/decimal_data_generation_003_from_syntax_filtering.h 

build/decimal_global.h: src/decimal_global.h 
	ln src/decimal_global.h build/decimal_global.h 

build/decimal_stack.h: src/decimal_stack.h 
	ln src/decimal_stack.h build/decimal_stack.h 

build/decimal_syntax_filtering_engine.h: src/decimal_syntax_filtering_engine.h 
	ln src/decimal_syntax_filtering_engine.h build/decimal_syntax_filtering_engine.h 

build/decimal_token.h: src/decimal_token.h 
	ln src/decimal_token.h build/decimal_token.h 

build/decimal_token_automata.h: src/decimal_token_automata.h 
	ln src/decimal_token_automata.h build/decimal_token_automata.h 

build/decimal_token_input_buffering.h: src/decimal_token_input_buffering.h 
	ln src/decimal_token_input_buffering.h build/decimal_token_input_buffering.h 

build/decimal_token_parser.h: src/decimal_token_parser.h 
	ln src/decimal_token_parser.h build/decimal_token_parser.h 

build/decimal_token_type.h: src/decimal_token_type.h 
	ln src/decimal_token_type.h build/decimal_token_type.h 

build/decimal_vm.h: src/decimal_vm.h 
	ln src/decimal_vm.h build/decimal_vm.h 

build/main.h: src/main.h 
	ln src/main.h build/main.h 




build_ci: build build/decimal_add.ci build/decimal_add_v001.ci build/decimal_div.ci build/decimal_div_v001.ci build/decimal_div_v002.ci build/decimal_div_v003.ci build/decimal_div_v004.ci build/decimal_div_v005.ci build/decimal_div_v006.ci build/decimal_div_v007.ci build/decimal_inc_and_dec.ci build/decimal_mult.ci build/decimal_print.ci build/decimal_shift.ci build/decimal_sub_and_neg.ci build/decimal_tests.ci build/decimal_tilde.ci build/decimal_token_env.ci build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/main_old.ci build/main_options.ci build/main_tests.ci build/oldies.ci build/sc_line_max.ci 

build/decimal_add.ci: src/decimal_add.ci 
	ln src/decimal_add.ci build/decimal_add.ci 

build/decimal_add_v001.ci: src/decimal_add_v001.ci 
	ln src/decimal_add_v001.ci build/decimal_add_v001.ci 

build/decimal_div.ci: src/decimal_div.ci 
	ln src/decimal_div.ci build/decimal_div.ci 

build/decimal_div_v001.ci: src/decimal_div_v001.ci 
	ln src/decimal_div_v001.ci build/decimal_div_v001.ci 

build/decimal_div_v002.ci: src/decimal_div_v002.ci 
	ln src/decimal_div_v002.ci build/decimal_div_v002.ci 

build/decimal_div_v003.ci: src/decimal_div_v003.ci 
	ln src/decimal_div_v003.ci build/decimal_div_v003.ci 

build/decimal_div_v004.ci: src/decimal_div_v004.ci 
	ln src/decimal_div_v004.ci build/decimal_div_v004.ci 

build/decimal_div_v005.ci: src/decimal_div_v005.ci 
	ln src/decimal_div_v005.ci build/decimal_div_v005.ci 

build/decimal_div_v006.ci: src/decimal_div_v006.ci 
	ln src/decimal_div_v006.ci build/decimal_div_v006.ci 

build/decimal_div_v007.ci: src/decimal_div_v007.ci 
	ln src/decimal_div_v007.ci build/decimal_div_v007.ci 

build/decimal_inc_and_dec.ci: src/decimal_inc_and_dec.ci 
	ln src/decimal_inc_and_dec.ci build/decimal_inc_and_dec.ci 

build/decimal_mult.ci: src/decimal_mult.ci 
	ln src/decimal_mult.ci build/decimal_mult.ci 

build/decimal_print.ci: src/decimal_print.ci 
	ln src/decimal_print.ci build/decimal_print.ci 

build/decimal_shift.ci: src/decimal_shift.ci 
	ln src/decimal_shift.ci build/decimal_shift.ci 

build/decimal_sub_and_neg.ci: src/decimal_sub_and_neg.ci 
	ln src/decimal_sub_and_neg.ci build/decimal_sub_and_neg.ci 

build/decimal_tests.ci: src/decimal_tests.ci 
	ln src/decimal_tests.ci build/decimal_tests.ci 

build/decimal_tilde.ci: src/decimal_tilde.ci 
	ln src/decimal_tilde.ci build/decimal_tilde.ci 

build/decimal_token_env.ci: src/decimal_token_env.ci 
	ln src/decimal_token_env.ci build/decimal_token_env.ci 

build/lib__01__pre_header.ci: src/lib__01__pre_header.ci 
	ln src/lib__01__pre_header.ci build/lib__01__pre_header.ci 

build/lib__02__header.ci: src/lib__02__header.ci 
	ln src/lib__02__header.ci build/lib__02__header.ci 

build/lib__03.ci: src/lib__03.ci 
	ln src/lib__03.ci build/lib__03.ci 

build/lib__04__string_stack.ci: src/lib__04__string_stack.ci 
	ln src/lib__04__string_stack.ci build/lib__04__string_stack.ci 

build/lib__05__error_state.ci: src/lib__05__error_state.ci 
	ln src/lib__05__error_state.ci build/lib__05__error_state.ci 

build/lib__06__exception.ci: src/lib__06__exception.ci 
	ln src/lib__06__exception.ci build/lib__06__exception.ci 

build/main_old.ci: src/main_old.ci 
	ln src/main_old.ci build/main_old.ci 

build/main_options.ci: src/main_options.ci 
	ln src/main_options.ci build/main_options.ci 

build/main_tests.ci: src/main_tests.ci 
	ln src/main_tests.ci build/main_tests.ci 

build/oldies.ci: src/oldies.ci 
	ln src/oldies.ci build/oldies.ci 

build/sc_line_max.ci: src/sc_line_max.ci 
	ln src/sc_line_max.ci build/sc_line_max.ci 




build/decimal.c: src/decimal.c 
	ln src/decimal.c build/decimal.c 

build/decimal_bytecode_type.c: src/decimal_bytecode_type.c 
	ln src/decimal_bytecode_type.c build/decimal_bytecode_type.c 

build/decimal_data_generation_003_from_syntax_filtering.c: src/decimal_data_generation_003_from_syntax_filtering.c 
	ln src/decimal_data_generation_003_from_syntax_filtering.c build/decimal_data_generation_003_from_syntax_filtering.c 

build/decimal_stack.c: src/decimal_stack.c 
	ln src/decimal_stack.c build/decimal_stack.c 

build/decimal_syntax_filtering_engine.c: src/decimal_syntax_filtering_engine.c 
	ln src/decimal_syntax_filtering_engine.c build/decimal_syntax_filtering_engine.c 

build/decimal_token.c: src/decimal_token.c 
	ln src/decimal_token.c build/decimal_token.c 

build/decimal_token_automata.c: src/decimal_token_automata.c 
	ln src/decimal_token_automata.c build/decimal_token_automata.c 

build/decimal_token_input_buffering.c: src/decimal_token_input_buffering.c 
	ln src/decimal_token_input_buffering.c build/decimal_token_input_buffering.c 

build/decimal_token_parser.c: src/decimal_token_parser.c 
	ln src/decimal_token_parser.c build/decimal_token_parser.c 

build/decimal_token_type.c: src/decimal_token_type.c 
	ln src/decimal_token_type.c build/decimal_token_type.c 

build/decimal_vm.c: src/decimal_vm.c 
	ln src/decimal_vm.c build/decimal_vm.c 

build/main.c: src/main.c 
	ln src/main.c build/main.c 









build_i: build build/decimal.i build/decimal_bytecode_type.i build/decimal_data_generation_003_from_syntax_filtering.i build/decimal_stack.i build/decimal_syntax_filtering_engine.i build/decimal_token.i build/decimal_token_automata.i build/decimal_token_input_buffering.i build/decimal_token_parser.i build/decimal_token_type.i build/decimal_vm.i build/main.i 

build/decimal.i: build/decimal.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_print.ci build/decimal_inc_and_dec.ci build/decimal_shift.ci build/decimal_tilde.ci build/decimal_add.ci build/decimal_sub_and_neg.ci build/decimal_mult.ci build/decimal_div.ci build/decimal_tests.ci 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal.c -o build/decimal.i  2>&1

build/decimal_bytecode_type.i: build/decimal_bytecode_type.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_bytecode_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_bytecode_type.c -o build/decimal_bytecode_type.i  2>&1

build/decimal_data_generation_003_from_syntax_filtering.i: build/decimal_data_generation_003_from_syntax_filtering.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_token.h build/decimal_token_type.h build/decimal_syntax_filtering_engine.h build/decimal_data_generation_003_from_syntax_filtering.h build/decimal_bytecode_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_data_generation_003_from_syntax_filtering.c -o build/decimal_data_generation_003_from_syntax_filtering.i  2>&1

build/decimal_stack.i: build/decimal_stack.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_stack.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_stack.c -o build/decimal_stack.i  2>&1

build/decimal_syntax_filtering_engine.i: build/decimal_syntax_filtering_engine.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_token_type.h build/decimal_token.h build/decimal_syntax_filtering_engine.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_syntax_filtering_engine.c -o build/decimal_syntax_filtering_engine.i  2>&1

build/decimal_token.i: build/decimal_token.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal_token.h build/decimal_token_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_token.c -o build/decimal_token.i  2>&1

build/decimal_token_automata.i: build/decimal_token_automata.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal_token_type.h build/decimal_token.h build/decimal_token_automata.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_token_automata.c -o build/decimal_token_automata.i  2>&1

build/decimal_token_input_buffering.i: build/decimal_token_input_buffering.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal_token_input_buffering.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_token_input_buffering.c -o build/decimal_token_input_buffering.i  2>&1

build/decimal_token_parser.i: build/decimal_token_parser.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_token_type.h build/decimal_token.h build/decimal_token_automata.h build/decimal_token_input_buffering.h build/decimal_token_parser.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_token_parser.c -o build/decimal_token_parser.i  2>&1

build/decimal_token_type.i: build/decimal_token_type.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal_token_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_token_type.c -o build/decimal_token_type.i  2>&1

build/decimal_vm.i: build/decimal_vm.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_stack.h build/decimal_vm.h build/decimal_bytecode_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/decimal_vm.c -o build/decimal_vm.i  2>&1

build/main.i: build/main.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/main.h build/decimal_token_input_buffering.h build/decimal_token.h build/decimal_token_parser.h build/decimal_data_generation_003_from_syntax_filtering.h build/decimal_bytecode_type.h build/decimal_stack.h build/decimal_vm.h build/main_options.ci build/main_tests.ci 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -E build/main.c -o build/main.i  2>&1






build_o: build build/decimal.o build/decimal_bytecode_type.o build/decimal_data_generation_003_from_syntax_filtering.o build/decimal_stack.o build/decimal_syntax_filtering_engine.o build/decimal_token.o build/decimal_token_automata.o build/decimal_token_input_buffering.o build/decimal_token_parser.o build/decimal_token_type.o build/decimal_vm.o build/main.o 

build/decimal.o: build/decimal.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_print.ci build/decimal_inc_and_dec.ci build/decimal_shift.ci build/decimal_tilde.ci build/decimal_add.ci build/decimal_sub_and_neg.ci build/decimal_mult.ci build/decimal_div.ci build/decimal_tests.ci 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal.c -o build/decimal.o  2>&1

build/decimal_bytecode_type.o: build/decimal_bytecode_type.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_bytecode_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_bytecode_type.c -o build/decimal_bytecode_type.o  2>&1

build/decimal_data_generation_003_from_syntax_filtering.o: build/decimal_data_generation_003_from_syntax_filtering.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_token.h build/decimal_token_type.h build/decimal_syntax_filtering_engine.h build/decimal_data_generation_003_from_syntax_filtering.h build/decimal_bytecode_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_data_generation_003_from_syntax_filtering.c -o build/decimal_data_generation_003_from_syntax_filtering.o  2>&1

build/decimal_stack.o: build/decimal_stack.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_stack.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_stack.c -o build/decimal_stack.o  2>&1

build/decimal_syntax_filtering_engine.o: build/decimal_syntax_filtering_engine.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_token_type.h build/decimal_token.h build/decimal_syntax_filtering_engine.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_syntax_filtering_engine.c -o build/decimal_syntax_filtering_engine.o  2>&1

build/decimal_token.o: build/decimal_token.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal_token.h build/decimal_token_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_token.c -o build/decimal_token.o  2>&1

build/decimal_token_automata.o: build/decimal_token_automata.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal_token_type.h build/decimal_token.h build/decimal_token_automata.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_token_automata.c -o build/decimal_token_automata.o  2>&1

build/decimal_token_input_buffering.o: build/decimal_token_input_buffering.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal_token_input_buffering.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_token_input_buffering.c -o build/decimal_token_input_buffering.o  2>&1

build/decimal_token_parser.o: build/decimal_token_parser.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_token_type.h build/decimal_token.h build/decimal_token_automata.h build/decimal_token_input_buffering.h build/decimal_token_parser.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_token_parser.c -o build/decimal_token_parser.o  2>&1

build/decimal_token_type.o: build/decimal_token_type.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal_token_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_token_type.c -o build/decimal_token_type.o  2>&1

build/decimal_vm.o: build/decimal_vm.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/decimal_stack.h build/decimal_vm.h build/decimal_bytecode_type.h 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/decimal_vm.c -o build/decimal_vm.o  2>&1

build/main.o: build/main.c build/lib__01__pre_header.ci build/lib__02__header.ci build/lib__03.ci build/lib__04__string_stack.ci build/lib__05__error_state.ci build/lib__06__exception.ci build/decimal_global.h build/decimal.h build/main.h build/decimal_token_input_buffering.h build/decimal_token.h build/decimal_token_parser.h build/decimal_data_generation_003_from_syntax_filtering.h build/decimal_bytecode_type.h build/decimal_stack.h build/decimal_vm.h build/main_options.ci build/main_tests.ci 
	cc -std=c99 -D_THREAD_SAFE -D_REENTRANT -D __DEBUG__ -D DEBUG -O0  -fmessage-length=0 -fdiagnostics-show-location=once -fdiagnostics-show-option -fstack-check  -fverbose-asm -ffreestanding -feliminate-unused-debug-types  -Wall -W -Wextra  -Werror -Wfatal-errors  -Werror-implicit-function-declaration -Wparentheses -Wimplicit -Wreturn-type -Wcomment -Wpointer-arith -Wchar-subscripts -Wimplicit-int -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wmultichar -Wsequence-point -Wreturn-type -Wstrict-prototypes -Wpacked -Wcast-qual -Winline -Wformat-nonliteral -Wwrite-strings -Wmissing-field-initializers -Wsign-compare  -Wformat-zero-length -Wswitch -Wswitch-enum -Wswitch-default -Wnested-externs -Wunknown-pragmas  -gfull -W -Wextra -Wnewline-eof -Wno-unsequenced         -fno-exceptions -fno-omit-frame-pointer  -fno-builtin -fno-builtin-printf -fno-builtin-abs -fno-builtin-strcpy -fno-builtin-strcat -fno-builtin-strlen -fno-builtin-bzero -fno-builtin-memset -fno-builtin-memcpy -fno-builtin-assert -fno-builtin-tolower -fno-builtin-toupper -fno-builtin-log -fno-builtin-alloca -fno-common -fno-exceptions -fno-non-call-exceptions -fno-asynchronous-unwind-tables -fno-inline -fno-inline-functions -fno-inline-functions  -Wno-cast-align -Wno-system-headers  -Wno-undef -Wno-redundant-decls -Wno-unused -Wno-unused-parameter -Wno-unused-function -Wno-switch-default -Wno-format-nonliteral    -c build/main.c -o build/main.o  2>&1















