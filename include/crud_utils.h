#ifndef CRUD_UTILS_H
#define CRUD_UTILS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Ini fokus non-status (krusial)
 */
typedef struct
{
    char nama[100];
    char deskripsi[100];
    char tanggal_deadline[32]; // dd/mm/yyyy
    char status[24]; //selesai atau belum selesai
    time_t tanggal_deadline_unix; // unix
    time_t last_added; // unix, terakhir ditambahkan
    time_t last_modified; // unix, terakhir diubah

} daftar_tugas;

/**
 * Menambahkan satu tugas baru ke dalam array daftar_tugas yang sudah ada.
 * Array akan di-realloc secara otomatis untuk menampung tugas baru.
 * 
 * @param tasks Pointer ke pointer array daftar_tugas. Akan diperbarui jika realokasi memori berhasil.
 * @param count Pointer ke integer yang menyimpan jumlah tugas saat ini. Akan diperbarui.
 * @param nama Nama untuk tugas baru.
 * @param deskripsi Deskripsi untuk tugas baru.
 * @param tanggal_deadline Tanggal deadline untuk tugas baru dd/mm/yyyy.
 * 
 * @return 0 jika berhasil, -1 jika gagal (misalnya alokasi memori gagal atau input tidak valid).
 */
int
tambah_tugas_ke_daftar(daftar_tugas** tasks, int* count, 
                           const char* nama, 
                           const char* deskripsi, 
                           const char* tanggal_deadline);

/**
 * Mengedit tugas yang sudah ada berdasarkan index
 * @param tasks Array tugas
 * @param count Jumlah tugas (untuk validasi index)
 * @param index Index tugas yang akan diedit (0-based)
 * @param nama Nama baru (NULL jika tidak ingin ubah)
 * @param deskripsi Deskripsi baru (NULL jika tidak ingin ubah)
 * @param tanggal_deadline Deadline baru format "dd/mm/yyyy" (NULL jika tidak ingin ubah)
 * @return 0 jika sukses, -1 jika gagal
 */
int 
edit_tugas(daftar_tugas* tasks, int count, int index,
           const char* nama, const char* deskripsi, const char* tanggal_deadline);

/**
 * Menghapus tugas berdasarkan index
 * @param tasks Pointer ke pointer array daftar_tugas
 * @param count Pointer ke integer jumlah tugas
 * @param index Index tugas yang akan dihapus (0-based)
 * @return 0 jika sukses, -1 jika gagal
 */
int 
hapus_tugas(daftar_tugas** tasks, 
            int* count, int index);

/**
 * @brief Membuat satu entri tugas baru di pointer yang diberikan.
 * @note Gunakan fungsi ***tambah_tugas_ke_daftar*** dan jangan langsung memanggil fungsi ini.
 * 
 * @param tugas Pointer ke struct daftar_tugas yang akan diisi.
 * @param nama Nama tugas.
 * @param deskripsi Deskripsi tugas.
 * @param tanggal_deadline Deadline dalam format "dd/mm/yyyy".
 * @return int Mengembalikan 0 jika sukses, -1 jika gagal.
 */
static 
int daftar_tugas_baru(daftar_tugas *tugas, 
                      const char *nama, 
                      const char *deskripsi, 
                      const char *tanggal_deadline);

/**
 * Validasi string untuk memastikan tidak mengandung delimiter , dan |
 * @return 0 jika aman, -1 jika berbahaya
 */ 
int validasi_teks_bebas_delimiter(const char* str);

/**
 * Membaca file, mem-parsing isinya yang memiliki 7 field, dan mengisinya ke dalam 
 * array dinamis dari struktur `daftar_tugas`.
 * 
 * Fungsi ini membaca seluruh konten file ke dalam memori, kemudian mem-parsing data
 * tugas yang dipisahkan oleh koma (`,`) untuk setiap record dan pipa (`|`) untuk setiap field.
 * Setiap record diharapkan memiliki 5 field yang akan dipetakan langsung ke struct.
 * Memori untuk array tugas akan dialokasikan secara dinamis.
 * 
 * @param filename TIDAK PERLU baca_file; Path ke file yang akan dibaca. File harus berisi data tugas
 *                 dengan format: "nama | deskripsi | tanggal_deadline | status: selesai/belum selesai | tanggal_deadline_unix | last_added | last_modified,".
 * @param tasks    Pointer ke pointer yang akan menunjuk ke array `daftar_tugas`
 *                 yang dialokasikan secara dinamis. **Pemanggil bertanggung
 *                 jawab untuk membebaskan memori ini dengan `free(*tasks)`**.
 * @param count    Pointer ke integer yang akan diisi dengan jumlah total tugas
 *                 yang berhasil diparsing dari file.
 * 
 * @return Mengembalikan 0 jika berhasil, dan -1 jika terjadi kesalahan.
 */
int 
baca_tugas_dari_file(
    const char* filename, 
    daftar_tugas** tasks, 
    int* count);

/**
 * Yang status-status aja wokwokw
 */

typedef enum {
    STATUS_BELUM_SELESAI = 0,
    STATUS_SELESAI = 1,
} status_tugas_t;

#define MARK_SELESAI "selesai"
#define MARK_BELUM_SELESAI "belum selesai"

/**
 * Menandai tugas tertentu sebagai selesai
 * 
 * Mengupdate field status pada tugas dengan index spesifik menjadi "selesai".
 * Melakukan validasi bounds checking untuk mencegah buffer overflow.
 * 
 * @param tasks Pointer ke array tugas (daftar_tugas[])
 * @param count Jumlah total tugas dalam array (untuk validasi index)
 * @param Index tugas yang akan ditandai selesai (0-based)
 * 
 * @return void
 * 
 * @note O(1) complexity - operasi copy dengan ukuran fixed
 * @note Tidak melakukan realloc atau modifikasi struktur data lainnya
 * @note Jika index invalid, fungsi akan return tanpa error (silent fail)
 * @warning Memerlukan tasks[index].status minimal 9 bytes (untuk "selesai" + null terminator)
 * @see my_strcpy() untuk detail safety mechanism copy string
 */
void
tandai_tugas_selesai(daftar_tugas* tasks, int count, int index);

/**
 * Menandai tugas tertentu sebagai belum selesai
 * 
 * Mengupdate field status pada tugas dengan index spesifik menjadi "belum_selesai".
 * Melakukan validasi bounds checking untuk mencegah buffer overflow.
 * 
 * @param tasks Pointer ke array tugas (daftar_tugas[])
 * @param count Jumlah total tugas dalam array (untuk validasi index)
 * @param index Index tugas yang akan ditandai belum selesai (0-based)
 * 
 * @return void
 * 
 * @note O(1) complexity - operasi copy dengan ukuran fixed
 * @note Fungsi ini dapat digunakan untuk "unmark" tugas yang sudah selesai
 * @note Jika index invalid, fungsi akan return tanpa error (silent fail)
 * @warning Memerlukan tasks[index].status minimal 14 bytes (untuk "belum_selesai" + null terminator)
 * @see my_strcpy() untuk detail safety mechanism copy string
 */
void
tandai_tugas_belum_selesai(daftar_tugas* tasks, int count, int index);

/**
 * @return none
 * 
 * @param input menerima masukkan berupa integer 0 - 1
 * @param tasks Pointer ke array tugas (daftar_tugas[])
 * @param count Jumlah total tugas dalam array (untuk validasi index)
 * @param index Index tugas yang akan diubah statusnya (0-based)
 * @brief 0 untuk belum selesai, 1 untuk selesai
 */
void
ubah_status_tugas(unsigned int input, daftar_tugas* tasks, int count, int index);

/**
 * 
 * 
 * 
 * 
 *  ISINYA UNTUK NOTIFIKASI DAN DEADLINE
 * 
 * 
 * 
 * 
 */
#endif