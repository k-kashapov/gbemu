#include <sys/stat.h>
#include <stdio.h>
#include "general.h"
#include "file.h"

long file_len(const char name[static 1]) {
    struct stat res;
    stat(name, &res);
    return res.st_size;
}

int readFile(void *dst, const char name[static 1], long max_len) {
    long len = file_len(name);
    if (len > max_len) {
        fprintf(stderr, "File too long: %ld > %ld\n", len, max_len);
        return -1;
    }

    DBG_PRINT("File size = %ld\n"
              "Opening...\n", len);

    FILE *file = fopen(name, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file: %s\n", name);
        return FILE_OPEN_ERR;
    }

    DBG_PRINT("Opened. Reading...\n");

    int read_bytes = (int)fread(dst, 1, (unsigned long)len, file);
    fclose(file);

    DBG_PRINT("Read %d bytes\n", read_bytes);

    ((char *)dst)[read_bytes] = '\0';

    return read_bytes;
}
