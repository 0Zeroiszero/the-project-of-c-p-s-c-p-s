#ifndef APP_H
#define APP_H

#include "crud_utils.h"
#include "notification.h"


/**
 * @brief bersihkan layar
 */
void
clear_screen();


void
handle_menu_tambah_tugas(daftar_tugas** tasks, int* count);


/**
 * @brief menampilkan menu tambah tugas UDAH ADA SCANF
 * @note sub-menu dari menu_pilihan_dan_edit_tugas
 *
 * @param tasks Pointer ke pointer array daftar_tugas
 * @param count Pointer ke integer jumlah tugas
 * @return none
 */
void
menu_tambah_tugas(daftar_tugas** tasks, int* count);


void
handle_menu_hapus_tugas(daftar_tugas** tasks, int* count);


/**
 * @brief menampilkan menu hapus tugas UDAH ADA SCANF
 * @note sub-menu dari menu_pilihan_dan_edit_tugas
 *
 * @param tasks Pointer ke pointer array daftar_tugas
 * @param count Pointer ke integer jumlah tugas
 * @return none
 */
void
menu_hapus_tugas(daftar_tugas** tasks, int* count);


void
handle_menu_edit_tugas(daftar_tugas* tasks, int count);


/**
 * @brief menampilkan menu edit tugas UDAH ADA SCANF
 * @note sub-menu dari menu_pilihan_dan_edit_tugas
 *
 * @param tasks Pointer ke pointer array daftar_tugas
 * @param count Pointer ke integer jumlah tugas
 * @return none
 */
void
menu_edit_tugas(daftar_tugas* tasks, int count);


/**
 * @brief hanya menampilkan menu pilihan dan edit tugas
 * @return none
 */
void
menu_pilihan_dan_edit_tugas();


void
menu_pengurutan();


/**
 * @brief menampilkan menu utama (fungsi ini selalu clear_screen) default 0
 * @note 1 pilihan tugas 2 menu pengurutan
 * @param pilihan pointer ke pilihan menu
 * @return none
 */
void
menu_utama(int* pilihan);


/**
 * @brief menampilkan notifikasi awal di layar terminal
 * @param daftar array daftar_tugas
 * @param count jumlah tugas dalam daftar
 * @return none
 */
void
notifikasi_awal_screen(daftar_tugas daftar[], int count);


/**
 * @brief menampilkan daftar tugas di layar terminal
 * @param tasks array daftar_tugas
 * @param count jumlah tugas dalam daftar
 * @return none
 */
void
tampilkan_daftar_tugas(daftar_tugas* tasks, int count);


/**
 * @brief menampilkan tugas tertentu di layar terminal
 * @param tasks array daftar_tugas
 * @param count jumlah tugas dalam daftar
 * @param index indeks tugas yang akan ditampilkan
 * @return none
 */
void
tampilkan_tugas_tertentu(daftar_tugas* tasks, int count, int index);


/**
 * @brief inisialisasi aplikasi utama
 * @return none
 */
void
app_init();


#endif