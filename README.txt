SiPus: Sistem Peminjaman Perpustakaan Mini
Kelompok : 14
Anggota 1: Made Reindra Aryanatha / 260530911019
Anggota 2: I Komang Trian Paradana / 260530911142

Perintah Kompilasi Program Utama (C++17, tanpa warning -Wall):
g++ -std=c++17 -Wall main.cpp buku.cpp anggota.cpp transaksi.cpp -o sipus

Perintah Menjalankan Program Utama:
./sipus          (Linux/WSL)
sipus.exe        (Windows/MinGW)

Perintah Kompilasi & Menjalankan Pengujian Otomatis:
g++ -std=c++17 -Wall uji.cpp buku.cpp anggota.cpp transaksi.cpp -o uji
./uji            (Linux/WSL)
uji.exe          (Windows/MinGW)

Perintah Pengujian Memori (Linux/WSL):
1) AddressSanitizer:
g++ -std=c++17 -Wall -g -fsanitize=address uji.cpp buku.cpp anggota.cpp transaksi.cpp -o uji_asan
./uji_asan
g++ -std=c++17 -Wall -g -fsanitize=address main.cpp buku.cpp anggota.cpp transaksi.cpp -o sipus_asan
./sipus_asan

2) Valgrind:
valgrind --leak-check=full ./uji
valgrind --leak-check=full ./sipus
