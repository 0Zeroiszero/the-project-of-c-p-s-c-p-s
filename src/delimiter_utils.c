#include "delimiter_utils.h"

/**
 * 
 * CUSTOM FUNGSI ASLI C
 * 
 */
void 
my_strcpy(char *dest, const char *src, size_t size) 
{
    if (!dest || !src || size == 0) return;
    
    size_t i = 0;
    
    while (i < size - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; 
}

char 
*my_strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    
    return dest;
}

size_t 
my_strlen(const char *s) {
    const char *p = s;
    while (*p != '\0') {
        p++;
    }
    return (size_t)(p - s);
}