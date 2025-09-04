#ifndef included_common_defines_h
#define included_common_defines_h

/* /###\ */
/*|Notes|*/
/* \###/ */
#define CALLER_FREES /* The caller frees that poinnter*/
#define FUNCTION_FREES /* the callee frees that pointer*/



/* /##\ */
/*|Util|*/
/* \##/ */
#ifndef NULL
#define NULL 0
#endif

#ifndef bool
typedef short bool;
#endif

#ifndef true
#define true 1
#define false 0
#endif



/*included_common_defines_h*/
#endif