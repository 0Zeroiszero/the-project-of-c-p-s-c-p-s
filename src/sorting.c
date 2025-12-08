#include <stdio.h>
#include "sorting.h"

/**
 * Fungsi untuk menukar dua tugas
 */
static 
void tukar_tugas(daftar_tugas* a, daftar_tugas* b) {
    daftar_tugas temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Fungsi untuk membandingkan dua string (case-insensitive)
 * Return: -1 jika a < b, 0 jika a == b, 1 jika a > b
 */
static 
int bandingkan_string(const char* str1, const char* str2) {
    int i = 0;
    
    while (str1[i] != '\0' && str2[i] != '\0') {
        char c1 = str1[i];
        char c2 = str2[i];
        
        // Konversi ke huruf kecil jika huruf besar
        if (c1 >= 'A' && c1 <= 'Z') {
            c1 = c1 + 32;
        }
        if (c2 >= 'A' && c2 <= 'Z') {
            c2 = c2 + 32;
        }
        
        if (c1 < c2) return -1;
        if (c1 > c2) return 1;
        i++;
    }
    
    // Cek panjang string
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;
    }
    if (str1[i] == '\0') {
        return -1;
    }
    return 1;
}

// ==================== FUNGSI SORTING UTAMA ====================

/**
 * Mengurutkan tugas berdasarkan NAMA (A-Z) menggunakan Selection Sort
 */
void 
sortir_by_name(daftar_tugas* tasks, int count) {
    // Validasi input
    if (tasks == NULL || count <= 1) {
        return;
    }
    
    // Selection Sort
    for (int i = 0; i < count - 1; i++) {
        int indeks_terkecil = i;
        
        for (int j = i + 1; j < count; j++) {
            // Bandingkan nama tugas
            if (bandingkan_string(tasks[j].nama, tasks[indeks_terkecil].nama) < 0) {
                indeks_terkecil = j;
            }
        }
        
        // Jika ditemukan nama yang lebih kecil, tukar posisi
        if (indeks_terkecil != i) {
            tukar_tugas(&tasks[i], &tasks[indeks_terkecil]);
        }
    }
}

/**
 * Mengurutkan tugas berdasarkan DEADLINE (terdekat dari hari ini)
 * Menggunakan Bubble Sort
 */
void 
sortir_by_deadline(daftar_tugas* tasks, int count) {
    // Validasi input
    if (tasks == NULL || count <= 1) {
        return;
    }
    
    // Dapatkan waktu sekarang
    time_t sekarang = waktu_sekarang();
    
    // Bubble Sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            // Hitung selisih deadline dengan hari ini
            double selisih_j = hitung_selisih_waktu(tasks[j].tanggal_deadline_unix, sekarang);
            double selisih_j1 = hitung_selisih_waktu(tasks[j + 1].tanggal_deadline_unix, sekarang);
            
            // Urutkan dari yang selisihnya paling kecil (paling dekat deadline)
            // Jika selisih negatif = sudah lewat deadline
            if (selisih_j > selisih_j1) {
                tukar_tugas(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}

/**
 * Fungsi sorting gabungan: urut berdasarkan nama, lalu deadline
 */
void 
sortir_by_name_then_deadline(daftar_tugas* tasks, int count) {
    if (tasks == NULL || count <= 1) {
        return;
    }
    
    // Pertama, urutkan berdasarkan deadline
    sortir_by_deadline(tasks, count);
    
    // Kemudian, dalam grup deadline yang sama, urutkan berdasarkan nama
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            // Cek jika deadline sama (dalam toleransi 1 hari = 86400 detik)
            double selisih_deadline = hitung_selisih_waktu(tasks[i].tanggal_deadline_unix, tasks[j].tanggal_deadline_unix);
            
            if (selisih_deadline >= -86400 && selisih_deadline <= 86400) {
                // Deadline sama atau hampir sama, urutkan berdasarkan nama
                if (bandingkan_string(tasks[i].nama, tasks[j].nama) > 0) {
                    tukar_tugas(&tasks[i], &tasks[j]);
                }
            }
        }
    }
}

/**
 * Fungsi untuk mengurutkan berdasarkan status (belum selesai dulu), lalu deadline
 */
void 
sortir_by_status_then_deadline(daftar_tugas* tasks, int count) {
    if (tasks == NULL || count <= 1) {
        return;
    }
    
    // Urutkan berdasarkan deadline terlebih dahulu
    sortir_by_deadline(tasks, count);
    
    // Kemudian urutkan berdasarkan status
    // Pindahkan semua yang belum selesai ke depan
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            // Cek status
            int status_j_belum_selesai = 0;
            int status_j1_belum_selesai = 0;
            
            // Manual check untuk status "belum selesai"
            const char* belum_selesai = "belum selesai";
            int k = 0;
            
            // Cek tasks[j]
            while (tasks[j].status[k] != '\0' && belum_selesai[k] != '\0') {
                if (tasks[j].status[k] != belum_selesai[k]) {
                    break;
                }
                k++;
            }
            if (tasks[j].status[k] == '\0' && belum_selesai[k] == '\0') {
                status_j_belum_selesai = 1;
            }
            
            // Cek tasks[j+1]
            k = 0;
            while (tasks[j + 1].status[k] != '\0' && belum_selesai[k] != '\0') {
                if (tasks[j + 1].status[k] != belum_selesai[k]) {
                    break;
                }
                k++;
            }
            if (tasks[j + 1].status[k] == '\0' && belum_selesai[k] == '\0') {
                status_j1_belum_selesai = 1;
            }
            
            // Jika tasks[j] selesai dan tasks[j+1] belum selesai, tukar
            if (!status_j_belum_selesai && status_j1_belum_selesai) {
                tukar_tugas(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}