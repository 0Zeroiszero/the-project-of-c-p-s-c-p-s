#include "waktu_utils.h"

time_t waktu_sekarang()
{
    return time(NULL);
}

bool cek_kabisat(int tahun)
{
    return (tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0);
}

time_t konversi_tanggal(const char* ddmmyyyy) 
{
    if (!ddmmyyyy) return -1;

    struct tm tm = {0};
    int day, month, year;

    if (sscanf(ddmmyyyy, "%d/%d/%d", &day, &month, &year) != 3) {
        return -1;
    }

    // Validasi range tahun (1900-2100 untuk to-do list realistis)
    if (year < 1900 || year > 2100) {
        fprintf(stderr, "Error: Tahun harus antara 1900-2100\n");
        return -1;
    }

    // Validasi bulan
    if (month < 1 || month > 12) {
        return -1;
    }

    // Validasi hari
    if (day < 1) return -1;
    
    int max_day = 31;
    if (month == 2) {
        max_day = cek_kabisat(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        max_day = 30;
    }
    
    if (day > max_day) {
        return -1;
    }

    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    tm.tm_isdst = -1;

    time_t timestamp = mktime(&tm);
    if (timestamp == -1) {
        return -1;
    }

    return timestamp;
}