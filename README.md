# Dokumentasi Fungsi CRUD
## Cara implementasi kode untuk membuat:

1. Membuat algoritma pengurutan
2. Membuat algoritma menyimpan file (saving)
3. Membuat algoritma deadline
4. Membuat algoritma notifikasi
------------

### Daftar Folder dan File
* `/src` - berisikan file dengan ekstensi '.c'
* `/include` - Berisikan file dengan ekstensi '.h'
* `/debug` - Terdapat contoh format yang diperlukan dalam melakukan parsing

### Fungsi dan Struktur 
`/include/`
- `crud_utils.h`
```c
typedef struct {
    char nama[100];
    char deskripsi[100];
    char tanggal_deadline[32];
    char status[24];
    time_t tanggal_deadline_unix;
    time_t last_added;
    time_t last_modified;
} daftar_tugas;
```
    tanggal_deadline; format: dd/mm/yyyy, contoh 23/12/2025
    status; //selesai atau belum selesai
    tanggal_deadline_unix; // unix
    last_added; // unix, terakhir ditambahkan
    last_modified; // unix, terakhir diubah

- `files_utils.h`

```c
/*
Fungsinya membaca file untuk file yang berisikan format (lihat folder debug) untuk struct daftar_tugas. Parameter filename hanya diperbolehkan file dengan ekstensi .txt
*/
char* baca_file(const char* filename);

/*
Mengecek apakah file ada dan dapat dibuka untuk dibaca
parameter filename adalah Nama file yang akan dicek. Return 1 jika file ada, 0 jika tidak ada atau tidak dapat diakses
 */
int cek_file_ada(const char* filename);
```
