#include <iostream>
#include <string>
#include <conio.h> 
#include <ctime>
using namespace std;

const int max_data = 100;

string ulang;

struct Warga {
    string pemilik_rumah;
    string nomor_rumah;
    string jumlah_anggota_keluarga;
    string kode_pos;
    string nomor_rt;
    struct Tanggal {
        int tahun;
        int bulan;
        int tanggal;
        int jam;
        int menit;
    } tanggal;
};

Warga data[max_data];

int datasekarang = 0;

int string_ke_int(){
   do{
    string noindeks;
    int noindeksconvert;

    cout << "Masukkan Nomor Data: ";
    getline(cin, noindeks);



    try {       
          noindeksconvert = stoi(noindeks);
            return noindeksconvert;
            break;

        } catch(const invalid_argument) {
            cout << "Mohon Masukkan Angka !!!" << endl;
        } catch(const out_of_range) {
            cout << "Data Tidak Di Temukan." << endl;
        }

   }while (true);

}


string pilihann() {
    string masukkan;
    cout << "Masukkan Pilihan Anda: ";
    getline(cin, masukkan);
    return masukkan;
}

void tekan_apapun_untuk_lanjut() {
    cout << "Tekan Apapun Untuk Lanjut.....";
    getch();
}

void lihat_data_warga() {
    if (datasekarang > 0) {
        for (int i = 0; i < datasekarang; i++) {
            cout << i + 1 << ". Data Warga:" << endl;
            cout << "Pemilik Rumah: " << data[i].pemilik_rumah << endl;
            cout << "No Rumah: " << data[i].nomor_rumah << endl;
            cout << "Anggota Keluarga: " << data[i].jumlah_anggota_keluarga << endl;
            cout << "No Kode Pos: " << data[i].kode_pos << endl;
            cout << "No RT: " << data[i].nomor_rt << endl;
            cout << "\nData Di Input Pada: " << endl;
            cout << "Tanggal: " << data[i].tanggal.tanggal << "/" << data[i].tanggal.bulan << "/" << data[i].tanggal.tahun << endl;
            cout << "Waktu: " << data[i].tanggal.jam << ":" << data[i].tanggal.menit << endl;
            cout << endl;
        }
    } else {
        cout << "Data Masih Kosong Pak RT !!!" << endl;
    }
}


void ubah_data_warga() {
    int ubah;
    if (datasekarang > 0) {
        lihat_data_warga();
        ubah = string_ke_int();
        if (ubah >= 1 && ubah <= datasekarang) {
            cout << "===================================" << endl;
            cout << "Pilih data yang ingin diubah:" << endl;
            cout << "1. Nama Pemilik Rumah" << endl;
            cout << "2. Jumlah Anggota Keluarga" << endl;
            cout << "3. Kode Pos" << endl;
            cout << "4. Nomor RT" << endl;
            cout << "5. Kembali" << endl;
            cout << "===================================" << endl;
            cout << "Pilihan Anda: ";
            string pilihan;
            getline(cin, pilihan);

            if (pilihan == "1") {
                cout << "Masukkan Nama Pemilik Rumah Baru: ";
                getline(cin, data[ubah - 1].pemilik_rumah);
            } else if (pilihan == "2") {
                cout << "Masukkan Jumlah Anggota Keluarga Baru: ";
                getline(cin, data[ubah - 1].jumlah_anggota_keluarga);
            } else if (pilihan == "3") {
                cout << "Masukkan Kode Pos Baru: ";
                getline(cin, data[ubah - 1].kode_pos);
            } else if (pilihan == "4") {
                cout << "Masukkan Nomor RT Baru: ";
                getline(cin, data[ubah - 1].nomor_rt);
            }else if (pilihan == "5"){

            } else {
                cout << "Pilihan tidak valid." << endl;
                
            }
            
            cout << "Apakah Mau Mengubah Data Lagi Tekan y untuk mengubah lagi atau tekan apapun untuk kembali:  ";
            ulang = getch();
    
            if (ulang == "y"){
                system("cls");
                ubah_data_warga();
            }else{
                cout << " " << endl;
                
            }
            
        } else {
            cout << "Nomor tidak valid." << endl;
        }
    } else {
        cout << "Data tidak ditemukan." << endl;
    }

}
void hapus_data_warga() {
    if (datasekarang > 0) {
        lihat_data_warga();
        int hapus;
        hapus = string_ke_int();
        if (hapus <= datasekarang && hapus >= 1) {
            for (int i = hapus - 1; i < datasekarang - 1; i++) {
                data[i] = data[i + 1];
            }
            datasekarang--;
            cout << "Data berhasil dihapus." << endl;
            cout << "Apakah Mau Menghapus Lagi Tekan y untuk menghapus lagi atau tekan apapun untuk kembali:  ";
            ulang = getch();
        
            if (ulang == "y"){
                system("cls");
                hapus_data_warga();
            }else{
                cout << " " << endl;
            }
        } else {
            cout << "Nomor tidak valid." << endl;
        }
    } else {
        cout << "Data tidak ditemukan." << endl;
    }
}
void tambah_data_warga() {
    lihat_data_warga();
    if (datasekarang < max_data) {
        cout << "Masukkan Data Pak RT" << endl;
        cout << "Masukkan Nama Pemilik Rumah: ";
        getline(cin, data[datasekarang].pemilik_rumah);
        cout << "Masukkan Nomor Rumah: ";
        getline(cin, data[datasekarang].nomor_rumah);
        cout << "Masukkan Jumlah Anggota Keluarga: ";
        getline(cin, data[datasekarang].jumlah_anggota_keluarga);
        cout << "Masukkan Kode Pos: ";
        getline(cin, data[datasekarang].kode_pos);
        cout << "Masukkan Nomor RT: ";
        getline(cin, data[datasekarang].nomor_rt);

        time_t now = time(0);
        tm *ltm = localtime(&now);

        data[datasekarang].tanggal.tahun = 1900 + ltm->tm_year;
        data[datasekarang].tanggal.bulan = 1 + ltm->tm_mon;
        data[datasekarang].tanggal.tanggal = ltm->tm_mday;
        data[datasekarang].tanggal.jam = ltm->tm_hour;
        data[datasekarang].tanggal.menit = ltm->tm_min;

        datasekarang++;

        cout << "Apakah Mau Menambah Data Lagi Tekan y untuk menambahkan lagi atau tekan apapun untuk kembali:  ";
        char ulang = getch();

        if (ulang == 'y') {
            system("cls");
            tambah_data_warga();
        }
    } else {
        cout << "Data Penuh Pak RT !!!" << endl;
    }
}

void menu_pak_rt() {
    do {
        cout << "===================================" << endl;
        cout << "Menu Pak RT" << endl;
        cout << "1. Tambah Data Warga" << endl;
        cout << "2. Lihat Data Warga" << endl;
        cout << "3. Ubah Data Warga" << endl;
        cout << "4. Hapus Data Warga" << endl;
        cout << "5. Kembali " << endl;
        cout << "6. EXIT " << endl;
        cout << "===================================" << endl;
        string pilih = pilihann();
        system("cls");

        if (pilih == "1") {
            tambah_data_warga();
            system("cls");
        } else if (pilih == "2") {
            lihat_data_warga();
            tekan_apapun_untuk_lanjut();
            system("cls");

        } else if (pilih == "3") {
            ubah_data_warga();
            tekan_apapun_untuk_lanjut();
            system("cls");

        } else if (pilih == "4") {
            hapus_data_warga();
            tekan_apapun_untuk_lanjut();
            system("cls");
        } else if (pilih == "5") {
            break;
        } else if (pilih == "6") {
            exit(0);
        } else {
            cout << "input tidak valid" << endl;
        }
    } while (true);
}

bool login_pakrt() {
    string user, pw;
    int percobaan = 0;
    do {
        cout << "Masukkan Username: ";
        getline(cin, user);
        cout << "Masukkan Password: ";
        getline(cin, pw);

        if (user == "raihan" && pw == "096") {
            break;
        } else {
            percobaan++;
            if (percobaan == 3) {
                cout << "Silahkan Coba Lagi Nanti !!!!" << endl;
                return false;
            } else {
                cout << "Silahkan Coba Lagi" << endl;
            }
        }

    } while (true);
    return true;
}

int main() {
    string pilihan;
    do {
        cout << "===================================" << endl;
        cout << "Halo Selamat Datang" << endl;
        cout << "1. Login" << endl;
        cout << "2. EXIT" << endl;
        cout << "===================================" << endl;
        pilihan = pilihann();
        system("cls");

        if (pilihan == "1") {
            if (login_pakrt()) {
                menu_pak_rt();
            } else {
                break;
            }

        } else if (pilihan == "2") {
            cout << "Terima kasih, sampai jumpa!" << endl;
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan masukkan pilihan yang benar." << endl;
        }
    } while (true);

    return 0;
}