#ifndef FILES_UTILS_H
#define FILES_UTILS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Membaca seluruh konten file teks
 * 
 * @param filename Nama file yang akan dibaca
 * @return Pointer ke buffer berisi konten file (harus di-free setelah digunakan)
 *         NULL jika gagal membuka file atau alokasi memori
 */
char* 
baca_file(const char* filename);

/**
 * @brief Menyimpan daftar tugas ke file
 * 
 * @param filename Nama file tempat menyimpan data
 * @return int 0 jika berhasil, -1 jika gagal
 */
int 
buat_file_baru(const char* filename);

/**
 * Mengecek apakah file ada dan dapat dibuka untuk dibaca
 * @param filename Nama file yang akan dicek
 * @return 1 jika file ada, 0 jika tidak ada atau tidak dapat diakses
 */
int 
cek_file_ada(const char* filename);

#endif