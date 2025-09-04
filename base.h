#ifndef INCLUDED_BASE_H
#define INCLUDED_BASE_H

#include "int.h"
#include <stdio.h>

typedef struct _Mod{
	char *ProjectId;
	char *FileId;
	struct Mod *next;
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

/* INCLUDED_BASE_H */
#endif