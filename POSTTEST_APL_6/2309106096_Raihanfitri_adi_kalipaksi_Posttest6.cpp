#include <iostream>
#include <string>
#include <conio.h> 
#include <ctime>
using namespace std;

const int max_data = 100;

string ulang;


struct Warga {
    string pemilik_rumah;
    int nomor_rumah;
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
    if(datasekarang > 0){

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
                cout << "Data Tidak Ditemukan." << endl;
                
            }

        }while (true);
    }else{
        
    }
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

void ubah_data_warga(int *ubah) {
    if (datasekarang > 0) {
        lihat_data_warga();
        if (*ubah >= 1 && *ubah <= datasekarang) {
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
                getline(cin, data[*ubah - 1].pemilik_rumah);
            } else if (pilihan == "2") {
                cout << "Masukkan Jumlah Anggota Keluarga Baru: ";
                getline(cin, data[*ubah - 1].jumlah_anggota_keluarga);
            } else if (pilihan == "3") {
                cout << "Masukkan Kode Pos Baru: ";
                getline(cin, data[*ubah - 1].kode_pos);
            } else if (pilihan == "4") {
                cout << "Masukkan Nomor RT Baru: ";
                getline(cin, data[*ubah - 1].nomor_rt);
            } else if (pilihan == "5") {

            } else {
                cout << "Pilihan tidak valid." << endl;
            }
            
            cout << "Apakah Mau Mengubah Data Lagi Tekan y untuk mengubah lagi atau tekan apapun untuk kembali:  ";
            ulang = getch();
    
            if (ulang == "y"){
                system("cls");
                ubah_data_warga(ubah);
            } else {
                cout << " " << endl;
            }
            
        } else {
            cout << "Nomor tidak valid." << endl;
        }
    }else {
        cout << "Data tidak ditemukan." << endl;
    }
}

void hapus_data_warga(int *datasekarang) {
    if (*datasekarang > 0) {
        lihat_data_warga();
        int hapus;
        hapus = string_ke_int();
        if (hapus <= *datasekarang && hapus >= 1) {
            for (int i = hapus - 1; i < *datasekarang - 1; i++) {
                data[i] = data[i + 1];
            }
            (*datasekarang)--;
            cout << "Data berhasil dihapus." << endl;
            cout << "Apakah Mau Menghapus Lagi Tekan y untuk menghapus lagi atau tekan apapun untuk kembali:  ";
            ulang = getch();
        
            if (ulang == "y"){
                system("cls");
                hapus_data_warga(datasekarang);
            } else {
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
    system("cls");
    lihat_data_warga();
    if (datasekarang < max_data) {
        cout << "Masukkan Data Pak RT" << endl;

        cout << "Masukkan Nama Pemilik Rumah: ";
        getline(cin, data[datasekarang].pemilik_rumah);
        
        
        cout << "Masukkan Nomor Rumah: ";
        string temp;
        getline(cin, temp);
        try {
            data[datasekarang].nomor_rumah = stoi(temp);
        } catch (const invalid_argument &) {
            cout << "Mohon masukkan angka yang valid untuk nomor rumah." << endl;
            tekan_apapun_untuk_lanjut();
            return;
        } catch (const out_of_range &) {
            cout << "Angka di luar jangkauan yang dapat ditangani." << endl;
            tekan_apapun_untuk_lanjut();
            return;
        }

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

        cout << "Apakah Mau Menambah Data Lagi? Tekan 'y' untuk menambahkan lagi atau tekan tombol lain untuk kembali: ";
        char ulang = getch();
        if (ulang == 'y') {
            tambah_data_warga();
        }
    } else {
        cout << "Data Penuh Pak RT!" << endl;
    }
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


void bubble_sort_descending() {
    for (int i = 0; i < datasekarang - 1; i++) {
        for (int j = 0; j < datasekarang - i - 1; j++) {
            if (data[j].pemilik_rumah < data[j + 1].pemilik_rumah) {
                Warga temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    lihat_data_warga();
}
void selection_sort_ascending() {
    if (datasekarang > 0) {
        for (int i = 0; i < datasekarang - 1; i++) {
            int min_index = i;
            for (int j = i + 1; j < datasekarang; j++) {
                
                if (data[j].nomor_rumah < data[min_index].nomor_rumah){
                    min_index = j;
                }
            }
        
            if (min_index != i) {
                Warga temp = data[i];
                data[i] = data[min_index];
                data[min_index] = temp;
            }
        }
        lihat_data_warga();
    }
}



void insertion_sort_ascending() {
    if (datasekarang > 0) {
        for (int i = 1; i < datasekarang; i++) {
            Warga key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j].pemilik_rumah > key.pemilik_rumah) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
        lihat_data_warga();
    }
}

void binary_search(int pilih) {
system("cls");
lihat_data_warga();
string cari;
cout << "Masukkan nama yang ingin dicari: ";
getline(cin,cari);

int low = 0;
int high = datasekarang - 1;
int mid;
bool found = false;

if (pilih == 1) {
    // Binary search in descending order
    while (low <= high) {
        mid = low + (high - low) / 2;

        if (data[mid].pemilik_rumah == cari) {
            found = true;
            cout << "Data ditemukan di data ke-" << mid+1 << endl;
            cout << "Pemilik Rumah: " << data[mid].pemilik_rumah << endl;
            cout << "Nomor Rumah: " << data[mid].nomor_rumah << endl;
            cout << "Anggota Keluarga: " << data[mid].jumlah_anggota_keluarga << endl;
            cout << "Kode Pos: " << data[mid].kode_pos << endl;
            cout << "Nomor RT: " << data[mid].nomor_rt << endl;
            cout << endl;
            break;
        }

        if (data[mid].pemilik_rumah > cari) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
} else if (pilih == 2) {
    while (low <= high) {
        mid = low + (high - low) / 2;

        if (data[mid].pemilik_rumah == cari) {
            found = true;
            cout << "Data ditemukan di data ke-" << mid+1 << endl;
            cout << "Pemilik Rumah: " << data[mid].pemilik_rumah << endl;
            cout << "Nomor Rumah: " << data[mid].nomor_rumah << endl;
            cout << "Anggota Keluarga: " << data[mid].jumlah_anggota_keluarga << endl;
            cout << "Kode Pos: " << data[mid].kode_pos << endl;
            cout << "Nomor RT: " << data[mid].nomor_rt << endl;
            cout << endl;
            break;
        }

        if (data[mid].pemilik_rumah > cari) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
}

if (!found) {
    cout << "Data tidak ditemukan." << endl;
}
}




void interpolation_search_ascending() {
    if (datasekarang > 0) {

        system("cls");
        
        string temp;
        int cari;
        cout << "Masukkan Nomor Rumah yang ingin dicari: ";
        
        while (true) {
            getline(cin, temp);
            try {
                cari = stoi(temp);
                break; 
            } catch (const invalid_argument&) {
                cout << "Mohon masukkan angka yang valid!" << endl;
                cout << "Masukkan Nomor Rumah yang ingin dicari: ";
            } catch (const out_of_range&) {
                cout << "Angka terlalu besar atau kecil. Silakan coba lagi." << endl;
                cout << "Masukkan Nomor Rumah yang ingin dicari: ";
            }
        }
        
        int low = 0;
        int high = datasekarang - 1;
        bool found = false;

        while (low <= high && cari >= data[low].nomor_rumah && cari <= data[high].nomor_rumah) {
            if (low == high) {
                if (data[low].nomor_rumah == cari) {
                    found = true;
                    cout << "Data ditemukan di data Ke: " << low + 1 << endl;
                    cout << "Pemilik Rumah: " << data[low].pemilik_rumah << endl;
                    cout << "Nomor Rumah: " << data[low].nomor_rumah << endl;
                    cout << "Anggota Keluarga: " << data[low].jumlah_anggota_keluarga << endl;
                    cout << "Kode Pos: " << data[low].kode_pos << endl;
                    cout << "Nomor RT: " << data[low].nomor_rt << endl;
                    cout << endl;
                    cout << "Tanggal Input: " << data[low].tanggal.tanggal << "/" << data[low].tanggal.bulan << "/" << data[low].tanggal.tahun << endl;
                    cout << "Waktu Input: " << data[low].tanggal.jam << ":" << data[low].tanggal.menit << endl;
                    break;
                } else {
                    break;
                }
            }

            int pos = low + ((cari - data[low].nomor_rumah) * (high - low)) / (data[high].nomor_rumah - data[low].nomor_rumah);
            
            if (pos < low || pos > high) {
                break;
            }
            
            if (data[pos].nomor_rumah == cari) {
                found = true;
                // Output data information
                cout << "Data ditemukan di data Ke: " << pos + 1 << endl;
                cout << "Pemilik Rumah: " << data[pos].pemilik_rumah << endl;
                cout << "Nomor Rumah: " << data[pos].nomor_rumah << endl;
                cout << "Anggota Keluarga: " << data[pos].jumlah_anggota_keluarga << endl;
                cout << "Kode Pos: " << data[pos].kode_pos << endl;
                cout << "Nomor RT: " << data[pos].nomor_rt << endl;
                cout << endl;
                cout << "Tanggal Input: " << data[pos].tanggal.tanggal << "/" << data[pos].tanggal.bulan << "/" << data[pos].tanggal.tahun << endl;
                cout << "Waktu Input: " << data[pos].tanggal.jam << ":" << data[pos].tanggal.menit << endl;
                break;
            }
            
            if (data[pos].nomor_rumah < cari) {
                low = pos + 1;
            } else {
                high = pos - 1;
            }
        }
        
        if (!found) {
            cout << "Data tidak ditemukan." << endl;
        }
    } else {
        cout << "Data tidak ditemukan." << endl;
    }
}









void pilihan_sorting_dan_searching(){   
    string pilihan,pilih;
    if (datasekarang > 0) {
        cout << "Apakah Anda Ingin Mengurutkan Atau Mencari Data?? y/t: ";
        getline(cin,pilihan);

        if(pilihan == "y"){
            system("cls");
            cout << "===============================================" << endl;
            cout << "Menu SORTING SEARCHING" << endl;
            cout << "1. Sorting & Searching Nama Pemilik Rumah" << endl;
            cout << "2. Sorting & Searching Nomor Rumah" << endl;
            cout << "3. EXIT " << endl;
            cout << "===============================================" << endl;
            cout << "Masukkan Pilihan Anda: ";
            getline(cin,pilih);
            if (pilih == "1"){
                cout << "Tekan 1 Untuk Urutkan Secara Descending / Tekan 2 Untuk Urutkan Secara Ascending: ";
                getline(cin,pilihan);
                if (pilihan == "1"){
                    system("cls");
                    bubble_sort_descending();
                    cout << "Apakah Ingin Lanjut Mencari Data? y/t: ";
                    getline(cin,pilih);
                    if (pilih == "y"){
                        system("cls");
                        binary_search(1);
                    }
                }else if(pilihan == "2"){
                    system("cls");
                    insertion_sort_ascending();
                    cout << "Apakah Ingin Lanjut Mencari Data? y/t: ";
                    getline(cin,pilih);

                    if (pilih == "y"){
                        system("cls");
                        binary_search(2);
                        
                    }
                }
            }else if(pilih == "2"){
                system("cls");
                selection_sort_ascending();
                cout << "Apakah Ingin Lanjut Mencari Data? y/t: ";
                getline(cin,pilih);
                if (pilih == "y"){
                        system("cls");
                        interpolation_search_ascending();
                    }
            }else if (pilih == "3")
            {
                
            
            }else {
            cout << "pilihan tidak valid" << endl;
            }

        }else {
            cout << "pilihan tidak valid" << endl;
            
        }

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
            pilihan_sorting_dan_searching();
            tekan_apapun_untuk_lanjut();
            system("cls");

        } else if (pilih == "3") {
            int ubah;
            lihat_data_warga();
            ubah = string_ke_int();
            ubah_data_warga(&ubah);
            tekan_apapun_untuk_lanjut();
            system("cls");

        } else if (pilih == "4") {
            hapus_data_warga(&datasekarang);
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