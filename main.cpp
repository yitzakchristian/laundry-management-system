#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void header() {
    cout << "\n\n\n";
    cout << "\t\t===============================================================\n"
         << "\t\t\t    Aplikasi Manajemen Operasional Laundry\n"
         << "\t\t===============================================================\n\n";
}

struct Pesanan {
    string nomorOrder;
    string namaPelanggan;
    string jenisPakaian;
    int jumlah;
    string paketLayanan;
    string status;
    string tanggalDiterima;
    string estimasiSelesai;
    string tanggalSelesai;
};

struct Keluhan {
    string nomorOrder;
    string deskripsi;
    string statusPenanganan;
};

struct BahanPenggunaan {
    string jenisBahan;
    int jumlah;
};

const int MAX_PESANAN = 100;
const int MAX_KELUHAN = 100;
const int MAX_BAHAN = 100;

Pesanan daftarPesanan[MAX_PESANAN];
Keluhan daftarKeluhan[MAX_KELUHAN];
BahanPenggunaan penggunaanBahan[MAX_BAHAN];

int jumlahPesanan = 0;
int jumlahKeluhan = 0;
int jumlahBahan = 0;

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[11];
    strftime(date, 11, "%Y-%m-%d", ltm);
    return string(date);
}

string generateNomorOrder() {
    static int counter = 1;
    return "ORD" + to_string(counter++);
}

void catatPesanan() {
    if (jumlahPesanan >= MAX_PESANAN) {
        cout << "Kapasitas daftar pesanan penuh.\n";
        return;
    }

    Pesanan pesananBaru;
    pesananBaru.nomorOrder = generateNomorOrder();

    cin.ignore();
    cout << "Masukkan nama pelanggan: ";
    getline(cin, pesananBaru.namaPelanggan);

    cout << "Masukkan jenis pakaian: ";
    getline(cin, pesananBaru.jenisPakaian);

    cout << "Masukkan jumlah pakaian: ";
    cin >> pesananBaru.jumlah;
    cin.ignore();

    if (pesananBaru.jumlah <= 0) {
        cout << "Jumlah pakaian harus lebih dari 0.\n";
        return;
    }

    cout << "Masukkan paket layanan: ";
    getline(cin, pesananBaru.paketLayanan);

    pesananBaru.status = "Diterima";
    pesananBaru.tanggalDiterima = getCurrentDate();

    daftarPesanan[jumlahPesanan++] = pesananBaru;
    cout << "Pesanan berhasil ditambahkan! Nomor Order: " << pesananBaru.nomorOrder << "\n";
}

void tampilkanDaftarPesanan() {
    cout << "Daftar Pesanan Aktif:\n";
    cout << "---------------------\n";
    for (int i = 0; i < jumlahPesanan; i++) {
        Pesanan pesanan = daftarPesanan[i];
        cout << "Nomor Order: " << pesanan.nomorOrder << endl;
        cout << "Nama Pelanggan: " << pesanan.namaPelanggan << endl;
        cout << "Jenis Pakaian: " << pesanan.jenisPakaian << endl;
        cout << "Jumlah: " << pesanan.jumlah << endl;
        cout << "Status: " << pesanan.status << endl;
        cout << "Tanggal Diterima: " << pesanan.tanggalDiterima << endl;
        cout << "--------------------------\n";
    }
}

void updateStatusPesanan() {
    string nomorOrder;
    cout << "Masukkan nomor pesanan: ";
    cin >> nomorOrder;

    for (int i = 0; i < jumlahPesanan; i++) {
        if (daftarPesanan[i].nomorOrder == nomorOrder) {
            cout << "Status saat ini: " << daftarPesanan[i].status << endl;
            cout << "Pilih status baru (Diterima, Dicuci, MulaiCuci, SelesaiCuci, Selesai): ";
            string statusBaru;
            cin >> statusBaru;
            daftarPesanan[i].status = statusBaru;
            if (statusBaru == "Selesai") {
                daftarPesanan[i].tanggalSelesai = getCurrentDate();
            }
            cout << "Status pesanan berhasil diperbarui!\n";
            return;
        }
    }

    cout << "Pesanan tidak ditemukan.\n";
}

void catatPenggunaanBahan() {
    if (jumlahBahan >= MAX_BAHAN) {
        cout << "Kapasitas daftar bahan penuh.\n";
        return;
    }

    BahanPenggunaan bahanBaru;
    cin.ignore();
    cout << "Masukkan jenis bahan (detergen/pelembut): ";
    getline(cin, bahanBaru.jenisBahan);
    cout << "Masukkan jumlah yang digunakan: ";
    cin >> bahanBaru.jumlah;

    if (bahanBaru.jumlah <= 0) {
        cout << "Jumlah harus lebih dari 0.\n";
        return;
    }

    penggunaanBahan[jumlahBahan++] = bahanBaru;
    cout << "Penggunaan bahan berhasil dicatat.\n";
}

void catatKeluhan() {
    if (jumlahKeluhan >= MAX_KELUHAN) {
        cout << "Kapasitas daftar keluhan penuh.\n";
        return;
    }

    Keluhan keluhanBaru;
    cin.ignore();
    cout << "Masukkan nomor order: ";
    getline(cin, keluhanBaru.nomorOrder);
    cout << "Masukkan deskripsi keluhan: ";
    getline(cin, keluhanBaru.deskripsi);
    keluhanBaru.statusPenanganan = "Belum Ditangani";

    daftarKeluhan[jumlahKeluhan++] = keluhanBaru;
    cout << "Keluhan berhasil dicatat.\n";
}

void tampilkanLaporanPesananSelesai() {
    cout << "Laporan Pesanan Selesai Hari Ini:\n";
    cout << "---------------------------------\n";
    string today = getCurrentDate();

    int pesananSelesaiHariIni = 0;
    for (int i = 0; i < jumlahPesanan; i++) {
        if (daftarPesanan[i].status == "Selesai" && daftarPesanan[i].tanggalSelesai == today) {
            cout << "Nomor Order: " << daftarPesanan[i].nomorOrder << endl;
            cout << "Nama Pelanggan: " << daftarPesanan[i].namaPelanggan << endl;
            cout << "Tanggal Selesai: " << daftarPesanan[i].tanggalSelesai << endl;
            cout << "--------------------------\n";
            pesananSelesaiHariIni++;
        }
    }

    int totalBahanHariIni = 0;
    for (int i = 0; i < jumlahBahan; i++) {
        totalBahanHariIni += penggunaanBahan[i].jumlah;
    }

    int keluhanHariIni = jumlahKeluhan;

    cout << "Statistik Hari Ini:\n";
    cout << "- Pesanan selesai: " << pesananSelesaiHariIni << endl;
    cout << "- Total penggunaan bahan: " << totalBahanHariIni << endl;
    cout << "- Total keluhan: " << keluhanHariIni << endl;
    cout << "---------------------------------\n";
}

bool kembaliKeMenu() {
    int pilih;
    cout << "\t\t Ingin Melakukan Transaksi Kembali ? \n\n"
         << "\t\t       1. Ya       2. Tidak \n\n"
         << "\t\t==========================================\n\n"
         << "\t\t pilih : ";
    cin >> pilih;
    return pilih == 1;
}

int main() {
    int pilihan;

    do {
        system("cls");
        header();
        cout << "1. Catat Pesanan\n";
        cout << "2. Lihat Daftar Pesanan\n";
        cout << "3. Update Status Pesanan\n";
        cout << "4. Catat Penggunaan Bahan\n";
        cout << "5. Catat Keluhan Pelanggan\n";
        cout << "6. Tampilkan Laporan Pesanan Selesai Hari Ini\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                catatPesanan();
                break;
            case 2:
                tampilkanDaftarPesanan();
                break;
            case 3:
                updateStatusPesanan();
                break;
            case 4:
                catatPenggunaanBahan();
                break;
            case 5:
                catatKeluhan();
                break;
            case 6:
                tampilkanLaporanPesananSelesai();
                break;
            case 7:
                cout << "Terima kasih telah menggunakan aplikasi ini!\n";
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (kembaliKeMenu());

    cout << "Terima kasih telah menggunakan aplikasi ini!\n";
    return 0;
}
