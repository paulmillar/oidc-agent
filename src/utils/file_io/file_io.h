#ifndef FILE_IO_H
#define FILE_IO_H

#include "list/list.h"
#include "utils/oidc_error.h"

#include <stdio.h>

oidc_error_t writeFile(const char* filepath, const char* text);
oidc_error_t appendFile(const char* path, const char* text);
char*        readFile(const char* path);
char*        getLineFromFILE(FILE* fp);
int          fileDoesExist(const char* path);
int          dirExists(const char* path);
oidc_error_t createDir(const char* path);
int          removeFile(const char* path);
list_t*      getLinesFromFile(const char* path);

#endif  // FILE_IO_H
