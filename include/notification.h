#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "crud_utils.h"

/**
 * @brief Menampilkan notifikasi deadline tugas ke terminal (layar)
 * @param daftar array daftar_tugas yang berisi tugas-tugas
 * @param count jumlah elemen dalam array daftar
 * @return none
 */
void
notification_terminal(daftar_tugas daftar[], int count);

#endif
