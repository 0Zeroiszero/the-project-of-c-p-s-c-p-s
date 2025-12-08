#include <stdio.h>
#include <time.h>

#include "deadline.h"

static int 
teks_sama(const char* a, const char* b) {
    int i = 0;
    while (1) {
        if (a[i] != b[i]) return 0;
        if (a[i] == '\0' && b[i] == '\0') return 1;
        i++;
    }
}

void tampilkan_tugas_lewat_deadline(daftar_tugas* tasks, int count) {
    printf("=== LIST TUGAS LEWAT DEADLINE ===\n");

    time_t now = waktu_sekarang();

    for (int i = 0; i < count; i++) {
        if (tasks[i].tanggal_deadline_unix < now &&
            teks_sama(tasks[i].status, "belum selesai"))
        {
            time_t tgl = tasks[i].tanggal_deadline_unix;
            struct tm t = dapatkan_waktu_dengan_detail(&tgl);

            printf("%s - Seharusnya %s\n",
                tasks[i].nama,
                tasks[i].tanggal_deadline
            );
        }
    }
}
