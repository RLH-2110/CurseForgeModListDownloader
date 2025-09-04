#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include "defines.h"

CURL *curl;
CURLcode res;

void init(){
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); /* Follow redirects */
}

void deinit(){
	 curl_easy_cleanup(curl);
}

#define URL_PART1 "https://www.curseforge.com/api/v1/mods/"
#define URL_PART2 "/files/"
#define URL_PART3 "/download"

bool download_file(char* projectId, char* fileId, char* output, bool quiet) {

    FILE *fp;
    char *url;
    char *filename;
    char *outfilename = NULL;

    if (!fileId){
    	puts("Error: could not get a mod, because the fileId was missing!");
    	return false;
    }
    if(!projectId){
    	puts("Error: could not get a mod, because the projectId was missing!");
    	return false;
	}

    url = malloc(strlen(projectId)+strlen(fileId)+sizeof(URL_PART1)+sizeof(URL_PART2)+sizeof(URL_PART3)); /*"https://www.curseforge.com/api/v1/mods/248787/files/6680857/download";*/
	strcpy(url,URL_PART1);
    strcpy(url+strlen(url),projectId);
    strcpy(url+strlen(url),URL_PART2);
    strcpy(url+strlen(url),fileId);
    strcpy(url+strlen(url),URL_PART3);
    

    filename = malloc(strlen(fileId)+strlen(".jar")+1);
    strcpy(filename,fileId);
    strcpy(filename+strlen(fileId),".jar");

    constuct_filename(output,filename, &outfilename);
    if (outfilename == NULL)
    	return;

    if (curl) {
        fp = fopen(outfilename, "wb");
        if(!fp) {
            printf("Error: could not create file for mod %s/%s\n",projectId,fileId);
            return false;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
       
        fclose(fp);
        if(res != CURLE_OK)
            printf("Error: download failed: %s\n", curl_easy_strerror(res));
        else{
        	if (!quiet)
            	printf("downloaded mod %s/%s\n",projectId,fileId);
        }
    }
    return true;
}
