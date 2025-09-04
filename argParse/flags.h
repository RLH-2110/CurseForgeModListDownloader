#ifndef flagsH
#define flagsH

#include "../int.h"

/* This file handles the command line flags */


extern uint32 argumentFlags; /* the flags that are set with the command line! */

/* help flag*/
#define ARGPARSE_FLAGS_H 0x00000001

/* path to the unpacked curseforge mod list*/
extern char* cursePath;
#define ARGPARSE_FLAGS_C 0x00000002



#endif

