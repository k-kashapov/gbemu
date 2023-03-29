#ifndef FILE_H
#define FILE_H
#include <stddef.h>

long file_len(const char name[static 1]);
int  readFile(void *dst, const char name[static 1], long max_len);

#endif //  FILE_H
