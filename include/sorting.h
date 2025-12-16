#ifndef SORTING_H
#define SORTING_H

#include "crud_utils.h"


/**
 * @brief Mengurutkan array daftar_tugas berdasarkan nama tugas secara alfabet
 * @param tasks pointer ke array daftar_tugas
 * @param count jumlah elemen dalam array tasks
 * @return none
 */
void 
sortir_by_name(daftar_tugas* tasks, int count);


/**
 * @brief Mengurutkan array daftar_tugas berdasarkan tanggal deadline (terdekat dari hari ini)
 * @param tasks pointer ke array daftar_tugas
 * @param count jumlah elemen dalam array tasks
 * @return none
 */
void 
sortir_by_deadline(daftar_tugas* tasks, int count);


/**
 * Fungsi sorting gabungan: urut berdasarkan nama, lalu deadline
 */
void 
sortir_by_name_then_deadline(daftar_tugas* tasks, int count);


/**
 * Fungsi untuk mengurutkan berdasarkan status (belum selesai dulu), lalu deadline
 */
void 
sortir_by_status_then_deadline(daftar_tugas* tasks, int count);


#endif