#ifndef DEADLINE_H
#define DEADLINE_H

#include <waktu_utils.h>
#include <crud_utils.h>

static int
teks_sama(const char* a, const char* b);

/**
 * @brief Menampilkan (ke layar) daftar tugas yang sudah lewat deadline
 * @param tasks pointer ke array daftar_tugas
 * @param count jumlah elemen dalam array tasks
 * @return none
 */
void 
tampilkan_tugas_lewat_deadline(daftar_tugas* tasks, int count);

#endif
