#ifndef WAKTU_UTILS_H
#define WAKTU_UTILS_H

#include <time.h>
#include <stdbool.h>
#include <stdio.h>

/**
* @brief Mendapatkan waktu sekarang
* @return sebuah time_t, waktu sekarang dalam format Unix timestamp
*/
time_t 
waktu_sekarang();

/**
 * @brief mendapatkan waktu secara lengkap termasuk detik, menit, jam, hari, bulan, dan tahun
 * @param waktu_dalam_unix pointer ke time_t yang merepresentasikan waktu dalam format Unix timestamp
 * @return sebuah struct tm yang berisi detail waktu
 */
struct tm 
dapatkan_waktu_dengan_detail(const time_t* waktu_dalam_unix);

/**
 * @brief Menghitung selisih waktu antara dua timestamp dalam satuan detik.
 *
 * Fungsi ini membungkus pemanggilan difftime() agar lebih mudah digunakan.
 * Hasil berupa nilai floating-point (double) sehingga dapat menampung selisih waktu besar
 * tanpa risiko overflow integer.
 *
 * @param end   Waktu akhir dalam format time_t.
 * @param start Waktu awal dalam format time_t.
 *
 * @return Selisih waktu (end - start) dalam satuan detik sebagai double.
 */
double 
hitung_selisih_waktu(time_t end, time_t start);

/**
 * @brief selisih hari antara waktu saat ini dengan waktu deadline yang diberikan dalam format Unix timestamp (time_t).
 * @param deadline_unix time_t yang merepresentasikan waktu deadline
 * @return Hasil berupa jumlah hari yang dibulatkan ke bawah karena operasi pembagian integer
 */
int 
hitung_sisa_hari(time_t deadline_unix);

/**
 * Mengecek apakah tahun pada tanggal merupakan tahun kabisat
 * @param tahun tahun yang mau dicek
 * @return true jika tahun kabisat, false jika tidak
 */
bool 
cek_kabisat(int tahun);

/**
 * Mengubah string tanggal format "dd/mm/yyyy" menjadi Unix timestamp
 * @param date_str: string dengan format "dd/mm/yyyy" (misal: "04/12/2025")
 * @return Unix timestamp (time_t) jika sukses, -1 jika gagal
 */
time_t 
konversi_tanggal(const char* date_str);

#endif