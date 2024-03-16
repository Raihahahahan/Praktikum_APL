#include <iostream>
#include <conio.h>
using namespace std;

const int max_data = 100;
string data[max_data][5], ulang;
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

string pilihann(){
    string masukkan;
    cout<< "Masukkan Pilihan Anda: ";
    getline(cin, masukkan );
    return masukkan;
}
void tekan_apapun_untuk_lanjut(){
    cout << "Tekan Apapun Untuk Lanjut.....";
    getch();
}

void lihat_data_warga(){
    if (datasekarang > 0){
        for (int i = 0; i < datasekarang; i++) {
            cout << i + 1 << ". Data Warga:" << endl;
            for (int j = 0; j < 5; j++) {
                if (j == 0){
                    cout << "Pemilik Rumah: " << data[i][j] << endl;
                }else if (j == 1){
                    cout << "No Rumah: " << data[i][j] << endl;
                }else if (j == 2){
                    cout << "Anggota Keluarga: " << data[i][j] << endl;
                }else if (j == 3){
                    cout << "No Kode Pos: " << data[i][j] << endl;
                }else if (j == 4){
                    cout << "No RT: " << data[i][j] << "\n" << endl;
                }
            }
        }
    }else{
        cout << "Data Masih Kosong Pak RT !!!" << endl;
    }
}   

void ubah_data_warga(){
    string pilihanubah;
    int ubahdata;
    do{
        if (datasekarang > 0){
            lihat_data_warga();
            ubahdata = string_ke_int();
            if (ubahdata >= 1 && ubahdata <= datasekarang){
                cout << "===================================" << endl;
                cout <<"1. Ubah Nama Pemilik Rumah" << endl;
                cout <<"2. Ubah Nomor Rumah" << endl;
                cout <<"3. Ubah Jumlah Anggota Keluarga" << endl;
                cout <<"4. Ubah Kode Pos" << endl;
                cout <<"5. Ubah Nomor RT" << endl;
                cout <<"6. Kembali" << endl;
                cout << "===================================" << endl;
                pilihanubah = pilihann();
                if (pilihanubah == "1"){
                    cout << "Masukkan Nama Pemilik Baru: ";
                    getline(cin,data[ubahdata-1][0]);
                }else if (pilihanubah == "2"){
                    cout << "Masukkan Nomor Rumah Baru: ";
                    getline(cin,data[ubahdata-1][1]);
                }else if (pilihanubah == "3"){
                    cout << "Masukkan Jumlah Anggota Keluarga Baru: ";
                    getline(cin,data[ubahdata-1][2]);
                }else if (pilihanubah == "4"){
                    cout << "Masukkan Kode Pos Baru: ";
                    getline(cin,data[ubahdata-1][3]);
                }else if (pilihanubah == "5"){
                    cout << "Masukkan Nomor RT Baru: ";
                    getline(cin,data[ubahdata-1][4]);
                }else if (pilihanubah == "6"){
                    break;
                }
                else{
                    cout << "Pilihan Tidak Valid " << endl;
                    continue;
                }
                cout << "Apakah Mau Mengubah Data Lagi Tekan y untuk mengubah lagi atau tekan apapun untuk kembali:  ";
                ulang = getch();
        
                if (ulang == "y"){
                    system("cls");
                    ubah_data_warga();
                }else{
                    break;
                }
            }else {
                cout << "Nomor Tidak Valid" << endl;
            }
        
        }else{
            cout << "Data Masih Kosong Pak RT !!!" << endl;
        }
    }while (true);
}


void hapus_data_warga(){
    int hapus;
    
    lihat_data_warga();
    if (datasekarang > 0){
        hapus = string_ke_int();
        if(hapus <= datasekarang && hapus >= 1) {
            for(int i = hapus - 1; i < datasekarang - 1; i++){
                for (int j = 0; j < 5; j++){
                    data[i][j] = data[i+1][j];
                }
            }
            datasekarang--;
            cout << "Apakah Mau Menghapus Lagi Tekan y untuk menghapus lagi atau tekan apapun untuk kembali:  ";
            ulang = getch();
        
            if (ulang == "y"){
                system("cls");
                hapus_data_warga();
            }
        } else {
            cout << "Nomor Tidak Valid" << endl;
        }
    }else {
        cout << "Data Tidak Di Temukan" << endl;
    }
    
}

void tambah_data_warga() {
    
    lihat_data_warga();
    if (datasekarang < max_data) {
        cout << "Masukkan Data Pak RT" << endl;
        cout << "Masukkan Nama Pemilik Rumah: ";
        getline(cin, data[datasekarang][0]);
        cout << "Masukkan Nomor Rumah: ";
        getline(cin, data[datasekarang][1]);
        cout << "Masukkan Jumlah Anggota Keluarga: ";   
        getline(cin, data[datasekarang][2]);
        cout << "Masukkan Kode Pos: ";
        getline(cin, data[datasekarang][3]);
        cout << "Masukkan Nomor RT: ";
        getline(cin, data[datasekarang][4]);
        datasekarang++;

        cout << "Apakah Mau Menambah Data Lagi Tekan y untuk menambahkan lagi atau tekan apapun untuk kembali:  ";
        ulang = getch();
        
        if (ulang == "y"){
            system("cls");
            tambah_data_warga();
        }
    } else {
        cout << "Data Penuh Pak RT !!!" << endl;
    }


}

void menu_pak_rt() {
    do{
        string pilih;
        cout << "===================================" << endl;
        cout << "Menu Pak RT" << endl;
        cout << "1. Tambah Data Warga" << endl;
        cout << "2. Lihat Data Warga" << endl;
        cout << "3. Ubah Data Warga" << endl;
        cout << "4. Hapus Data Warga" << endl;
        cout << "5. Kembali " << endl;
        cout << "6. EXIT " << endl;
        cout << "===================================" << endl;
        pilih = pilihann();
        system("cls");
        if (pilih == "1") {
            tambah_data_warga();
            system("cls");
        }else if (pilih == "2"){
            lihat_data_warga();
            tekan_apapun_untuk_lanjut();
            system("cls");
            
        }else if (pilih == "3"){
            ubah_data_warga();
            tekan_apapun_untuk_lanjut();
            system("cls");
            
        }else if (pilih == "4"){
            hapus_data_warga();
            tekan_apapun_untuk_lanjut();
            system("cls");
        }else if (pilih == "5"){
            break;
        }else if (pilih == "6"){
            exit(0);
        }else{
            cout<<"input tidak valid"<<endl;
        }
    }while (true);
}

bool login_pakrt(){
    string user,pw;
    int percobaan = 0;
    do{
        cout << "Masukkan Username: ";
        getline(cin,user);
        cout << "Masukkan Password: ";
        getline(cin,pw);
        
        if(user == "Raihanfitri adi kalipaksi" && pw == "2309106096"){
            break;
        }else{
            percobaan++;
            if(percobaan == 3){
                cout << "Silahkan Coba Lagi Nanti !!!!" << endl;
                return false;
            }else{
                cout <<"Silahkan Coba Lagi" << endl;
            }
        }

    }while (true);
    
}

int main(){
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
            if (login_pakrt()){
                menu_pak_rt();
            }else{
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
