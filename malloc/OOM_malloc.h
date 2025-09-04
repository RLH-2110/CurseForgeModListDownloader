#ifndef included_OOM_malloc_h
#define included_OOM_malloc_h

#include <stdlib.h>
#include "../defines.h"

/*
	This file defines macros to quickly handle malloc OOM errors without ignoreing them.

	all these macro functions take a size and a pointer.
	size:the size in bytes for the malloc
	p: the pointer that will get the address of the allocated memory. this will be overwritten by the macro to point at the malloc result
*/


/* malloc, but returns NULL on failure*/
#define OOMmalloc_retnull(size, p) p = malloc(size); \
	if (p == 0) \
		return NULL;

/* malloc but returns a number saved in num on failure*/
#define OOMmalloc_retn(size, p, num) p = malloc(size); \
	if (p == 0) \
		return num;

/* malloc but exits the progamm on failure*/
#define OOMmalloc_exit(size, p) p = malloc(size); \
	if (p == 0) { \
		puts("out of memory"); \
		exit(EXIT_FAILURE); \
	}

/* malloc but exits the progamm on failure with custom message*/
#define OOMmalloc_exit_msg(size, p, msg) p = malloc(size); \
	if (p == 0) { \
		puts(msg); \
		exit(EXIT_FAILURE); \
	}

/* included_OOM_malloc_h */
#endif 
