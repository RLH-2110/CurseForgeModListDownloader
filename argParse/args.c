#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../malloc/OOM_malloc.h"

#include "flags.h"


int fetch_flag_arg_count(int argc, char*argv[], int firstIndex); /* counts how many parameters there are after a flag */
void print_help(char* argv0); /* prints help screen */

/* arg = pointer to the raw text of the argument, THIS POINER MUST STAY ALIVE FOR THE ENTIRE RUNTIME!
   list = a pointer to a char** , an array of strings
   listC = pointer to the count of how many elements are in the list */
void append_arg(char *arg, char ***list, int *listC){

	if (!arg || !list){ /* if one param is NULL */
		fputs("ERROR: append_arg does not take NULL!\n",stdout);
		exit(1);
	} 



	if (*list == NULL){

		OOMmalloc_exit_msg(sizeof(char*), *list, "ERROR: append_arg is out of memory!");

		*listC = 1;
		*list[0] = arg; /* set the first element in the list to the argument pointer */	
	}else{
		*listC = *listC + 1;
		if (*listC == 0){
			/* If we got here, then that means there are so many parameters that we had an overflow. That sucks.*/
			fputs("ERROR: too many arguments for a flag! We had an overflow, what the fuck did you do to cause this?\n",stdout);
			exit(1);
		}

		*list = realloc(*list,*listC * sizeof(char*)); /* make space for one more pointer */


		if (*list == NULL){
			fputs("ERROR: append_arg is out of memory (realloc)!\n",stdout);
			exit(1);
		}


		(*list)[*listC - 1] = arg; /* set the last element to the argument pointer */


	}

}



void get_args(int argc, char*argv[]){
	int argI = 1; /* argument index, starts at first argument, ignores filename */
	int i;
	int result;

	/*argumentFlags and other where initalized at startup and are not restet here!*/

	for (;argI + 1 <= argc; argI++){ /* argc is a count, argI is an index thats why we need to increment argI */

		if (argv[argI][0] != '-') /* ignore if its not a flag */
			continue;

		switch (argv[argI][1]){

			/* help */
			case 'h':

			argumentFlags += ARGPARSE_FLAGS_H;

			print_help(argv[0]);
			break;

			/* quiet */
			case 'q':

			argumentFlags += ARGPARSE_FLAGS_Q;
			break;

			/* force */
			case 'f':

			argumentFlags += ARGPARSE_FLAGS_F;
			break;

			/* input */
			case 'i':

				if (argumentFlags & ARGPARSE_FLAGS_I != 0){
					puts("please only use the -i flag once!");
					exit(1);
				}

				result = fetch_flag_arg_count(argc,argv,argI+1);

				if (result != 1){
					fputs("Error: flag -i needs only one argument!\n",stdout);
					print_help(argv[0]);
					exit(1);
				}

				argumentFlags += ARGPARSE_FLAGS_I;				
				cursePath = argv[argI + 1];
				break;

			/* output */
			case 'o':

				if (argumentFlags & ARGPARSE_FLAGS_O != 0){
					puts("please only use the -o flag once!");
					exit(1);
				}

				result = fetch_flag_arg_count(argc,argv,argI+1);

				if (result != 1){
					fputs("Error: flag -o needs only one argument!\n",stdout);
					print_help(argv[0]);
					exit(1);
				}

				argumentFlags += ARGPARSE_FLAGS_O;				
				downloadPath = argv[argI + 1];
				break;
			

			default:
				fprintf(stdout,"Error: unrecognized parameter: %s\n",argv[argI]);
				print_help(argv[0]);
				exit(1);
				
		}
	}

}

/* counts how many parameters there are after a flag */
int fetch_flag_arg_count(int argc, char*argv[], int firstIndex){
	
	int paramCount = 0;
	int i = firstIndex;

	if (firstIndex >= argc)	
		return 0;
	

	for (;i < argc && argv[i][0] != '-';i++)
		paramCount++;

	return paramCount;
}

void print_help(char* argv0){
	fprintf(stdout,"Usage: %s -t [-f row_heights...]\n",argv0);
	fputs("  -i: input - directory where the manifest.json is (defaults to .)\n",stdout);
	fputs("  -o: output - directory where the mods will be saved in (defaults to ./mods)\n",stdout);
	fputs("  -f: force - automatically answer all Y/N options with yes\n",stdout);
	fputs("  -q: quiet - does not print info messages \n",stdout);
	fputs("  -h: help - shows this help screen\n",stdout);
	
}


