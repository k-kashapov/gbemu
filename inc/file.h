#ifndef FILE_H
#define FILE_H
#include <stddef.h>

size_t file_len(const char name[static 1]);
int    readFile(void *dst, const char name[static 1]);

#endif //  FILE_H