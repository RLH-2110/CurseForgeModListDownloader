#ifndef INCLUDED_BASE_H
#define INCLUDED_BASE_H

#include "int.h"
#include "defines.h"
#include <stdio.h>

typedef struct _Mod{
	char *ProjectId;
	char *FileId;
	struct _Mod *next;
} Mod; 

typedef struct _PackMetadata{
	char *minecraftVersion;
	char *primaryModLoader;
	uint32 reccomendedRam;
	char *manifestVersion;
	char *packName;
	char *packVersion;
	char *packAuthor;
	Mod  *mods;
	char *overrides;

} PackMetadata;

PackMetadata get_pack_metadata(FILE* reader);
void print_pack_metadata(PackMetadata* data);


void init();
void deinit();
bool download_file(char* projectId, char* fileId, char* output, bool quiet);


void constuct_filename(char* base_path, char* filename, char** memory);

/* INCLUDED_BASE_H */
#endif