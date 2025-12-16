#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "app.h"
#include "waktu_utils.h"
#include "files_utils.h"
#include "saving.h"
#include "sorting.h"
#include "delimiter_utils.h"


void
clear_screen()
{
    system("cls");
}


void
handle_menu_tambah_tugas(daftar_tugas** tasks, int* count)
{
    char nama[100];
    char deskripsi[100];
    char tanggal_deadline[32];
    int c;

    while ((c = getchar()) != '\n' && c != EOF);

    printf("Nama tugas: ");
    if (fgets(nama, sizeof(nama), stdin) == NULL) return;
    if (strchr(nama, '\n') == NULL) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Error: Nama terlalu panjang (max %d karakter)\n", (int)sizeof(nama)-1);
        return;
    }
    nama[strcspn(nama, "\n")] = '\0';

    printf("Deskripsi: ");
    if (fgets(deskripsi, sizeof(deskripsi), stdin) == NULL) return;
    if (strchr(deskripsi, '\n') == NULL) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Error: Deskripsi terlalu panjang (max %d karakter)\n", (int)sizeof(deskripsi)-1);
        return;
    }
    deskripsi[strcspn(deskripsi, "\n")] = '\0';

    printf("Deadline (dd/mm/yyyy): ");
    if (fgets(tanggal_deadline, sizeof(tanggal_deadline), stdin) == NULL) return;
    if (strchr(tanggal_deadline, '\n') == NULL) {
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Error: Tanggal terlalu panjang\n");
        return;
    }
    tanggal_deadline[strcspn(tanggal_deadline, "\n")] = '\0';

    if (validasi_teks_bebas_delimiter(nama) != 0) {
        printf("Error: Nama tidak boleh mengandung koma (,) atau pipa (|)\n");
        return;
    }

    if (validasi_teks_bebas_delimiter(deskripsi) != 0) {
        printf("Error: Deskripsi tidak boleh mengandung koma (,) atau pipa (|)\n");
        return;
    }

    if (validasi_teks_bebas_delimiter(tanggal_deadline) != 0) {
        printf("Error: Tanggal tidak boleh mengandung koma (,) atau pipa (|)\n");
        return;
    }

    if (tambah_tugas_ke_daftar(tasks, count, nama, deskripsi, tanggal_deadline) == 0) {
        printf("Tugas berhasil ditambahkan.\n");
    } else {
        printf("Gagal menambahkan tugas (format tanggal mungkin salah).\n");
    }
}


void
menu_tambah_tugas(daftar_tugas** tasks, int* count)
{
    printf("TAMBAH TUGAS\n\n");
    handle_menu_tambah_tugas(tasks, count);
}


void
handle_menu_hapus_tugas(daftar_tugas** tasks, int* count)
{
    char buffer[32];
    unsigned int index;

    while (getchar() != '\n' && !feof(stdin));

    printf("Masukkan urutan nomor tugas yang mau dihapus: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL ||
        sscanf(buffer, "%u", &index) != 1 ||
        index < 1 || index > (unsigned int)*count) {
        printf("Input tidak valid. Harap masukkan angka antara 1 dan %d.\n", *count);
        return;
    }

    tampilkan_tugas_tertentu(*tasks, *count, index - 1);

    printf("apakah kamu yakin? y/n: ");
    char confirm_buf[10];
    if (fgets(confirm_buf, sizeof(confirm_buf), stdin) != NULL && (confirm_buf[0] == 'y' || confirm_buf[0] == 'Y')) {
        printf(hapus_tugas(tasks, count, index - 1) == 0 ?
               "Tugas berhasil dihapus.\n" : "Gagal menghapus tugas.\n");
    } else {
        printf("Penghapusan dibatalkan.\n");
    }
}


void
menu_hapus_tugas(daftar_tugas** tasks, int* count)
{
    printf("HAPUS TUGAS\n\n");
    handle_menu_hapus_tugas(tasks, count);
}


void
handle_menu_edit_tugas(daftar_tugas* tasks, int count)
{
    char buffer[32];
    unsigned int index;
    int c;

    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("Masukkan urutan nomor tugas yang mau diedit: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%u", &index) != 1) {
        printf("Error: Input tidak valid.\n");
        return;
    }

    if (index < 1 || index > count) {
        printf("Error: Nomor urut harus antara 1 dan %d.\n", count);
        return;
    }

    const int idx = index - 1;
    tampilkan_tugas_tertentu(tasks, count, idx);

    printf("INPUT YANG MAU DIEDIT\n\n");

    char nama[100] = "", deskripsi[100] = "", deadline[32] = "", status_str[10] = "";

    printf("Nama tugas (Enter untuk kosong): ");
    fgets(nama, sizeof(nama), stdin); nama[strcspn(nama, "\n")] = '\0';

    printf("Deskripsi (Enter untuk kosong): ");
    fgets(deskripsi, sizeof(deskripsi), stdin); deskripsi[strcspn(deskripsi, "\n")] = '\0';

    printf("Deadline (dd/mm/yyyy, Enter untuk kosong): ");
    fgets(deadline, sizeof(deadline), stdin); deadline[strcspn(deadline, "\n")] = '\0';

    printf("Status (0=belum selesai, 1=selesai, Enter untuk kosong): ");
    fgets(status_str, sizeof(status_str), stdin); status_str[strcspn(status_str, "\n")] = '\0';

    char* nama_ptr = strlen(nama) ? nama : NULL;
    char* desc_ptr = strlen(deskripsi) ? deskripsi : NULL;
    char* deadline_ptr = strlen(deadline) ? deadline : NULL;

    if (nama_ptr && validasi_teks_bebas_delimiter(nama) != 0) {
        printf("Error: Nama mengandung koma/pipa.\n");
        return;
    }

    if (desc_ptr && validasi_teks_bebas_delimiter(deskripsi) != 0) {
        printf("Error: Deskripsi mengandung koma/pipa.\n");
        return;
    }

    if (deadline_ptr && validasi_teks_bebas_delimiter(deadline) != 0) {
        printf("Error: Deadline mengandung koma/pipa.\n");
        return;
    }

    if (edit_tugas(tasks, count, idx, nama_ptr, desc_ptr, deadline_ptr) != 0) {
        printf("Gagal mengedit tugas (format deadline salah).\n");
        return;
    }

    if (strlen(status_str) > 0) {
        unsigned int status;
        if (sscanf(status_str, "%u", &status) != 1 || (status != 0 && status != 1)) {
            printf("Error: Status harus 0 atau 1.\n");
            return;
        }

        ubah_status_tugas(status, tasks, count, idx);
    }

    printf("Tugas berhasil diedit.\n");
}


void
menu_edit_tugas(daftar_tugas* tasks, int count)
{
    printf("EDIT TUGAS\n\n");
    handle_menu_edit_tugas(tasks, count);
}


void
menu_pilihan_dan_edit_tugas()
{
    printf("PILIHAN MENU\n\n");

    printf("1. Penambahan tugas\n");
    printf("2. Penghapusan tugas\n");
    printf("3. Pengeditan tugas\n");
    printf("4. Pengurutan tugas\n");
    printf("5. Kembali dari menu\n\n");
}


void
menu_pengurutan()
{
    printf("PILIHAN MENU\n\n");
    printf("1. Berdasarkan abjad (A-Z)\n");
    printf("2. Berdasarkan tanggal deadline (terdekat)\n");
    printf("3. Kembali dari menu\n\n");
}


void
menu_utama(int* pilihan)
{
    if (pilihan == NULL) {
        int default_pilihan = 0;
        pilihan = &default_pilihan;
    }

    clear_screen();

    printf("PILIHAN MENU\n\n");

    if (*pilihan == 0) {
        printf("1. Menu Tugas\n");
        printf("2. Tampilkan Tugas\n\n");
    } else if (*pilihan == 1) {
        clear_screen();
        menu_pilihan_dan_edit_tugas();
    } else if (*pilihan == 2) {
        clear_screen();
        menu_pengurutan();
    }
}


void
notifikasi_awal_screen(daftar_tugas daftar[], int count)
{
    notification_terminal(daftar, count);
}


void
tampilkan_daftar_tugas(daftar_tugas* tasks, int count)
{
    if (count == 0) printf("Tugas Kosong...");

    for (int i = 0; i < count; i++) {
        int sisa_hari = hitung_sisa_hari(tasks[i].tanggal_deadline_unix);

        printf("[%d]", i + 1);
        printf("\tNama tugas: %s\n", tasks[i].nama);
        printf("\tDeskripsi: %s\n", tasks[i].deskripsi);
        printf("\tDeadline: %s\n", tasks[i].tanggal_deadline);

        if (sisa_hari < 0) {
            printf("\tSudah lewat: %d hari\n", -sisa_hari);
        } else {
            printf("\tSisa hari: %d\n", sisa_hari);
        }

        printf("\tStatus: %s\n\n", tasks[i].status);
    }
}


void
tampilkan_tugas_tertentu(daftar_tugas* tasks, int count, int index)
{
    int sisa_hari = hitung_sisa_hari(tasks[index].tanggal_deadline_unix);

    printf("\nNama tugas: %s\n", tasks[index].nama);
    printf("Deskripsi: %s\n", tasks[index].deskripsi);
    printf("Deadline: %s\n", tasks[index].tanggal_deadline);

    if (sisa_hari < 0) {
        printf("Sudah lewat: %d hari\n", -sisa_hari);
    } else {
        printf("Sisa hari: %d\n", sisa_hari);
    }

    printf("Status: %s\n\n", tasks[index].status);
}


void 
app_init() {
    daftar_tugas* tasks = NULL;
    int count = 0;
    const char* filename = "tugas_saya.txt";

    if (cek_file_ada(filename)) {
        baca_tugas_dari_file(filename, &tasks, &count);
    }

    int menu_state = 0;
    int pilihan = 0;

    while (1) {
        switch (menu_state) {
            case 0:
                menu_utama(&(int){0});
                printf("NOTIFIKASI\n\n");
                notifikasi_awal_screen(tasks, count);
                break;

            case 1:
                clear_screen();
                menu_pilihan_dan_edit_tugas();
                printf("TUGAS SAYA\n\n");
                tampilkan_daftar_tugas(tasks, count);
                break;

            case 2:
                clear_screen();
                menu_pengurutan();
                printf("TUGAS SAYA\n\n");
                tampilkan_daftar_tugas(tasks, count);
                break;
        }

        printf("\n\nPilihan menu: ");

        if (scanf("%d", &pilihan) != 1) {
            clear_input_buffer();
            continue;
        }

        switch (menu_state) {
            case 0:
                switch (pilihan) {
                    case 1:
                        menu_state = 1;
                        break;

                    case 2:
                        menu_state = 2;
                        break;

                    case 0:
                        save_and_exit(tasks, count, filename);
                        return;

                    default:
                        break;
                }

                break;

            case 1:
                switch (pilihan) {
                    case 1:
                        clear_screen();
                        menu_tambah_tugas(&tasks, &count);
                        simpan_ke_file(filename, tasks, count);
                        break;

                    case 2:
                        clear_screen();
                        menu_hapus_tugas(&tasks, &count);
                        simpan_ke_file(filename, tasks, count);
                        break;

                    case 3:
                        clear_screen();
                        menu_edit_tugas(tasks, count);
                        simpan_ke_file(filename, tasks, count);
                        break;

                    case 4:
                        menu_state = 2;
                        break;

                    case 5:
                    case 0:
                        menu_state = 0;
                        break;

                    default:
                        break;
                }

                break;

            case 2:
                switch (pilihan) {
                    case 1:
                        sortir_by_name(tasks, count);
                        simpan_ke_file(filename, tasks, count);
                        break;

                    case 2:
                        sortir_by_status_then_deadline(tasks, count);
                        simpan_ke_file(filename, tasks, count);
                        break;

                    case 3:
                    case 0:
                        menu_state = 0;
                        break;

                    default:
                        break;
                }

                break;
        }

        clear_input_buffer();
    }
}