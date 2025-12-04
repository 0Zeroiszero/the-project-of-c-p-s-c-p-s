#ifndef DELIMITER_UTILS_H
#define DELIMITER_UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>

/**
 * Menyalin string dengan batasan ukuran (versi aman)
 * @param dest Buffer tujuan
 * @param src String sumber
 * @param size Ukuran buffer dest (akan menyalin maks size-1 karakter + null terminator)
 */
void 
my_strcpy(char *dest, const char *src, size_t size);

/**
 * Meniru perilaku std::strncpy
 */
char 
*my_strncpy(char *dest, const char *src, size_t n);

/**
 * Menghitung panjang string
 */
size_t 
my_strlen(const char *s);

#endif