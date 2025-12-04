#ifndef WAKTU_UTILS_H
#define WAKTU_UTILS_H

#include <time.h>
#include <stdbool.h>
#include <stdio.h>

/*
Mendapatkan waktu saat ini dalam format unix timestamp
*/
time_t 
waktu_sekarang();

/**
 * Mengecek apakah tahun pada tanggal merupakan tahun kabisat
 * @param tahun tahun yang mau dicek
 * @return true jika tahun kabisat, false jika tidak
 */
bool cek_kabisat(int tahun);

/**
 * Mengubah string tanggal format "dd/mm/yyyy" menjadi Unix timestamp
 * @param date_str: string dengan format "dd/mm/yyyy" (misal: "04/12/2025")
 * @return Unix timestamp (time_t) jika sukses, -1 jika gagal
 */
time_t 
konversi_tanggal(const char* date_str);

#endif