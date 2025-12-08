#include "app.h"
#include "crud_utils.h"
#include "files_utils.h"
#include "saving.h"
#include "sorting.h"

int main() {
    daftar_tugas* tasks = NULL;
    int count = 0;
    int menu_state = 0; // LOCK STATE: 0=Menu Utama, 1=Menu Tugas, 2=Menu Pengurutan
    int pilihan = 0;
    const char* filename = "tugas_saya.txt";

    // Load data dari file jika ada
    if (cek_file_ada(filename)) {
        baca_tugas_dari_file(filename, &tasks, &count);
    }

    // Main loop - akan berjalan sampai user pilih 0 di menu utama
    while (1) {
        // =========================
        // TAMPILKAN MENU SESUAI STATE
        // =========================
        switch (menu_state) {
            case 0: // Menu Utama (selalu tampilkan opsi 0, 1, 2)
                {
                    int dummy = 0; // Selalu pass 0 agar tidak ada bug dari menu_utama
                    menu_utama(&dummy);
                    printf("NOTIFIKASI\n\n");
                    notifikasi_awal_screen(tasks, count);
                }
                break;
            case 1: // Menu Tugas (CRUD)
                clear_screen();
                menu_pilihan_dan_edit_tugas();
                printf("TUGAS SAYA\n\n");

                tampilkan_daftar_tugas(tasks, count);
                break;
            case 2: // Menu Pengurutan
                clear_screen();
                menu_pengurutan();
                printf("TUGAS SAYA\n\n");

                tampilkan_daftar_tugas(tasks, count);
                break;
        }

        // =========================
        // TERIMA INPUT USER
        // =========================
        printf("\n\nPilihan menu: ");
        scanf("%d", &pilihan);

        // =========================
        // PROSES INPUT BERDASARKAN STATE YANG TERKUNCI
        // =========================
        switch (menu_state) {
            case 0: // DI MENU UTAMA
                if (pilihan == 1) {
                    menu_state = 1; // Pindah ke menu tugas
                } else if (pilihan == 2) {
                    menu_state = 2; // Pindah ke menu pengurutan
                } else if (pilihan == 0) {
                    // Simpan dan keluar
                    simpan_ke_file(filename, tasks, count);
                    printf("Data berhasil disimpan. Program selesai.\n");
                    goto cleanup; // Keluar dari loop
                }
                break;

            case 1: // DI MENU TUGAS (CRUD)
                if (pilihan == 1) {
                    clear_screen();
                    menu_tambah_tugas(&tasks, &count);
                    simpan_ke_file(filename, tasks, count);
                } else if (pilihan == 2) {
                    clear_screen();
                    menu_hapus_tugas(&tasks, &count);
                    simpan_ke_file(filename, tasks, count);
                } else if (pilihan == 3) {
                    clear_screen();
                    menu_edit_tugas(tasks, count);
                    simpan_ke_file(filename, tasks, count);
                } else if (pilihan == 4) {
                    menu_state = 2; // Menuju pengurutan
                } else if (pilihan == 5 || pilihan == 0) {
                    menu_state = 0; // Kembali ke utama
                }
                break;

            case 2: // DI MENU PENGURUTAN
                if (pilihan == 1) {
                    sortir_by_name(tasks, count);
                    simpan_ke_file(filename, tasks, count);
                } else if (pilihan == 2) {
                    sortir_by_status_then_deadline(tasks, count);
                    simpan_ke_file(filename, tasks, count);
                } else if (pilihan == 3 || pilihan == 0) {
                    menu_state = 0; // Kembali ke utama
                }
                break;
        }

        // Bersihkan sisa input di buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

    } // End while

cleanup:
    free(tasks);
    return 0;
}