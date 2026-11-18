#include <iostream>
#include "sipus.h"
using namespace std;

int lulus = 0, gagal = 0;

void cek(bool kondisi, const string& nama) {
    cout << (kondisi ? "[LULUS] " : "[GAGAL] ") << nama << endl;
    kondisi ? lulus++ : gagal++;
}

int main() {
    DaftarBuku d;
    DaftarAnggota a;

    inisialisasi(d, 2);
    inisialisasi(a, 2);

    tambahBuku(d, {"BK-002", "Struktur Data", "Wati", 0, 2024, 3, 0});
    tambahBuku(d, {"BK-001", "Algoritma", "Budi", 0, 2023, 1, 0});
    tambahBuku(d, {"BK-003", "Basis Data", "Sari", 1, 2022, 2, 0});
    cek(d.n == 3 && d.kapasitas >= 3, "F1: array dinamis buku membesar otomatis");

    Buku ganda = {"BK-001", "X", "Y", 0, 2020, 1, 0};
    cek(!tambahBuku(d, ganda), "F1: kode buku ganda ditolak");

    cek(ubahBuku(d, "BK-003", "Basis Data Lanjut", "Sari", 1, 2023, 2) &&
        hapusBuku(d, "BK-002") && cariKode(d, "BK-002") == nullptr,
        "F1: ubah dan hapus buku berhasil");
}