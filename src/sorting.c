#include <time.h>

#include "sorting.h"
#include "waktu_utils.h"
#include "crud_utils.h"


static
void tukar_tugas(daftar_tugas* a, daftar_tugas* b) {
    daftar_tugas temp = *a;

    *a = *b;
    *b = temp;
}


static
int bandingkan_string(const char* str1, const char* str2) {
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        char c1 = str1[i];
        char c2 = str2[i];

        if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;

        if (c1 < c2) return -1;
        if (c1 > c2) return 1;

        i++;
    }

    if (str1[i] == '\0' && str2[i] == '\0') return 0;
    if (str1[i] == '\0') return -1;

    return 1;
}


void
sortir_by_name(daftar_tugas* tasks, int count) {
    if (tasks == NULL || count <= 1) return;

    for (int i = 0; i < count - 1; i++) {
        int indeks_terkecil = i;

        for (int j = i + 1; j < count; j++) {
            if (bandingkan_string(tasks[j].nama, tasks[indeks_terkecil].nama) < 0) {
                indeks_terkecil = j;
            }
        }

        if (indeks_terkecil != i) {
            tukar_tugas(&tasks[i], &tasks[indeks_terkecil]);
        }
    }
}


void
sortir_by_deadline(daftar_tugas* tasks, int count) {
    if (tasks == NULL || count <= 1) return;

    time_t sekarang = waktu_sekarang();

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            double selisih_j = hitung_selisih_waktu(tasks[j].tanggal_deadline_unix, sekarang);
            double selisih_j1 = hitung_selisih_waktu(tasks[j + 1].tanggal_deadline_unix, sekarang);

            if (selisih_j > selisih_j1) {
                tukar_tugas(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}


void
sortir_by_name_then_deadline(daftar_tugas* tasks, int count) {
    if (tasks == NULL || count <= 1) return;

    sortir_by_deadline(tasks, count);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            double selisih_deadline = hitung_selisih_waktu(tasks[i].tanggal_deadline_unix, tasks[j].tanggal_deadline_unix);

            if (selisih_deadline >= -86400 && selisih_deadline <= 86400) {
                if (bandingkan_string(tasks[i].nama, tasks[j].nama) > 0) {
                    tukar_tugas(&tasks[i], &tasks[j]);
                }
            }
        }
    }
}


void
sortir_by_status_then_deadline(daftar_tugas* tasks, int count) {
    if (tasks == NULL || count <= 1) return;

    sortir_by_deadline(tasks, count);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int status_j_belum_selesai = 0;
            int status_j1_belum_selesai = 0;
            const char* belum_selesai = "belum selesai";
            int k = 0;

            while (tasks[j].status[k] != '\0' && belum_selesai[k] != '\0') {
                if (tasks[j].status[k] != belum_selesai[k]) break;
                k++;
            }

            if (tasks[j].status[k] == '\0' && belum_selesai[k] == '\0') status_j_belum_selesai = 1;

            k = 0;
            while (tasks[j + 1].status[k] != '\0' && belum_selesai[k] != '\0') {
                if (tasks[j + 1].status[k] != belum_selesai[k]) break;
                k++;
            }

            if (tasks[j + 1].status[k] == '\0' && belum_selesai[k] == '\0') status_j1_belum_selesai = 1;

            if (!status_j_belum_selesai && status_j1_belum_selesai) {
                tukar_tugas(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}