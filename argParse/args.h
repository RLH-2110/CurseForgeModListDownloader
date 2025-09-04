#ifndef argsH
#define argsH



/* gets all the arguments and stores them argument flags (flags.h) 
	argumentFlags and other flags are not reset on calling the function, they are initalized in flags.c, but they are never reset!

	argc: amount of arguments
	argv: array of strings
*/
void get_args(int argc, char*argv[]);

/* prints help screen
	argv0: string name of the progamm
*/
void print_help(char* argv0);



#endif

