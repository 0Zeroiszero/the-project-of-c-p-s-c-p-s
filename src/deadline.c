#include <stdio.h>
#include <time.h>

#include "deadline.h"

static int 
teks_sama(const char* a, const char* b) {
    int i = 0;
    while (1) {
        if (a[i] != b[i]) return 0;
        if (a[i] == '\0' && b[i] == '\0') return 1;
        i++;
    }
}