#include <stdio.h>
#include <stdlib.h>

#include "files_utils.h"


char*
baca_file(const char* filename)
{
    FILE* file = fopen(filename, "r");

    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(size + 1);

    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);

    return buffer;
}


int
buat_file_baru(const char* filename) {
    if (filename == NULL) return -1;

    FILE* fp = fopen(filename, "w");

    if (fp == NULL) return -1;

    fclose(fp);

    return 0;
}


int
cek_file_ada(const char* filename)
{
    if (!filename) return 0;

    FILE* file = fopen(filename, "r");

    if (file) {
        fclose(file);
        return 1;
    }

    return 0;
}