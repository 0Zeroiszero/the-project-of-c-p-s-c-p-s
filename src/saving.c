#include <stdio.h>
#include <string.h>
#include "crud_utils.h"
#include "files_utils.h"

int 
simpan_ke_file(const char* filename, daftar_tugas* tasks, int count) {

    if (filename == NULL || tasks == NULL || count < 0) {
        return -1;
    }

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s|%s|%s|%s|%ld|%ld|%ld,\n",
            tasks[i].nama,
            tasks[i].deskripsi,
            tasks[i].tanggal_deadline,
            tasks[i].status,
            (long)tasks[i].tanggal_deadline_unix,
            (long)tasks[i].last_added,
            (long)tasks[i].last_modified
        );
    }

    fclose(fp);
    return 0;
} 