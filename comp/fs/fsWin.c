/* I know the w is missing, I just like to call it WinDos */
#ifdef OS_WINDOS 

#include <sys/stat.h>
#include "../../defines.h"

bool dir_exists(char const * const path) {
    struct _stat info;
    if (_stat(path, &info) != 0)
        return 0;
    return _S_ISDIR(info.st_mode) != 0;
}

bool make_dir(const char *path) {
    return _mkdir(path) == 0;
}

#endif

typedef int happy_fsWin_c; /* ISO C forbids an empty translation unit */