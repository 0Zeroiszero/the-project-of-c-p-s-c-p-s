#include <stdio.h>
#include <stdbool.h>

#include "notification.h"
#include "crud_utils.h"
#include "waktu_utils.h"


void
notification_terminal(daftar_tugas daftar[], int count) {
    bool ada_notifikasi = false;

    printf("=== NOTIFIKASI DEADLINE ===\n");

    for(int i = 0; i < count; i++) {
        int sisa_hari = hitung_sisa_hari(daftar[i].tanggal_deadline_unix);

        if(sisa_hari < 0) {
            printf("SUDAH LEWAT: %s - Deadline: %s (Lewat %d hari)\n",
                   daftar[i].nama, daftar[i].tanggal_deadline, -sisa_hari);
            ada_notifikasi = true;
        }
        else if (sisa_hari == 0) {
            printf("HARI INI: %s - Deadline: %s\n",
                   daftar[i].nama, daftar[i].tanggal_deadline);
            ada_notifikasi = true;
        }
        else if(sisa_hari <= 5 && sisa_hari >= 0) {
            printf("%d hari lagi: %s - Deadline: %s\n",
                   sisa_hari, daftar[i].nama, daftar[i].tanggal_deadline);
            ada_notifikasi = true;
        }
    }

    if (count > 0 && !ada_notifikasi) {
        printf("Tidak ada tugas yang dekat deadline\n");
    }
    else if (count == 0) {
        printf("Daftar tugas kosong.\n");
    }
}