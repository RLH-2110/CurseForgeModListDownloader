#ifdef OS_POSIX

#include <sys/stat.h>
#include <sys/types.h>
#include "../../defines.h"

bool dir_exists(char const * const path) {
    struct stat info;
    if (stat(path, &info) != 0)
        return 0;
    return S_ISDIR(info.st_mode);
}

bool make_dir(const char *path) {
    return mkdir(path, 0755) == 0; /* rwxr-xr-x */
}

#endif

typedef int happy_fsPosix_c; /* ISO C forbids an empty translation unit */

