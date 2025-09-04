#include "defines.h"
#include "argParse/flags.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "argParse/args.h"
#include "comp/fs/fs.h"
#include "base.h"
#include <string.h>
#include <errno.h>

#define MANIFEST_NAME "manifest.json"

void boolean_puts(char* msg, bool print){
	if (print)
		puts(msg);
}

bool hande_dir_already_exists(char* dirname){
	if (dir_exists(dirname) != false){
		puts("Error: directory already exists! please delete it manually! future updates may be able to delete it for you.");
		return true;
	}
}

/* concats base_path and filename, adds a '/' if nessesary. memory is set to NULL on error. frees memory if not NULL*/
void constuct_filename(char* base_path, char* filename, char** memory){
	char* writePtr;

	if (!base_path || !filename) /* base_path and filename cant be NULL*/
		return;

	if (*memory != NULL)
		free(*memory);

	*memory = malloc(strlen(base_path)+1+strlen(filename)+1); /* enough space for the new filename */
	if (*memory == NULL)
		return;

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

	Mod *mod;
	Mod *next;
	bool err;
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
	
	/* read metadata */

	manifest = fopen(filename, "r");
	if (manifest == NULL){
		puts("Error: can not open manifest.json!");
		exit(EXIT_FAILURE);
	}

	metadata = get_pack_metadata(manifest);
	fclose(manifest);

	if (!(argumentFlags & ARGPARSE_FLAGS_Q)){
		print_pack_metadata(&metadata);
	}


	/* set download path */
	if (downloadPath == NULL){
		boolean_puts("-o argument not provided, using pack name...", !(argumentFlags & ARGPARSE_FLAGS_Q)); /* print if not quiet*/
		if (metadata.packName == NULL)
			goto manifest_err;

		downloadPath = metadata.packName;
		if (hande_dir_already_exists(downloadPath) == true)
			goto manifest_err;

		err = !make_dir(downloadPath);

		if (err == true)
		{
			manifest_err:
		
			boolean_puts("cant make a directory with the pack name, defaulting to './mods'...", !(argumentFlags & ARGPARSE_FLAGS_Q)); /* print if not quiet*/
			downloadPath = "mods";

			if (hande_dir_already_exists(downloadPath) == true)
				exit(EXIT_FAILURE);

			err = !make_dir(downloadPath);

			if (err){
				printf("Error: can't create directory!");
				exit(EXIT_FAILURE);
			}
		}
	}

	/* download path is set */

	printf("DEBUG: output: %s\n",downloadPath);

	init();

	if (metadata.mods != NULL){

		mod = metadata.mods;
		while(true){


			download_file(mod->ProjectId,mod->FileId,downloadPath, (argumentFlags & ARGPARSE_FLAGS_Q) );

			next = mod->next;
			free(mod);

			if (next == NULL)
				break;

			mod = next;
		}
	}

	deinit();

}