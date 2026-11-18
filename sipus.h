#ifndef SIPUS_H
#define SIPUS_H

#include <string>
using namespace std;

const int JML_KATEGORI = 5;
const int JML_BULAN = 12;
const int MAKS_PINJAM = 3;
const int DENDA_HARIAN = 1000;
const int LAMA_PINJAM = 7;

inline const string NAMA_KATEGORI[JML_KATEGORI] = {
    "Pemrograman", "Basis Data", "Jaringan", "Matematika", "Umum"
};

struct Tanggal {
    int hari, bulan, tahun;
};

struct Buku {
    string kode;
    string judul;
    string penulis;
    int kategori;
    int tahun;
    int stok;
    int totalDipinjam;
    int sedangDipinjam = 0;
};

struct Anggota {
    string id;
    string nama;
    string prodi;
    int sedangPinjam;
};

struct Transaksi {
    int nomor;
    string idAnggota;
    string kodeBuku;
    Tanggal tglPinjam;
    Tanggal tglKembali;
    bool selesai;
    int denda;
};

struct DaftarBuku {
    Buku* data;
    int n, kapasitas;
};

struct DaftarAnggota {
    Anggota* data;
    int n, kapasitas;
};

struct DaftarTransaksi {
    Transaksi* data;
    int n, kapasitas;
};

bool formatKodeBukuValid(const string& kode);
void inisialisasi(DaftarBuku& d, int kapasitasAwal);
void bebaskan(DaftarBuku& d);
Buku* cariKode(DaftarBuku& d, const string& kode);
const Buku* cariKodeConst(const DaftarBuku& d, const string& kode);
bool tambahBuku(DaftarBuku& d, const Buku& b);
bool ubahBuku(DaftarBuku& d, const string& kode, const string& judulBaru,
              const string& penulisBaru, int kategoriBaru, int tahunBaru, int stokBaru);
bool hapusBuku(DaftarBuku& d, const string& kode);
void tampilBuku(const DaftarBuku& d);

bool formatIdAnggotaValid(const string& id);
void inisialisasi(DaftarAnggota& d, int kapasitasAwal);
void bebaskan(DaftarAnggota& d);
Anggota* cariAnggota(DaftarAnggota& d, const string& id);
const Anggota* cariAnggotaConst(const DaftarAnggota& d, const string& id);
bool tambahAnggota(DaftarAnggota& d, const Anggota& a);
bool ubahAnggota(DaftarAnggota& d, const string& id, const string& namaBaru, const string& prodiBaru);
void tampilAnggota(const DaftarAnggota& d);

#endif