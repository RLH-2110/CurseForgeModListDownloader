#include "base.h"
#include "defines.h"
#include "int.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* mstrdup(char const * const str){
	char* ret;
	if (str == NULL)
		return NULL;

	ret = malloc(strlen(str)+1);
	if (ret == NULL){
		puts("Memory error occured while duplicating strings!");
		return "{MEMORY ERROR}";
	}
	strcpy(ret,str);
	return ret;

}

char* extract_string(const char* buffer, const char* key) {
	char *pos;
	char *end;
	char *res;
	size_t len;

    pos = strstr(buffer, key);
    if (!pos) return NULL;
    pos += strlen(key);
    while (*pos && (*pos==' ' || *pos==':' || *pos=='\"')) pos++;
    end = pos;
    while (*end && *end != '\"' && *end != ',' && *end != '\n') end++;
    len = end - pos;
    res = malloc(len+1);
    strncpy(res, pos, len);
    res[len] = '\0';
    return res;
}

unsigned int extract_uint(const char* buffer, const char* key) {
	unsigned int val;
    char *pos = strstr(buffer, key);

    if (!pos) return 0;
    sscanf(pos + strlen(key), " : %u", &val);
    return val;
}

PackMetadata get_pack_metadata(FILE* reader) {
	long len;
	char *buffer;
	PackMetadata ret;
	char *modLoaderPos;
	Mod *head;
    Mod **cur;
    char *filesPos;
    char *p;
    char *filePos;
    char tmp[64];

    fseek(reader, 0, SEEK_END);
    len = ftell(reader);
    fseek(reader, 0, SEEK_SET);
    
    buffer = malloc(len + 1);
    fread(buffer, 1, len, reader);
    buffer[len] = 0;

    ret.minecraftVersion = extract_string(buffer, "\"version\"");
    
    /* get primary loader */
    modLoaderPos = strstr(buffer, "\"modLoaders\"");
    ret.primaryModLoader = extract_string(modLoaderPos, "\"id\"");
    
    ret.reccomendedRam = extract_uint(buffer, "\"recommendedRam\"");
    ret.manifestVersion = extract_string(buffer, "\"manifestVersion\"");
    ret.packName = extract_string(buffer, "\"name\"");
    ret.packVersion = extract_string(buffer, "\"version\"");
    ret.packAuthor = extract_string(buffer, "\"author\"");
    ret.overrides = extract_string(buffer, "\"overrides\"");

    /* Parse mods */
    head = NULL;
    cur = &head;
    filesPos = strstr(buffer, "\"files\"");
    if (filesPos) {
        p = filesPos;
        while ((p = strstr(p, "\"projectID\""))) {
            Mod *m = malloc(sizeof(Mod));
            sscanf(p, "\"projectID\": %63s", tmp);
            m->ProjectId = mstrdup(tmp);
            /*dirty fix*/
    		if (m->ProjectId[strlen(m->ProjectId)-1] == ',')
    			m->ProjectId[strlen(m->ProjectId)-1] = '\0';

            filePos = strstr(p, "\"fileID\"");
            sscanf(filePos, "\"fileID\": %63s", tmp);
            m->FileId = mstrdup(tmp);
            /*dirty fix*/
    		if (m->FileId [strlen(m->FileId )-1] == ',')
    			m->FileId [strlen(m->FileId )-1] = '\0';

            m->next = NULL;
            *cur = m;
            cur = &m->next;
            p = filePos + 1;
        }
    }
    ret.mods = head;

    free(buffer);
    return ret;
}

void print_pack_metadata(PackMetadata* data){

    puts("Pack Metadata:");

    if (!data) {
        puts("\t{NULL}");
        return;
    }

    /* debug stuff, not needed for end user*/
    /* print mods */
    /*
    puts("\tMods:");
    if (!data->mods) {
        puts("\t\t{NULL}");
    } else {
        Mod *m = data->mods;
        while (m) {
            fputs("\t\tProject ID: ", stdout);
            puts(m->ProjectId ? m->ProjectId : "{NULL}");

            fputs("\t\tFile ID: ", stdout);
            puts(m->FileId ? m->FileId : "{NULL}");

            m = m->next;
        }
    }
	*/

    fputs("\tMinecraft Version: ", stdout);
    puts(data->minecraftVersion ? data->minecraftVersion : "{NULL}");

    fputs("\tPrimary Mod Loader: ", stdout);
    puts(data->primaryModLoader ? data->primaryModLoader : "{NULL}");

    printf("\tRecommended RAM: %u MB\n", data->reccomendedRam);

    fputs("\tManifest Version: ", stdout);
    puts(data->manifestVersion ? data->manifestVersion : "{NULL}");

    fputs("\tPack Name: ", stdout);
    puts(data->packName ? data->packName : "{NULL}");

    fputs("\tPack Version: ", stdout);
    puts(data->packVersion ? data->packVersion : "{NULL}");

    fputs("\tPack Author: ", stdout);
    puts(data->packAuthor ? data->packAuthor : "{NULL}");

/* debug stuff, not needed for end user*/
/* 
    fputs("\tOverrides: ", stdout);
    puts(data->overrides ? data->overrides : "{NULL}");
*/

}