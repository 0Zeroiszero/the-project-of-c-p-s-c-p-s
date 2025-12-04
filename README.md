# Dokumentasi Fungsi CRUD
## Arahan implementasi kode untuk membuat:
[lihat format.txt](http://github.com/0Zeroiszero/the-project-of-c-p-s-c-p-s/blob/main/debug/format.txt "lihat format.txt")
[lihat contoh.txt](http://github.com/0Zeroiszero/the-project-of-c-p-s-c-p-s/blob/main/debug/contoh.txt "lihat contoh.txt")
1. Membuat algoritma pengurutan
2. Membuat algoritma menyimpan file (saving)
3. Membuat algoritma deadline
4. Membuat algoritma notifikasi
------------
### Isi contoh.txt
```
    Belajar Python | Mengerjakan latihan fungsi dan modul | 15-12-2024 | belum selesai | 1734220800 | 01-12-2024
    Desain Poster | Buat poster acara seminar teknologi | 10-12-2024 | selesai | 1733788800 | 25-11-2024
    Riset Pasar | Analisis kompetitor produk digital | 20-12-2024 | belum selesai | 1734652800 | 30-11-2024
    Presentasi Kelompok | Slide presentasi proyek akhir | 05-12-2024 | selesai | 1733356800 | 20-11-2024
    Laporan Keuangan | Catatan pengeluaran bulan November | 08-12-2024 | belum selesai | 1733616000 | 02-12-2024
```
### Isi format.txt (acuan contoh.txt)
```
    nama | deskripsi | tanggal_deadline | status: selesai/belum selesai | tanggal_deadline_unix | last_added | last_modified,
```
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
- `waktu_utils.h`

```c
/*
Mendapatkan waktu saat ini dalam format unix timestamp dengan return time_t
*/
time_t waktu_sekarang();
```

### Algoritma Pengurutan
#### Algoritma
Dua algoritma pengurutan: 
1. nama (A-Z)
2. deadline (Deadline terdekat dari hari ini)
```c
// sorting.h
void sortir_by_name(daftar_tugas* tasks, int count);
void sortir_by_deadline(daftar_tugas* tasks, int count);
```
#### Hasil
1. Hasil yang diinginkan
`Pengurutan berdasarkan nama (A-Z)`
```
    Belajar Python | Mengerjakan latihan fungsi dan modul | 15-12-2024 | status: belum selesai | 1734220800 | 01-12-2024 | ,
    Desain Poster | Buat poster acara seminar teknologi | 10-12-2024 | status: selesai | 1733788800 | 25-11-2024 | ,
    Laporan Keuangan | Catatan pengeluaran bulan November | 08-12-2024 | status: belum selesai | 1733616000 | 02-12-2024 | ,
    Presentasi Kelompok | Slide presentasi proyek akhir | 05-12-2024 | status: selesai | 1733356800 | 20-11-2024 | ,
    Riset Pasar | Analisis kompetitor produk digital | 20-12-2024 | status: belum selesai | 1734652800 | 30-11-2024 | ,
```
2. Hasil yang diinginkan `berdasarkan deadline (ascending)`
```
    Presentasi Kelompok | Slide presentasi proyek akhir | 05-12-2024 | status: selesai | 1733356800 | 20-11-2024 | ,
    Laporan Keuangan | Catatan pengeluaran bulan November | 08-12-2024 | status: belum selesai | 1733616000 | 02-12-2024 | ,
    Desain Poster | Buat poster acara seminar teknologi | 10-12-2024 | status: selesai | 1733788800 | 25-11-2024 | ,
    Belajar Python | Mengerjakan latihan fungsi dan modul | 15-12-2024 | status: belum selesai | 1734220800 | 01-12-2024 | ,
    Riset Pasar | Analisis kompetitor produk digital | 20-12-2024 | status: belum selesai | 1734652800 | 30-11-2024 | ,
```
#### Catatan
Download file `crud_utils.c` dan `crud_utils.h` kemudian berikan kepada AI.

deadline diurutkan dengan memanfaatkan `tanggal_deadline_unix` yang terdapat pada struct dan gunakan fungsi `time_t waktu_sekarang();` untuk melihat mana yang terdekat dari hari ini