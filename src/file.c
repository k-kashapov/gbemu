#include <sys/stat.h>
#include <stdio.h>
#include "general.h"
#include "file.h"

size_t file_len(const char name[static 1]) {
    struct stat res;
    stat(name, &res);
    return res.st_size;
}

int readFile(void *dst, const char name[static 1], unsigned max_len) {
    size_t len = file_len(name);
    if (len > max_len) {
        fprintf(stderr, "File too long: %lu > %u\n", len, max_len);
        return -1;
    }

    DBG_PRINT("File size = %lu\n"
              "Opening...\n", len);

    FILE *file = fopen(name, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file: %s\n", name);
        return FILE_OPEN_ERR;
    }

    DBG_PRINT("Opened. Reading...\n");

    int read_bytes = fread(dst, 1, len, file);
    fclose(file);

    DBG_PRINT("Read %d bytes\n", read_bytes);

    ((char *)dst)[read_bytes] = '\0';

    return read_bytes;
}
