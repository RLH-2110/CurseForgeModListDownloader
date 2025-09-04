#include "defines.h"
#include "argParse/flags.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "argParse/args.h"
#include "comp/fs/fs.h"
#include "base.h"
#include "settings.h"
#include <string.h>

#define MANIFEST_NAME "manifest.json"

void boolean_puts(char* msg, bool print){
	if (print)
		puts(msg);
}

/* concats base_path and filename, adds a '/' if nessesary. memory is set to NULL on error. frees memory if not NULL*/
void constuct_filename(char* base_path, char* filename, char** memory){
	char* writePtr;

	if (!base_path || !filename) /* base_path and filename cant be NULL*/
		return;

	if (*memory != NULL)
		free(*memory);

	*memory = malloc(strlen(base_path)+1+strlen(filename)+1); /* enough space for the new filename */

	strcpy(*memory,base_path); /* copy base path*/

	/* add / */

	if (strlen(*memory) > 0 && (*memory)[strlen(*memory)]-1 != '/'){ /* if there is no trailing / */
		writePtr = *memory + strlen(*memory);
		*writePtr = '/'; writePtr++;
	}

	/* add filename*/
	strcpy(writePtr,filename);
}

int main(int argc, char *argv[]){

	char* filename = NULL;
	PackMetadata metadata = { 0 };
	FILE *manifest = NULL;

	get_args(argc, argv);

	/*defalt input path*/
	if (cursePath == NULL){
		boolean_puts("-i argument not provided, using default path...", !(argumentFlags & ARGPARSE_FLAGS_Q)); /* print if not quiet*/
		cursePath = ".";
	}

	if (dir_exists(cursePath) == false){
		fputs("Error: directory: ",stdout);
		fputs(cursePath,stdout);
		puts(" does not exist!");
		exit(EXIT_FAILURE);
	}

	constuct_filename(cursePath,MANIFEST_NAME,&filename);
	


	manifest = fopen(filename, "r");
	if (manifest == NULL){
		puts("Error: can not open manifest.json!");
		exit(EXIT_FAILURE);
	}

	metadata = get_pack_metadata(manifest);
	fclose(manifest);

}