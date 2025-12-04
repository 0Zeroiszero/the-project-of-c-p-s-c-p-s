#include "crud_utils.h"
#include "delimiter_utils.h"
#include "waktu_utils.h"
#include "files_utils.h"

static  
int daftar_tugas_baru(daftar_tugas *tugas,
                  const char *nama, 
                  const char *deskripsi, 
                  const char *tanggal_deadline) 
{
    if (!tugas || !nama || !deskripsi || !tanggal_deadline) {
        return -1;
    }

    if (my_strlen(nama) >= sizeof(tugas->nama) ||
        my_strlen(deskripsi) >= sizeof(tugas->deskripsi) ||
        my_strlen(tanggal_deadline) >= sizeof(tugas->tanggal_deadline)) {
        
        perror("Periksa kembali input");
        return -1;
    }

    if (validasi_teks_bebas_delimiter(nama) != 0 ||
        validasi_teks_bebas_delimiter(deskripsi) != 0 ||
        validasi_teks_bebas_delimiter(tanggal_deadline) != 0) {
        return -1;
    }

    my_strcpy(tugas->nama, nama, sizeof(tugas->nama));
    my_strcpy(tugas->deskripsi, deskripsi, sizeof(tugas->deskripsi));
    my_strcpy(tugas->tanggal_deadline, tanggal_deadline, sizeof(tugas->tanggal_deadline));
    my_strcpy(tugas->status, MARK_BELUM_SELESAI, sizeof(tugas->status)); //

    time_t converted_time = konversi_tanggal(tanggal_deadline);
    if (converted_time == -1) {
        perror("Format tanggal tidak valid, gunakan format DD/MM/YYYY");
        return -1;
    }
    tugas->tanggal_deadline_unix = converted_time;
    tugas->last_added = waktu_sekarang();
    tugas->last_modified = tugas->last_added;
    
    return 0;
}

int
tambah_tugas_ke_daftar(daftar_tugas** tasks, int* count, 
                           const char* nama, 
                           const char* deskripsi, 
                           const char* tanggal_deadline) 
{
    if (!tasks || !count || !nama || !deskripsi || !tanggal_deadline) {
        return -1;
    }

    daftar_tugas tugas_baru_obj;
    if (daftar_tugas_baru(&tugas_baru_obj, nama, deskripsi, tanggal_deadline) != 0) {
        return -1;
    }

    daftar_tugas* temp = realloc(*tasks, (*count + 1) * sizeof(daftar_tugas));
    if (!temp) {
        return -1;
    }

    *tasks = temp;

    (*tasks)[*count] = tugas_baru_obj;

    (*count)++;

    return 0;
}

int 
edit_tugas(daftar_tugas* tasks, int count, int index,
           const char* nama, const char* deskripsi, const char* tanggal_deadline)
{
    // Validasi pointer dan index
    if (!tasks || index < 0 || index >= count) {
        return -1;
    }
    
    daftar_tugas* tugas = &tasks[index]; // Pointer ke tugas yang akan diedit
    
    // Edit nama jika diberikan
    if (nama != NULL) {
        if (my_strlen(nama) >= sizeof(tugas->nama)) {
            perror("Nama terlalu panjang");
            return -1;
        }
        my_strcpy(tugas->nama, nama, sizeof(tugas->nama));
    }
    
    // Edit deskripsi jika diberikan
    if (deskripsi != NULL) {
        if (my_strlen(deskripsi) >= sizeof(tugas->deskripsi)) {
            perror("Deskripsi terlalu panjang");
            return -1;
        }
        my_strcpy(tugas->deskripsi, deskripsi, sizeof(tugas->deskripsi));
    }
    
    // Edit deadline jika diberikan
    if (tanggal_deadline != NULL) {
        // Validasi panjang string
        if (my_strlen(tanggal_deadline) >= sizeof(tugas->tanggal_deadline)) {
            perror("Tanggal deadline tidak valid");
            return -1;
        }
        
        // Konversi tanggal
        time_t converted_time = konversi_tanggal(tanggal_deadline);
        if (converted_time == -1) {
            perror("Format tanggal tidak valid, gunakan format DD/MM/YYYY");
            return -1; // Format tanggal invalid
        }
        
        // Update data
        my_strcpy(tugas->tanggal_deadline, tanggal_deadline, sizeof(tugas->tanggal_deadline));
        tugas->tanggal_deadline_unix = converted_time;
    }
    
    tugas->last_modified = waktu_sekarang();
    
    return 0;
}

int 
hapus_tugas(daftar_tugas** tasks, int* count, int index)
{
    // Validasi pointer dan index
    if (!tasks || !count) {
        return -1;
    }
    
    if (*count == 0) {
        perror("Daftar tugas kosong");
        return -1;
    }
    
    if (index < 0 || index >= *count) {
        perror("Index tidak valid");
        return -1;
    }
    
    // Geser elemen setelah index ke kiri
    for (int i = index; i < *count - 1; i++) {
        (*tasks)[i] = (*tasks)[i + 1];
    }
    
    // Kurangi count
    (*count)--;
    
    // Realloc untuk mengurangi ukuran array
    if (*count > 0) {
        daftar_tugas* temp = realloc(*tasks, (*count) * sizeof(daftar_tugas));
        if (!temp && *count > 0) {  // Gagal realloc tapi masih ada data
            perror("Peringatan: Gagal mengoptimalkan memori setelah penghapusan");
            // Tidak fatal, lanjutkan karena data masih valid
        } else if (temp) {
            *tasks = temp;  // Hanya update jika realloc berhasil
        }
    } else {
        // Jika tidak ada tugas lagi, free dan set ke NULL
        free(*tasks);
        *tasks = NULL;
    }
    
    return 0;
}

static 
int validasi_teks_bebas_delimiter(const char* str) {
    if (!str) return -1;
    
    for (size_t i = 0; i < my_strlen(str); i++) {
        if (str[i] == ',' || str[i] == '|') {
            fprintf(stderr, "Error: Input tidak boleh mengandung koma (,) atau pipa (|)\n");
            return -1;
        }
    }
    return 0;
}

int 
baca_tugas_dari_file(
    const char* filename, 
    daftar_tugas** tasks, 
    int* count)
{
    if (!filename || !tasks || !count) {
        return -1;
    }
    
    char* buffer = baca_file(filename);
    if (!buffer) {
        return -1;
    }
    
    // Hitung jumlah tugas
    int task_count = 0;
    char* p = buffer;
    while (*p) {
        if (*p == ',') task_count++;
        p++;
    }
    task_count++;
    
    // Alokasi memori
    *tasks = (daftar_tugas*)malloc(task_count * sizeof(daftar_tugas));
    if (!*tasks) {
        free(buffer);
        return -1;
    }
    
    // Parse tugas
    char* record = strtok(buffer, ",");
    int i = 0;
    while (record != NULL && i < task_count) {

        while (*record == ' ' || *record == '\t' || *record == '\n') record++;
        
        char* fields[7] = {NULL};
        int field_idx = 0;
        
        char* saveptr;
        char* temp_record = strdup(record);

        char* field = strtok_r(temp_record, "|", &saveptr);
        while (field != NULL && field_idx < 7) {

            while (*field == ' ' || *field == '\t') field++;
            char* end = field + strlen(field) - 1;
            while (end > field && (*end == ' ' || *end == '\t' || *end == '\n')) end--;
            *(end + 1) = '\0';
            
            fields[field_idx++] = field;
            field = strtok_r(NULL, "|", &saveptr);
        }

        if (field_idx == 7) {
            daftar_tugas* current_task = &(*tasks)[i];

            my_strncpy(current_task->nama, fields[0], sizeof(current_task->nama) - 1);
            current_task->nama[sizeof(current_task->nama) - 1] = '\0';

            my_strncpy(current_task->deskripsi, fields[1], sizeof(current_task->deskripsi) - 1);
            current_task->deskripsi[sizeof(current_task->deskripsi) - 1] = '\0';

            my_strncpy(current_task->tanggal_deadline, fields[2], sizeof(current_task->tanggal_deadline) - 1);
            current_task->tanggal_deadline[sizeof(current_task->tanggal_deadline) - 1] = '\0';

            my_strncpy(current_task->status, fields[3], sizeof(current_task->status) - 1);
            current_task->status[sizeof(current_task->status) - 1] = '\0';

            if (strcmp(current_task->status, MARK_SELESAI) != 0) {
                my_strcpy(current_task->status, MARK_BELUM_SELESAI, sizeof(current_task->status));
            }

            time_t deadline_unix = konversi_tanggal(fields[2]);
            current_task->tanggal_deadline_unix = (deadline_unix != -1) ? deadline_unix : 0;
            current_task->last_added = atol(fields[5]);   // field ke-5, bukan ke-4!
            current_task->last_modified = atol(fields[6]);
            
            i++;
        }
        
        free(temp_record);
        record = strtok(NULL, ",");
    }
    
    free(buffer);
    *count = i;
    return 0;
}

/**
 * NGATUR STATUS
 */

void 
tandai_tugas_selesai(daftar_tugas* tasks, int count, int index) 
{
    if (!tasks || index < 0 || index >= count) return;
    my_strcpy(tasks[index].status, MARK_SELESAI, sizeof(tasks[index].status));
}

void 
tandai_tugas_belum_selesai(daftar_tugas* tasks, int count, int index) 
{
    if (!tasks || index < 0 || index >= count) return;
    my_strcpy(tasks[index].status, MARK_BELUM_SELESAI, sizeof(tasks[index].status));
}

void
ubah_status_tugas(unsigned int input, daftar_tugas* tasks, int count, int index)
{
    if (input == STATUS_BELUM_SELESAI) {
        tandai_tugas_belum_selesai(tasks, count, index);
    } else if (input == STATUS_SELESAI) {
        tandai_tugas_selesai(tasks, count, index);
    }
}
