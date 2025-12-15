#ifndef SAVING_H
#define SAVING_H

#include "crud_utils.h"

/**
 * @brief Menyimpan daftar tugas ke file
 * 
 * @param filename Nama file tempat menyimpan data
 * @param tasks Array daftar tugas
 * @param count Jumlah tugas dalam array
 * @return int 0 jika berhasil, -1 jika gagal
 */
int 
simpan_ke_file(const char* filename, daftar_tugas* tasks, int count);
#endif