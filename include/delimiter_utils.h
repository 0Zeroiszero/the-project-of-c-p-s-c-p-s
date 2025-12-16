#ifndef DELIMITER_UTILS_H
#define DELIMITER_UTILS_H

/**
 * 
 * CUSTOM FUNGSI ASLI C
 * 
 */

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


/**
 * Membersihkan buffer input dari karakter yang tersisa setelah pembacaan input
 * @note Fungsi ini digunakan untuk menghindari masalah buffer overflow saat membaca input dari stdin
 * @return Tidak ada nilai kembali
 */
void
clear_input_buffer(void);


#endif