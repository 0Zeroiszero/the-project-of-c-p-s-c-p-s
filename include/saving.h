#ifndef SAVING_H
#define SAVING_H


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


/**
 * Menyimpan tugas ke file dan membersihkan memori sebelum keluar
 * @param tasks Pointer ke array tugas yang akan disimpan
 * @param count Jumlah tugas dalam array
 * @param filename Nama file untuk menyimpan data
 * @return Tidak ada nilai kembali
 * @note Fungsi ini menyimpan data ke file, menampilkan pesan konfirmasi,
 *       dan membebaskan alokasi memori untuk tasks sebelum program selesai
 */
void 
save_and_exit(daftar_tugas* tasks, int count, const char* filename);


#endif