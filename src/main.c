#include "crud_utils.h"

int main() {
    daftar_tugas* tasks = NULL;
    int count = 0;
    if(tambah_tugas_ke_daftar(&tasks, &count, "Nama Tugas", "Deskripsi, | Tugas", "01/01/2024") != 0) {
        printf("Gagal menambahkan tugas\n");
    }

    printf("Nama tugas: %s\n", tasks[0].nama);
    getchar();
    return 0;
}