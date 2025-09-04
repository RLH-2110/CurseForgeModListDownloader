#ifndef flagsH
#define flagsH

#include "../int.h"
#include "../defines.h"

/* This file handles the command line flags */


extern uint32 argumentFlags; /* the flags that are set with the command line! */

/* help flag*/
#define ARGPARSE_FLAGS_H 0x00000001

/* path to the unpacked curseforge mod list*/
extern char* cursePath;
#define ARGPARSE_FLAGS_I 0x00000002

/* directory where we want to download into*/
extern char* downloadPath;
#define ARGPARSE_FLAGS_O 0x00000004

/* quiet*/
#define ARGPARSE_FLAGS_Q 0x00000008

/* force*/
#define ARGPARSE_FLAGS_F 0x00000010


#endif

