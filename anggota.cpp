#include "sipus.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

bool formatIdAnggotaValid(const string& id) {
    if (id.size() != 6) return false;
    if (id.substr(0, 3) != "AG-") return false;
    for (int i = 3; i < 6; i++) {
        if (!isdigit(static_cast<unsigned char>(id[i]))) return false;
    }
    return true;
}

void inisialisasi(DaftarAnggota& d, int kapasitasAwal) {
    if (kapasitasAwal <= 0) kapasitasAwal = 4;
    d.data = new Anggota[kapasitasAwal];
    d.n = 0;
    d.kapasitas = kapasitasAwal;
}

static void perbesarAnggota(DaftarAnggota& d) {
    int kapBaru = (d.kapasitas == 0) ? 4 : d.kapasitas * 2;
    Anggota* baru = new Anggota[kapBaru];
    for (int i = 0; i < d.n; i++) {
        baru[i] = d.data[i];
    }
    delete[] d.data;
    d.data = baru;
    d.kapasitas = kapBaru;
}

void bebaskan(DaftarAnggota& d) {
    delete[] d.data;
    d.data = nullptr;
    d.n = 0;
    d.kapasitas = 0;
}

Anggota* cariAnggota(DaftarAnggota& d, const string& id) {
    for (int i = 0; i < d.n; i++) {
        if (d.data[i].id == id) {
            return &d.data[i];
        }
    }
    return nullptr;
}

const Anggota* cariAnggotaConst(const DaftarAnggota& d, const string& id) {
    for (int i = 0; i < d.n; i++) {
        if (d.data[i].id == id) {
            return &d.data[i];
        }
    }
    return nullptr;
}

bool tambahAnggota(DaftarAnggota& d, const Anggota& a) {
    if (!formatIdAnggotaValid(a.id)) return false;
    if (a.nama.empty() || a.prodi.empty()) return false;
    if (a.sedangPinjam < 0 || a.sedangPinjam > MAKS_PINJAM) return false;
    if (cariAnggotaConst(d, a.id) != nullptr) return false;

    if (d.n == d.kapasitas) {
        perbesarAnggota(d);
    }
    d.data[d.n] = a;
    d.n++;
    return true;
}

bool ubahAnggota(DaftarAnggota& d, const string& id, const string& namaBaru, const string& prodiBaru) {
    Anggota* target = cariAnggota(d, id);
    if (target == nullptr) return false;
    if (namaBaru.empty() || prodiBaru.empty()) return false;

    target->nama = namaBaru;
    target->prodi = prodiBaru;
    return true;
}

void tampilAnggota(const DaftarAnggota& d) {
    if (d.n == 0) {
        cout << "Belum ada data anggota.\n";
        return;
    }
    cout << left
         << setw(10) << "ID"
         << setw(26) << "Nama"
         << setw(24) << "Prodi"
         << setw(10) << "Pinjaman" << "\n";
    cout << string(70, '-') << "\n";
    for (int i = 0; i < d.n; i++) {
        cout << left
             << setw(10) << d.data[i].id
             << setw(26) << d.data[i].nama.substr(0, 24)
             << setw(24) << d.data[i].prodi.substr(0, 22)
             << setw(10) << d.data[i].sedangPinjam << "\n";
    }
}
