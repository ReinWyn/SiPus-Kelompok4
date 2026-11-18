#include "sipus.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

bool formatKodeBukuValid(const string& kode) {
    if (kode.size() != 6) return false;
    if (kode.substr(0, 3) != "BK-") return false;
    for (int i = 3; i < 6; i++) {
        if (!isdigit(static_cast<unsigned char>(kode[i]))) return false;
    }
    return true;
}

void inisialisasi(DaftarBuku& d, int kapasitasAwal) {
    if (kapasitasAwal <= 0) kapasitasAwal = 4;
    d.data = new Buku[kapasitasAwal];
    d.n = 0;
    d.kapasitas = kapasitasAwal;
}

static void perbesarBuku(DaftarBuku& d) {
    int kapBaru = (d.kapasitas == 0) ? 4 : d.kapasitas * 2;
    Buku* baru = new Buku[kapBaru];
    for (int i = 0; i < d.n; i++) {
        baru[i] = d.data[i];
    }
    delete[] d.data;
    d.data = baru;
    d.kapasitas = kapBaru;
}

void bebaskan(DaftarBuku& d) {
    delete[] d.data;
    d.data = nullptr;
    d.n = 0;
    d.kapasitas = 0;
}

bool tambahBuku(DaftarBuku& d, const Buku& b) {
    if (!formatKodeBukuValid(b.kode)) return false;
    if (b.judul.empty() || b.penulis.empty()) return false;
    if (b.kategori < 0 || b.kategori >= JML_KATEGORI) return false;
    if (b.tahun <= 0 || b.stok < 0 || b.totalDipinjam < 0) return false;
    if (cariKodeConst(d, b.kode) != nullptr) return false;

    if (d.n == d.kapasitas) {
        perbesarBuku(d);
    }
    d.data[d.n] = b;
    d.n++;
    return true;
}

bool ubahBuku(DaftarBuku& d, const string& kode, const string& judulBaru,
              const string& penulisBaru, int kategoriBaru, int tahunBaru, int stokBaru) {
    Buku* target = cariKode(d, kode);
    if (target == nullptr) return false;
    if (judulBaru.empty() || penulisBaru.empty()) return false;
    if (kategoriBaru < 0 || kategoriBaru >= JML_KATEGORI) return false;
    if (tahunBaru <= 0 || stokBaru < 0) return false;

    target->judul = judulBaru;
    target->penulis = penulisBaru;
    target->kategori = kategoriBaru;
    target->tahun = tahunBaru;
    target->stok = stokBaru;
    return true;
}

bool hapusBuku(DaftarBuku& d, const string& kode) {
    int idx = -1;
    for (int i = 0; i < d.n; i++) {
        if (d.data[i].kode == kode) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return false;
    if (d.data[idx].sedangDipinjam > 0) return false;

    for (int i = idx; i < d.n - 1; i++) {
        d.data[i] = d.data[i + 1];
    }
    d.n--;
    return true;
}

void tampilBuku(const DaftarBuku& d) {
    if (d.n == 0) {
        cout << "Belum ada data buku.\n";
        return;
    }
    cout << left
         << setw(8) << "Kode"
         << setw(26) << "Judul"
         << setw(18) << "Penulis"
         << setw(14) << "Kategori"
         << setw(7) << "Tahun"
         << setw(6) << "Stok"
         << setw(8) << "Dipinjam" << "\n";
    cout << string(87, '-') << "\n";
    for (int i = 0; i < d.n; i++) {
        cout << left
             << setw(8) << d.data[i].kode
             << setw(26) << d.data[i].judul.substr(0, 24)
             << setw(18) << d.data[i].penulis.substr(0, 16)
             << setw(14) << NAMA_KATEGORI[d.data[i].kategori]
             << setw(7) << d.data[i].tahun
             << setw(6) << d.data[i].stok
             << setw(8) << d.data[i].totalDipinjam << "\n";
    }
}