#include "../../defines.h"

/* checks if the path is a dir, returns 0 if false, and non-zero if true*/
bool dir_exists(char const * const path);

/* creates a directory, returns true if successfull, and 0 / false on error */
bool make_dir(const char *path);