#include "iostream"
#include "string"
#include "fstream"
#include "sstream"
#include "iomanip"
#include "ctime"
#include "conio.h"

using namespace std;

fstream Data;

void cekcsv(const string& filePath);
void hapusatauubah(string nama, int index);
void sort();
void tipesort(int pilihan);
void ubahPassword(string id,string password);
void loginmember();
void belibarang(string id);
void history_member(string id);
void menu();
void menuadmin();
void tambah();
void editstock(string nama);
void ubah(string ubahbarang);

struct Pengguna {
    string id;
    string password;
    int point;
};

struct history {
    string id;
    string nama;
    string pembayaran;
    int harga;
    int jumlah;
    string tanggal;
};

struct barang{
    string nama;
    int jumlah;
    int harga;
    string waktu;
    int pointmasuk;
    int pointkeluar;
    string kategori;
};

void print(const string& text, const string& colorCode) {
    cout << colorCode << text << "\033[0m" << endl; // "\033[0m" resets the color
}
void printnoendl(const string& text, const string& colorCode) {
    cout << colorCode << text << "\033[0m"; // "\033[0m" resets the color
}
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string RESET = "\033[0m";


int inputInteger(string pesan) {
    int num;
    string input;

    while (true) {
        cout << pesan;
        cin >> input;

        try {
            num = stoi(input);
            break;
        } catch (const invalid_argument& e) {
            print("Jangan memasukan nilai selain integer!!!.\n", RED);
        }
    }
    return num;
}

string inputString(const string& pesan, bool releaseBuff) {
    string hasil;

    // Fungsi untuk menghapus spasi di awal dan akhir string
    auto trim = [](const string& str) -> string {
        size_t first = 0;
        while (first < str.size() && str[first] == ' ') {
            ++first;
        }
        if (first == str.size()) {
            return ""; // String hanya berisi spasi
        }
        size_t last = str.size() - 1;
        while (last > first && str[last] == ' ') {
            --last;
        }
        return str.substr(first, last - first + 1);
    };

    if (releaseBuff) {
        fflush(stdin);
    }

    do {
        cout << pesan;
        getline(cin, hasil);
        
        // Trim the input to remove leading and trailing spaces
        hasil = trim(hasil);

        if (hasil.empty()) {
            cout << "Input tidak boleh kosong!!!\n";
        }
    } while (hasil.empty());

    return hasil;
}

int length(){
    int total = 0;
    string tmp;
    Data.open("data.csv", ios::in);
    // AMBIL TOTAL
    while (getline(Data, tmp)) {
        total++;
    };
    Data.close();
    return total;
}
int ukuran = length();

int length_riwayat(){
    int total = 0;
    string tmp;
    Data.open("riwayatpembelian.csv", ios::in);
    while(getline(Data, tmp)){
        total++;
    }
    Data.close();
    return total;
}

int length_user(){
    int total = 0;
    string tmp;
    Data.open("pengguna.csv", ios::in);
    // AMBIL TOTAL
    while (getline(Data, tmp)) {
        total++;
    };
    Data.close();
    return total;
}

bool cekpassword(const string& password) {
    if (password.empty()) {
        return false;
    }
    for (char ch : password) {
        if (ch == ' ') {
            return false;
        }
    }
    return true;
}

int pilihb(int pilihan, int item){
    while(true){
        system("cls");
        print("=========================================",CYAN);
        print("::                                     ::", YELLOW);
        printnoendl("::     ",YELLOW);printnoendl("Masukkan Barang Ke Keranjang?",GREEN);print("   ::", YELLOW);
        print("::                                     ::", YELLOW);
        print("=========================================",CYAN);
        printnoendl("::", YELLOW); cout << "                 [" << (pilihan == 0 ? ">" : " ") << "]YA               "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "                 [" << (pilihan == 1 ? ">" : " ") << "]NO               "; printnoendl("::", YELLOW); cout << endl;
        print("=========================================",CYAN);


        int input = _getch();
        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }
    }
    return pilihan;
}

int pilihanstock(int pilihan, int item){
    while(true){
        system("cls");
        print("=========================================",CYAN);
        printnoendl("::", YELLOW); cout << "  Barang Sudah Berada Di Dalam Data  "; printnoendl("::", YELLOW); cout << endl;
        print("=========================================",CYAN);
        print("::                                     ::", YELLOW);
        printnoendl("::", YELLOW); cout << "         Ingin Menambah Stock        "; printnoendl("::", YELLOW); cout << endl;
        print("::                                     ::", YELLOW);
        print("=========================================",CYAN);
        printnoendl("::", YELLOW); cout << "                 [" << (pilihan == 0 ? ">" : " ") << "]YA               "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "                 [" << (pilihan == 1 ? ">" : " ") << "]NO               "; printnoendl("::", YELLOW); cout << endl;
        print("=========================================",CYAN);


        int input = _getch();
        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }
    }
    return pilihan;
}

int edits(int pilihan, int item){
    while (true){
        system("cls");
        print("===========================",CYAN);
        print("::                       ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  STOCK SHOPPING MART  "; printnoendl("::", YELLOW); cout << endl;
        print("::                       ::", YELLOW);
        print("===========================",CYAN);
        print("::                       ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 0 ? ">" : " ") << "] Tambah Stock     "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 1 ? ">" : " ") << "] Kurangi Stock    "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 2 ? ">" : " ") << "] Kembali          "; printnoendl("::", YELLOW); cout << endl;
        print("::                       ::", YELLOW);
        print("===========================",CYAN);
        int input = _getch();
        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }
    }
    return pilihan;

}

int ubahdata(int pilihan, int item){
    while (true){
        system("cls");
        print("==================================", CYAN);
        print("::                              ::", YELLOW);
        printnoendl("::", YELLOW); cout << "      STOCK SHOPPING MART     "; printnoendl("::", YELLOW); cout << endl;
        print("::                              ::", YELLOW);
        print("==================================", CYAN);
        print("::                              ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 0 ? ">" : " ") << "] Ubah Nama               "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 1 ? ">" : " ") << "] Ubah Jumlah Stock       "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 2 ? ">" : " ") << "] Ubah Harga              "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 3 ? ">" : " ") << "] Ubah Point Di Dapat     "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 4 ? ">" : " ") << "] Ubah Harga Point Barang "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 5 ? ">" : " ") << "] Ubah Kategori           "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 6 ? ">" : " ") << "] Kembali                 "; printnoendl("::", YELLOW); cout << endl;  
        print("::                              ::", YELLOW);
        print("==================================", CYAN);
        int input = _getch();
        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }
    }
    return pilihan;

}

int tampilkan_menu(int pilihan, int item) {
   
    while (true) {
        
        system("cls");
        print("============================",CYAN);
        print("::                        ::", YELLOW);
        printnoendl("::", YELLOW); cout << "      Shopping Mart     "; printnoendl("::", YELLOW); cout << endl;
        print("::                        ::", YELLOW);
        print("============================",CYAN);
        print("::                        ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 0 ? ">" : " ") << "] Login Admin       "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 1 ? ">" : " ") << "] Login Member      "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 2 ? ">" : " ") << "] Register Member   "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 3 ? ">" : " ") << "] Buy Items         "; printnoendl("::", YELLOW); cout << endl;
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 4 ? ">" : " ") << "] Exit              "; printnoendl("::", YELLOW); cout << endl;
        print("::                        ::", YELLOW);
        print("============================",CYAN);

        int input = _getch();

        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }
    }
    return pilihan;
}

int kategorimenu(int pilihan, int item){
    while (true){
        system("cls");
        print("====================================", CYAN);
        print("::                                ::", YELLOW);
        printnoendl("::", YELLOW); cout << "             KATEGORI           "; printnoendl("::", YELLOW);cout << endl;
        print("::                                ::", YELLOW);
        print("====================================", CYAN);
        print("::                                ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 0 ? ">" : " ") << "] Makanan                   "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 1 ? ">" : " ") << "] Minuman                   "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 2 ? ">" : " ") << "] Mainan                    "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 3 ? ">" : " ") << "] Bahan Pokok               "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 4 ? ">" : " ") << "] Pengharum                 "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 5 ? ">" : " ") << "] Kebersihan                "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 6 ? ">" : " ") << "] Pakaian                   "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 7 ? ">" : " ") << "] Perlengkapan Sekolah      "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 8 ? ">" : " ") << "] Perlengkapan Rumah Tangga "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 9 ? ">" : " ") << "] Lain-Lain                 "; printnoendl("::", YELLOW);cout << endl; 
        print("::                                ::", YELLOW);
        print("====================================", CYAN);


        int input = _getch();
        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }
    }
    return pilihan;
}

int admin(int pilihan, int item){
    while (true){

        system("cls");

        print("============================", CYAN);
        print("::                        ::", YELLOW);
        printnoendl("::", YELLOW); cout << "      Shopping Mart     "; printnoendl("::", YELLOW); cout << endl;
        print("::                        ::", YELLOW);
        print("============================", CYAN);
        print("::                        ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 0 ? ">" : " ") << "] Tambah Barang     "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 1 ? ">" : " ") << "] Tampilkan Barang  "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 2 ? ">" : " ") << "] Filtering Kategori"; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 3 ? ">" : " ") << "] Sorting Barang    "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 4 ? ">" : " ") << "] Searching Barang  "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 5 ? ">" : " ") << "] History Pembelian "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 6 ? ">" : " ") << "] Kembali           "; printnoendl("::", YELLOW);cout << endl; 

        print("::                        ::", YELLOW);
        print("============================", CYAN);

        int input = _getch();
        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }

    }
    return pilihan;
}

int menubeli(int pilihan, int item){
    while(true){
        system("cls");
        
        print("======================================", CYAN);
        print("::                                  ::", YELLOW);
        printnoendl("::", YELLOW); cout << "       Welcome Shopping Mart      "; printnoendl("::", YELLOW);cout << endl; 
        print("::                                  ::", YELLOW);
        print("======================================", CYAN);
        print("::                                  ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 0 ? ">" : " ") << "] Cari Nama Produk            "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 1 ? ">" : " ") << "] Lihat Keranjang             "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 2 ? ">" : " ") << "] Lihat Kategori Produk       "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 3 ? ">" : " ") << "] Lanjut Ke Pembayran         "; printnoendl("::", YELLOW);cout << endl; 
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 4 ? ">" : " ") << "] Cancel Pembeliian / Kembali "; printnoendl("::", YELLOW);cout << endl; 

        print("::                                  ::", YELLOW);
        print("======================================", CYAN);
        int input = _getch();
        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }

    }
    return pilihan;
}

int beli(int jumlah, int item) {
    
    while (true) {
        system("cls"); 
        if (jumlah+1 >= 0 and jumlah+1 <= 9){
            print("===========================", CYAN);
            printnoendl("::",CYAN);cout << " Jumlah Barang Di Beli ";print("::",CYAN);
            print("===========================", CYAN);
            print("::                       ::", YELLOW);
            printnoendl("::          [",YELLOW);cout << jumlah + 1 ;print("]          ::",YELLOW);
            print("::                       ::", YELLOW);
            print("===========================", CYAN);
        }else if(jumlah+1 > 9 and jumlah+1 <= 99){
            print("===========================", CYAN);
            printnoendl("::",CYAN);cout << " Jumlah Barang Di Beli ";print("::",CYAN);
            print("===========================", CYAN);
            print("::                       ::", YELLOW);
            printnoendl("::          [",YELLOW);cout << jumlah + 1 ;print("]          ::",YELLOW);
            print("::                       ::", YELLOW);
            print("===========================", CYAN);

        }else if(jumlah+1 > 99){
          
            print("===========================", CYAN);
            printnoendl("::",CYAN);cout << " Jumlah Barang Di Beli ";print("::",CYAN);
            print("===========================", CYAN);
            print("::                       ::", YELLOW);
            printnoendl("::          [",YELLOW);cout << jumlah + 1 ;print("]          ::",YELLOW);
            print("::                       ::", YELLOW);
            print("===========================", CYAN);
        }


        
        int input = _getch();


        if (input == 72) {
            if(jumlah < item-1){

                jumlah++;
            }


   
        } else if (input == 80) {
            if(jumlah > 0) {
                jumlah--;
            }

      
        } else if (input == 13) {
            break;  

        }

       
        
    }

    return jumlah;
}

int belipake(int pilihan, int item){
    while(true){
        system("cls");
        print("===========================", CYAN);
        print("::                       ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  STOCK SHOPPING MART  "; print("::", YELLOW); 
        print("::                       ::", YELLOW);
        print("===========================", CYAN);

        print("::                       ::", YELLOW);
        printnoendl("::", YELLOW); cout << " [" << (pilihan == 0 ? ">" : " ") << "] Beli Dengan Point "; print("::", YELLOW); 
        printnoendl("::", YELLOW); cout << " [" << (pilihan == 1 ? ">" : " ") << "] Beli Dengan Cash  "; print("::", YELLOW); 
        printnoendl("::", YELLOW); cout << " [" << (pilihan == 2 ? ">" : " ") << "] Kembali           "; print("::", YELLOW); 
        print("::                       ::", YELLOW);
        print("===========================", CYAN);

        int input = _getch();
        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }    
    }
    return pilihan;
}
void cekcsv(const string& filePath) {
    cout << endl;
    ifstream file(filePath);

    // Jika file tidak ditemukan, buat file baru
    if (!file.is_open()) {
        printnoendl("FILE ",RED);cout << filePath; print(" tidak ditemukan. File sedang dibuat...",RED);
        
        ofstream newFile(filePath);
        if (!newFile.is_open()) {
            printnoendl("ERROR : File tidak bisa dibuat.",RED);
            system("pause");
            menu();
        }

        
        printnoendl("FILE ",RED);cout << filePath; print(" telah dibuat. Silakan mulai dari awal.",RED);
        newFile.close();
        system("pause");
        menu();

    }

    // Jika file ditemukan, cek apakah file kosong
    if(filePath == "data.csv"){
        file.seekg(0, ios::end);
        if (file.tellg() == 0) {
            printnoendl("FILE ",RED);cout << filePath; print(" Kosong.",RED);
            file.close();
            system("pause");
            menu();
        }
    }

    file.close();
}
void tambahstock(string nama) {
    bool barangg = false;
    int panjangData = length();
    int i = 0;
    barang Barang[1000];
    Data.open("data.csv", ios::in);
    if (!Data.is_open()){
        return;
    }
    
    while (!Data.eof()) {
        getline(Data, Barang[i].nama, ',');
        if (Barang[i].nama.empty()){
            break;
        }
        Data >> Barang[i].jumlah;  
        Data.ignore(1);  
        Data >> Barang[i].harga; 
        Data.ignore(1);  
        getline(Data, Barang[i].waktu, ',');
        Data >> Barang[i].pointmasuk;  
        Data.ignore(1);  
        Data >> Barang[i].pointkeluar;  
        Data.ignore(1);  
        getline(Data, Barang[i].kategori, '\n'); 
        i++;  
    }
    Data.close();  

    for (int j = 0; j < panjangData; j++) {
        if (Barang[j].nama == nama) {
            barangg =true;
            goto menustock;
            
        } 
        
    }
    if (barangg == true){
        menustock:
        string pilih;
        system("cls");


        int pilihan = pilihanstock(0,2);
        enum kategori{y=0,t};

        switch(pilihan){
            case y: pilih = "y"; break;
            case t: pilih = "t"; break;
        }

        if (pilih == "y"){
            system("cls");
            editstock(nama);
        }
        else if(pilih == "t"){
            system("cls");
            menuadmin();
        }else {
            system("cls");
            print("===========================", CYAN);
            printnoendl("::", YELLOW); cout << "  Pilihan Tidak Valid  "; print("::", YELLOW);
            print("===========================", CYAN);
            system("pause");
            system("cls");
            goto menustock;
        }
    }
}
  
void tambah(){
    string filePath = "data.csv";
    ifstream file(filePath);
    // Jika file tidak ditemukan, buat file baru
    if (!file.is_open()) {
        printnoendl("FILE ",RED);cout << filePath; print(" tidak ditemukan. File sedang dibuat...",RED);
        
        ofstream newFile(filePath);
        if (!newFile.is_open()) {
            printnoendl("ERROR : File tidak bisa dibuat.",RED);
            system("pause");
            menu();
        }

        
        printnoendl("FILE ",RED);cout << filePath; print(" telah dibuat. Silakan mulai dari awal.",RED);
        newFile.close();
        system("pause");
        menu();

    }
    
    system("cls");

    string nama;
    barang Barang;
    print("============================",CYAN);
    printnoendl("::", YELLOW); cout << "    TAMBAH DATA BARANG  "; printnoendl("::", YELLOW); cout << endl;
    print("============================",CYAN);
    cout << endl;
    cout << endl;

    nama = inputString("Nama Barang : ", true);

    tambahstock(nama);
    Barang.nama = nama;


    Barang.jumlah = inputInteger("Jumlah Barang : ");
    Barang.harga = inputInteger("Harga Barang : ");
    Barang.pointmasuk = inputInteger("Point Yang Di Dapat Member : ");
    Barang.pointkeluar = inputInteger("Harga Barang Dalam Point : ");
    system("cls");
    enum kategori {makanan=0, minuman, mainan, bahan_pokok, pengharum, kebersihan, pakaian, perlengkapan_sekolah, perlengkapan_rumah_tangga, lain_lain};


    int pilihan = kategorimenu(0,10);
    switch (pilihan){
        case makanan:Barang.kategori = "Makanan";break;
        case minuman:Barang.kategori = "Minuman";break;
        case mainan:Barang.kategori = "Mainan";break;
        case bahan_pokok:Barang.kategori = "Bahan Pokok";break;
        case pengharum:Barang.kategori = "Pengharum";break;
        case kebersihan:Barang.kategori = "Kebersihan";break;
        case pakaian:Barang.kategori = "Pakaian";break;
        case perlengkapan_sekolah:Barang.kategori = "Perlengkapan Sekolah";break;
        case perlengkapan_rumah_tangga:Barang.kategori = "Perlengkapan Rumah Tangga";break;
        case lain_lain:Barang.kategori = "Lain-Lain";break;
  
    }
    time_t now = time(nullptr);
    char* time = ctime(&now);
    string clean_time(time);
    clean_time.erase(clean_time.find('\n'));

    Barang.waktu = clean_time;
    Data.open("data.csv", ios :: app);
    Data <<Barang.nama << ", " << Barang.jumlah << ", "<< Barang.harga << ", "<< Barang.waktu << ", " << Barang.pointmasuk << ", " << Barang.pointkeluar << ", " << Barang.kategori << endl;
    Data.close();
    print("Berhasil ditambahkan", GREEN);
   
}

void editstock(string nama) {
    int i = 0;
    barang Barang[1000];
    int panjangData = length();
    Data.open("data.csv", ios::in);
    
    // Membaca data barang dari file
    while (!Data.eof() && i < 1000) {
        getline(Data, Barang[i].nama, ',');
        if (Barang[i].nama.empty()) {
            break;
        }
        Data >> Barang[i].jumlah;
        Data.ignore(1);
        Data >> Barang[i].harga;
        Data.ignore(1);
        getline(Data, Barang[i].waktu, ',');
        Data >> Barang[i].pointmasuk;
        Data.ignore(1);
        Data >> Barang[i].pointkeluar;
        Data.ignore(1);
        getline(Data, Barang[i].kategori, '\n');
        i++;
    }
    Data.close();
    bool found = false;
    for (int j = 0; j < panjangData; j++) {
        if (Barang[j].nama == nama) {
            found = true;

            int pilihan = edits(0,3);
            enum pilih{tambah_stock = 0, kurangi_stock,kembali};

            switch (pilihan) {
                case tambah_stock:
                int jumlah_tambah;
                jumlah_tambah = beli(0,100000);
                Barang[j].jumlah += jumlah_tambah;
                system("cls");
                print("===================================", CYAN);
                printnoendl("::", YELLOW); cout << "  STOCK BERHASIL DI TAMBAHKAN  "; print("::", YELLOW); 
                print("===================================", CYAN);
                system("pause");
                break;

                case kurangi_stock:
                int jumlah_kurang;
                jumlah_kurang = beli(0,100000);
                if (jumlah_kurang <= Barang[j].jumlah) {
                    Barang[j].jumlah -= jumlah_kurang;
                    print("=================================", CYAN);
                    printnoendl("::", YELLOW); cout << "  STOCK BERHASIL DI KURANGI  "; print("::", YELLOW); 
                    print("=================================", CYAN);
                    break;
                } else {
                    print("==============================================================", CYAN);
                    printnoendl("::", YELLOW); cout << "  Jumlah pengurangan melebihi jumlah stock yang tersedia  "; print("::", YELLOW);
                    print("==============================================================", CYAN);
                }
                break;
                case kembali:
                menuadmin();
            }

            Data.open("data.csv", ios::out | ios::trunc);
            for (int k = 0; k < i; k++) {
                Data << Barang[k].nama << ","
                     << Barang[k].jumlah << ","
                     << Barang[k].harga << ","
                     << Barang[k].waktu << ","
                     << Barang[k].pointmasuk << ","
                     << Barang[k].pointkeluar << ","
                     << Barang[k].kategori << endl;
            }
            Data.close();

            break;
        }
    }

    if (!found) {
        print("Barang tidak ditemukan.", RED);
    }
    menuadmin();
}

void tampil(){
    cekcsv("data.csv");
    int i = 0;
    string line;
    Data.open("data.csv", ios :: in);
    string nama,harga,jumlah,waktu,pointmasuk,pointkeluar,kategori;
    if(!Data.is_open()){
        cout << "Data Tidak Di Temukan" << endl;
        menuadmin();
    }
    print( "===========================================================================================================================================================", GREEN);
    print("| NO |      Nama Barang      | Jumlah Barang | Harga Barang |        Waktu Input        |  Point Di Dapat  | Harga Point |            Kategori            |",GREEN);
    print( "===========================================================================================================================================================", GREEN);
   
    while (getline(Data, nama, ',') &&
           getline(Data, jumlah, ',') &&
           getline(Data, harga, ',') &&
           getline(Data, waktu, ',') &&
           getline(Data, pointmasuk, ',') &&
           getline(Data, pointkeluar, ',') &&
           getline(Data, kategori, '\n')) {

        if (nama.empty() && harga.empty() && jumlah.empty() && waktu.empty()&&
            pointmasuk.empty() && pointkeluar.empty() && kategori.empty()) {
            break;
        }

        printnoendl("| ", GREEN); cout << setw(2) << i + 1; printnoendl(" | ", GREEN);
             cout << setw(21) << nama; printnoendl(" | ", GREEN);
             cout << setw(13) << jumlah; printnoendl(" | ", GREEN);
             cout << setw(12) << harga; printnoendl(" | ", GREEN);
             cout << setw(12) << waktu; printnoendl(" | ", GREEN);
             cout << setw(16) << pointmasuk; printnoendl(" | ", GREEN);
             cout << setw(11) << pointkeluar; printnoendl(" | ", GREEN);
             cout << setw(30) << kategori; printnoendl(" | ", GREEN);cout << endl;

        i++;
    }
    Data.close();
    print( "===========================================================================================================================================================", GREEN);
}
void hapus(int index){
    
    int i = 1;
    string barang, waktu, harga, nama, jumlah, pointmasuk, pointkeluar, kategori;
    string temp;
    ifstream data("data.csv");
    while (getline(data, barang)) {
        if (i != index) {
            stringstream line(barang);
            getline(line, nama, ',');
            getline(line, jumlah, ',');
            getline(line, harga, ',');
            getline(line, waktu, ',');
            getline(line, pointmasuk, ',');
            getline(line, pointkeluar, ',');
            getline(line, kategori, '\n');
            temp += nama + "," + jumlah + "," + harga + "," + waktu + "," + pointmasuk + "," + pointkeluar + "," + kategori + "\n";
        }
        i++;
    }
    data.close();
    ofstream outData("data.csv", ios::out | ios::trunc);
    outData << temp;
    outData.close();
    system("cls");
    print("==============================",CYAN);
    print("::                          ::", YELLOW);
    printnoendl("::", YELLOW); cout << " Data Berhasil Di Hapus   "; print("::", YELLOW); 
    print("::                          ::", YELLOW);
    print("==============================",CYAN);
    system("pause");
    menuadmin();

}

void ubah(string namabarang){
    int panjangData = length();
    barang Barang [panjangData];
    int i = 0;
    Data.open("data.csv", ios::in);
    while (!Data.eof() && i < panjangData) {
        getline(Data, Barang[i].nama, ','); 
        if (Barang[i].nama.empty()) {
            break;
        }
        Data >> Barang[i].jumlah;  
        Data.ignore(1);  
        Data >> Barang[i].harga; 
        Data.ignore(1);  
        getline(Data, Barang[i].waktu, ',');
        Data >> Barang[i].pointmasuk;  
        Data.ignore(1);  
        Data >> Barang[i].pointkeluar;  
        Data.ignore(1);  
        getline(Data, Barang[i].kategori, '\n'); 
        i++;  
    }
    Data.close();
    string temp, nama;
    int harga, pointmasuk, pointkeluar,kategori;
    for (int j = 0;j < panjangData; ++j){
        if (namabarang == Barang[j].nama){
            enum pilih{ubahnama = 0, ubahjumlah, ubahharga,  ubahpointm, ubahpointk, ubahkategori, kembali};
            int pilih = ubahdata(0,7);
           
            switch (pilih){
                ulang:
                case ubahnama:nama = inputString("Masukkan Nama Barang Baru : ", true);
                    for (int p = 0 ; p < panjangData; p++){
                        if(nama == Barang[p].nama){
                            print("Nama Barang Sudah Berada Di Dalam Data",GREEN);
                            goto ulang;
                        }
                    }
                    Barang[j].nama = nama;
                    break; 
                case ubahharga : harga = inputInteger("Masukkan Harga Barang Baru : ");
                    Barang[j].harga = harga; 
                    break;
                case ubahjumlah : editstock(namabarang);
                    break;
                case ubahpointm : pointmasuk = inputInteger("Masukkan Point Di Dapat Baru : ");
                    Barang[j].pointmasuk = pointmasuk;
                    break;
                case ubahpointk : pointkeluar = inputInteger("Masukkan Harga Barang Dalam Bentuk Point Baru : ");
                    Barang[j].pointkeluar = pointkeluar;
                    break;
                case ubahkategori :
                    kategori = kategorimenu(0,10);
                    enum pilih {makanan=0, minuman, mainan, bahan_pokok, pengharum, kebersihan, pakaian, perlengkapan_sekolah, perlengkapan_rumah_tangga, lain_lain};
                    switch (kategori){
                        case makanan:Barang[j].kategori = "Makanan";break;
                        case minuman:Barang[j].kategori = "Mainan";break;
                        case mainan:Barang[j].kategori = "Minuman";break;
                        case bahan_pokok:Barang[j].kategori = "Bahan Pokok";break;
                        case pengharum:Barang[j].kategori = "Pengharum";break;
                        case kebersihan:Barang[j].kategori = "Kebersihan";break;
                        case pakaian:Barang[j].kategori = "Pakaian";break;
                        case perlengkapan_sekolah:Barang[j].kategori = "Perlengkapan Sekolah";break;
                        case perlengkapan_rumah_tangga:Barang[j].kategori = "Perlengkapan Rumah Tangga";break;
                        case lain_lain:Barang[j].kategori = "Lain-Lain";break;
                    }
                    break;
                case kembali:return;

            }
            
            Data.open("data.csv", ios::out | ios::trunc);
            for (int k = 0; k < i; k++) {
                Data << Barang[k].nama << ","
                     << Barang[k].jumlah << ","
                     << Barang[k].harga << ","
                     << Barang[k].waktu << ","
                     << Barang[k].pointmasuk << ","
                     << Barang[k].pointkeluar << ","
                     << Barang[k].kategori<< endl;
            }
            Data.close();

            break;
        }

    }
    print("==============================",CYAN);
    print("::                          ::", YELLOW);
    printnoendl("::", YELLOW); cout << "  Data Berhasil Di Ubah   "; print("::", YELLOW); 
    print("::                          ::", YELLOW);
    print("==============================",CYAN);
    system("pause");
    
}

void TampilKategori(const string& kategori) {
    int panjangdatabarang = length();
    int panjangData = 0 ;
    barang Barang[panjangdatabarang];
    
    ifstream data("data.csv");
    if (!data.is_open()) {
        cout << "Gagal membuka file data.csv" << endl;
        return;
    }
    while (!data.eof() && panjangData < panjangdatabarang) {
        getline(data, Barang[panjangData].nama, ',');
        if (Barang[panjangData].nama.empty()) {
            break;
        }
        data >> Barang[panjangData].jumlah;
        data.ignore(1);
        data >> Barang[panjangData].harga;
        data.ignore(1);
        getline(data, Barang[panjangData].waktu, ',');
        data >> Barang[panjangData].pointmasuk;
        data.ignore(1);
        data >> Barang[panjangData].pointkeluar;
        data.ignore(1);
        getline(data, Barang[panjangData].kategori, '\n');
        panjangData++;
    }
    data.close();
    bool hasBarang = false;
    int pilihankat = 0;
    for (int i = 0; i < panjangData; i++) {
        if (Barang[i].kategori == " " + kategori || Barang[i].kategori == kategori) {
            hasBarang = true;
            break;
        }
    }
    if (!hasBarang) {
        print("===================================================", CYAN);
        printnoendl("::", YELLOW);cout << "     Barang Dengan Kategori " << kategori << " kosong     ";print("::", YELLOW);
        print("===================================================", CYAN);
        system("pause");
        return;
    }
    while (true) {
        system("cls");
        int count = 0;
        int indeksTerpilih = -1; 
        print("============================================================================================================================================================", GREEN);
        print("| PILIH |      Nama barang      | Jumlah barang | Harga barang |        Waktu Input        |  Point Masuk  | Point Keluar |             Kategori           |", GREEN);
        print("============================================================================================================================================================", GREEN);
        for (int z = 0; z < panjangData; z++) {
            if (Barang[z].kategori == " " + kategori || Barang[z].kategori == kategori) {
                printnoendl( "|   ", GREEN);cout << (pilihankat == count ? ">" : " ");
                
                printnoendl("    | ", GREEN);cout << setw(21) << Barang[z].nama;
                printnoendl(" | ", GREEN); cout << setw(13) << Barang[z].jumlah;
                printnoendl(" | ", GREEN); cout << setw(12) << fixed << setprecision(2) << Barang[z].harga;
                printnoendl(" | ", GREEN); cout << setw(12) << Barang[z].waktu;
                printnoendl(" | ", GREEN); cout << setw(13) << Barang[z].pointmasuk;
                printnoendl(" | ", GREEN); cout << setw(12) << Barang[z].pointkeluar;
                printnoendl(" | ", GREEN); cout << setw(29) << Barang[z].kategori;
                printnoendl(" |", GREEN); cout << endl;
                if (pilihankat == count) {
                    indeksTerpilih = z;
                }
                count++;
            }
        }
        print("============================================================================================================================================================", GREEN);
        int input = _getch();
        if (input == 72) {  // Panah atas
            if (pilihankat > 0) {
                pilihankat--;
            }
        } else if (input == 80) {  // Panah bawah
            if (pilihankat < count - 1) {
                pilihankat++;
            }
        } else if (input == 13) {  // Enter
            if (indeksTerpilih != -1) {
                int index = indeksTerpilih + 1;
                hapusatauubah(Barang[indeksTerpilih].nama,index);
                menuadmin();
 
            } else {
                print("Data tidak ada!", RED);
                system("pause");
            }
        }
    }
}

void hapusatauubah(string nama, int index){
    int panjangdatabarang = length();
    int panjangData = 0 ;
    barang Barang[panjangdatabarang];
    
    ifstream data("data.csv");
    while (!data.eof() && panjangData < panjangdatabarang) {
        getline(data, Barang[panjangData].nama, ',');
        if (Barang[panjangData].nama.empty()) {
            break;
        }
        data >> Barang[panjangData].jumlah;
        data.ignore(1);
        data >> Barang[panjangData].harga;
        data.ignore(1);
        getline(data, Barang[panjangData].waktu, ',');
        data >> Barang[panjangData].pointmasuk;
        data.ignore(1);
        data >> Barang[panjangData].pointkeluar;
        data.ignore(1);
        getline(data, Barang[panjangData].kategori, '\n');
        panjangData++;
    }
    data.close();
    int pilihan = 0;
    int item = 3;
    while(true){
        system("cls");
        
        print("======================================", CYAN);
        print("::                                  ::", YELLOW);
        printnoendl("::",YELLOW);cout << "      Admin menu Shopping Mart    ";print("::",YELLOW);
        print("::                                  ::", YELLOW);
        print("======================================", CYAN);
        print("::                                  ::", YELLOW);
        printnoendl("::",YELLOW);cout << "   [" << (pilihan == 0 ? ">" : " ") <<"] Ubah                       ";print("::",YELLOW);
        printnoendl("::",YELLOW);cout << "   [" << (pilihan == 1 ? ">" : " ") <<"] Hapus                      ";print("::",YELLOW);
        printnoendl("::",YELLOW);cout << "   [" << (pilihan == 2 ? ">" : " ") <<"] kembali                    ";print("::",YELLOW);
        print("::                                  ::", YELLOW);
        print("======================================", CYAN);
        int input = _getch();
        if (input == 72) {
            if (pilihan > 0) {
                pilihan--;
            }
        } else if (input == 80) {
            if (pilihan < item - 1) {
                pilihan++;
            }
        } else if (input == 13) {
            
            break; 
        }

    }

    enum pilih {update = 0,del,kembali};

    switch (pilihan){
        case update: ubah(nama);break;
        case del: hapus(index); break;
    }
}

void filteringkategori() {
    cekcsv("data.csv");
    ulang:
    enum kategori { makanan = 0, minuman, mainan, bahanpokok, pengharum, kebersihan, pakaian, sekolah, rumah, lainlain };
    int pilihkategori = kategorimenu(0, 10);
    switch (pilihkategori) {
        case makanan:
            TampilKategori("Makanan");
            break;
        case minuman:
            TampilKategori("Minuman");
            break;
        case mainan:
            TampilKategori("Mainan");
            break;
        case bahanpokok:
            TampilKategori("Bahan Pokok");
            break;
        case pengharum:
            TampilKategori("Pengharum");
            break;
        case kebersihan:
            TampilKategori("Kebersihan");
            break;
        case pakaian:
            TampilKategori("Pakaian");
            break;
        case sekolah:
            TampilKategori("Perlengkapan Sekolah");
            break;
        case rumah:
            TampilKategori("Perlengkapan Rumah Tangga");
            break;
        case lainlain:
            TampilKategori("Lain-Lain");
            break;
        // Add other cases here
        default:
            break;
    }
    goto ulang;
}

// Fungsi untuk mencetak data barang
void cetakbarang(const barang& item, int index, bool isHighlighted) {

    if (isHighlighted) {
        printnoendl("|  ", GREEN); cout << ">";
    } else {
        printnoendl("|   ", GREEN);

    }
    
    printnoendl("    | ", GREEN);cout << setw(21) << item.nama;
    printnoendl(" | ", GREEN); cout << setw(13) << item.jumlah;
    printnoendl(" | ", GREEN); cout << setw(12) << fixed << setprecision(2) << item.harga;
    printnoendl(" | ", GREEN); cout << setw(12) << item.waktu;
    printnoendl(" | ", GREEN); cout << setw(13) << item.pointmasuk;
    printnoendl(" | ", GREEN); cout << setw(12) << item.pointkeluar;
    printnoendl(" | ", GREEN); cout << setw(29) << item.kategori;
    printnoendl(" |", GREEN); cout << endl;


}

void tampilkanhasilsorting(barang databarang[], int ukuran) {
    // Simpan kembali data ke file CSV setelah penghapusan
    
    ofstream masukfile("data.csv");
    
    for (int i = 0; i < ukuran; ++i) {
        masukfile << databarang[i].nama << "," << databarang[i].jumlah << "," << databarang[i].harga << ","
                    << databarang[i].waktu << "," << databarang[i].pointmasuk << "," << databarang[i].pointkeluar << ","
                    << databarang[i].kategori << endl;
    }
    masukfile.close();
    
    
    ofstream outputFile("data.csv");

    for (int i = 0; i < ukuran; ++i) {
        outputFile << databarang[i].nama << "," << databarang[i].jumlah << "," << databarang[i].harga << ","
                    << databarang[i].waktu << "," << databarang[i].pointmasuk << "," << databarang[i].pointkeluar << ","
                    << databarang[i].kategori << endl;
    }
    outputFile.close();


    int highlight = 0;
    int choice;
    int c;

    while (true) {
        system("cls");
        print("===========================================================================================================================================================", GREEN);
        print("| PILIH |      Nama barang      | Jumlah barang | Harga barang |        Waktu Input        |  Point Masuk  | Point Keluar |            Kategori           |", GREEN);
        print("===========================================================================================================================================================", GREEN);

        for (int i = 0; i < ukuran; ++i) {
            cetakbarang(databarang[i], i, i == highlight);
        }
        print("===========================================================================================================================================================", GREEN);

        c = _getch();
        switch (c) {
            case 72: // Panah atas
                if (highlight > 0) {
                    highlight--;
                }
                break;
            case 80: // Panah bawah
                if (highlight < ukuran - 1) {
                    highlight++;
                }
                break;
            case 13: // Enter key
                choice = highlight;
                cout << "Item yang dipilih: " << databarang[choice].nama << endl;
                system("pause");
                if (choice != -1) {
                    int index = choice + 1;
                    hapusatauubah(databarang[choice].nama,index);
                    menuadmin();
                } else {
                    cout << "Data tidak ada!";
                    system("pause");
                }
                return; // Keluar dari loop setelah memilih
            default:
                break;
        }
    }
}

void insertionsortNama(barang databarang[], int ukuran) {
    for (int i = 1; i < ukuran; ++i) {
        barang key = databarang[i];
        int j = i - 1;

        while (j >= 0 && databarang[j].nama > key.nama) {
            databarang[j + 1] = databarang[j];
            j = j - 1;
        }
        databarang[j + 1] = key;
    }
}

void insertionsortJumlah(barang databarang[], int ukuran) {
    for (int i = 1; i < ukuran; ++i) {
        barang key = databarang[i];
        int j = i - 1;

        while (j >= 0 && databarang[j].jumlah > key.jumlah) {
            databarang[j + 1] = databarang[j];
            j = j - 1;
        }
        databarang[j + 1] = key;
    }
}

void insertionsortKategori(barang databarang[], int ukuran) {
    for (int i = 1; i < ukuran; ++i) {
        barang key = databarang[i];
        int j = i - 1;

        while (j >= 0 && databarang[j].kategori > key.kategori) {
            databarang[j + 1] = databarang[j];
            j = j - 1;
        }
        databarang[j + 1] = key;
    }
}

void reverseArray(barang databarang[], int ukuran) {
    for (int i = 0; i < ukuran / 2; ++i) {
        barang temp = databarang[i];
        databarang[i] = databarang[ukuran - i - 1];
        databarang[ukuran - i - 1] = temp;
    }
}

void tipesort(int pilihan) {
    ukuran = length();
    barang databarang[1000];
    system("cls");
    
    Data.open("data.csv", ios::in);

    string baris;
    int i = 0;
    while (getline(Data, baris)) {
        stringstream ss(baris);
        string nama, history, kategori;
        int jumlah, harga, pointMasuk, pointKeluar;
        getline(ss, nama, ',');
        ss >> jumlah;
        ss.ignore();
        ss >> harga;
        ss.ignore();
        getline(ss, history, ',');
        ss >> pointMasuk;
        ss.ignore();
        ss >> pointKeluar;
        ss.ignore();
        getline(ss, kategori, ',');
        databarang[i++] = {nama, jumlah, harga, history, pointMasuk, pointKeluar, kategori};
    }
    Data.close();
    int choice;
    if (pilihan == 1) {
        int choice = 1; // Pilihan default pada opsi pertama
        while (true) {
            system("cls");
            print("====================================", CYAN);
            print("::                                ::", YELLOW);
            printnoendl("::", YELLOW); cout << "         PILIH TIPE SORT        "; print("::", YELLOW);
            print("::                                ::", YELLOW);
            print("====================================", CYAN);
            print("::                                ::", YELLOW);
            printnoendl("::", YELLOW);cout << "  [" << (choice == 1 ? ">" : " ") << "] ABJAD A - Z               ";print("::",YELLOW);
            printnoendl("::", YELLOW);cout << "  [" << (choice == 2 ? ">" : " ") << "] ABJAD Z - A               ";print("::",YELLOW);
            printnoendl("::", YELLOW);cout << "  [" << (choice == 3 ? ">" : " ") << "] KEMBALI                   ";print("::",YELLOW);
            print("::                                ::", YELLOW);
            print("====================================", CYAN);


            int input = _getch();
            if (input == 72) { // Tombol panah atas
                choice = (choice == 1) ? 3 : choice - 1;
            } else if (input == 80) { // Tombol panah bawah
                choice = (choice == 3) ? 1 : choice + 1;
            } else if (input == 13) { // Tombol Enter
                if (choice == 1) {
                    insertionsortNama(databarang,ukuran);
                    tampilkanhasilsorting(databarang, ukuran);
                    system("pause");
                } else if (choice == 2) {
                    insertionsortNama(databarang,ukuran);
                    reverseArray(databarang, ukuran);
                    tampilkanhasilsorting(databarang, ukuran);
                    system("pause");
                } else if (choice == 3) {
                    return;
                }
            }
        }
    } else if (pilihan == 2) {
        int choice = 1; // Pilihan default pada opsi pertama
        while (true) {
            system("cls");
            print("====================================", CYAN);
            print("::                                ::", YELLOW);
            printnoendl("::",YELLOW); cout <<"         PILIH TIPE SORT        ";print("::",YELLOW);
            print("::                                ::", YELLOW);
            print("====================================", CYAN);

            print("::                                ::", YELLOW);
            printnoendl("::", YELLOW); cout << "  [" << (choice == 1 ? ">" : " ") << "] JUMLAH TERENDAH           "; print("::", YELLOW);
            printnoendl("::", YELLOW); cout << "  [" << (choice == 2 ? ">" : " ") << "] JUMLAH TERTINGGI          "; print("::", YELLOW);
            printnoendl("::", YELLOW); cout << "  [" << (choice == 3 ? ">" : " ") << "] KEMBALI                   "; print("::", YELLOW);
            print("::                                ::", YELLOW);
            print("====================================", CYAN);


            int input = _getch();
            if (input == 72) { // Tombol panah atas
                choice = (choice == 1) ? 3 : choice - 1;
            } else if (input == 80) { // Tombol panah bawah
                choice = (choice == 3) ? 1 : choice + 1;
            } else if (input == 13) { // Tombol Enter
                if (choice == 1) {
                    insertionsortJumlah(databarang, ukuran);
                    tampilkanhasilsorting(databarang, ukuran);
                    system("pause");
                } else if (choice == 2) {
                    insertionsortJumlah(databarang, ukuran);
                    reverseArray(databarang, ukuran);
                    tampilkanhasilsorting(databarang, ukuran);
                    system("pause");
                } else if (choice == 3) {
                    return;
                }
            }
        }
    } else if (pilihan == 3) {

        int choice = 1; // Pilihan default pada opsi pertama
        while (true) {
            system("cls");
            print("====================================", CYAN);
            print("::                                ::", YELLOW);
            printnoendl("::",YELLOW); cout <<"         PILIH TIPE SORT        ";print("::",YELLOW);
            print("::                                ::", YELLOW);
            print("====================================", CYAN);

            print("::                                ::", YELLOW);
            printnoendl("::", YELLOW);cout << "  [" << (choice == 1 ? ">" : " ") << "] ABJAD A - Z               ";print("::",YELLOW);
            printnoendl("::", YELLOW);cout << "  [" << (choice == 2 ? ">" : " ") << "] ABJAD Z - A               ";print("::",YELLOW);
            printnoendl("::", YELLOW);cout << "  [" << (choice == 3 ? ">" : " ") << "] KEMBALI                   ";print("::",YELLOW);
            print("::                                ::", YELLOW);
            print("====================================", CYAN);


            int input = _getch();
            if (input == 72) { // Tombol panah atas
                choice = (choice == 1) ? 3 : choice - 1;
            } else if (input == 80) { // Tombol panah bawah
                choice = (choice == 3) ? 1 : choice + 1;
            } else if (input == 13) { // Tombol Enter
                if (choice == 1) {
                    insertionsortKategori(databarang,ukuran);
                    tampilkanhasilsorting(databarang, ukuran);
                    system("pause");
                } else if (choice == 2) {
                    insertionsortKategori(databarang,ukuran);
                    reverseArray(databarang, ukuran);
                    tampilkanhasilsorting(databarang, ukuran);
                    system("pause");
                } else if (choice == 3) {
                    return;
                }
            }
        }

    }
}

void sort() {
    cekcsv("data.csv");
    int pilihan = 1; 
    while (true) {
        system("cls");
        print("====================================", CYAN);
        print("::                                ::", YELLOW);
        printnoendl("::", YELLOW); cout << "         PILIH TIPE SORT        "; print("::", YELLOW);
        print("::                                ::", YELLOW);
        print("====================================", CYAN);
        print("::                                ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 1 ? ">" : " ") << "] BERDASARKAN NAMA          "; print("::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 2 ? ">" : " ") << "] BERDASARKAN JUMLAH        "; print("::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 3 ? ">" : " ") << "] BERDASARKAN KATEGORI      "; print("::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 4 ? ">" : " ") << "] KEMBALI                   "; print("::", YELLOW);
        print("::                                ::", YELLOW);
        print("====================================", CYAN);


        int input = _getch();
        if (input == 72) { // Tombol panah atas
            if (pilihan > 1) {
                pilihan--;
            }
        } else if (input == 80) { // Tombol panah bawah
            if (pilihan < 4) {
                pilihan++;
            }
        } else if (input == 13) { // Tombol Enter
            if (pilihan == 4) { // Kembali
                return;
            } else {
                tipesort(pilihan); // Panggil fungsi yang sesuai dengan pilihan
            }
        }
    }
}

string search(){
    int panjangData = length();
    string nama,input;
    char charactertemp;
    int index = 0;
    barang Barang[panjangData];
    ifstream data("data.csv");
    if (!data.is_open()){
        cout << "File tidak ditemukan" << endl;
    }
    while(!data.eof() && index < panjangData ){
        getline(data,Barang[index].nama,',');
        if (Barang[index].nama.empty()){
            break;
        }
        data >> Barang[index].jumlah;
        data.ignore(1);
        data >> Barang[index].harga;
        data.ignore(1);
        getline(data, Barang[index].waktu, ',');
        data >> Barang[index].pointmasuk;
        data.ignore(1);
        data >> Barang[index].pointkeluar;
        data.ignore(1);
        getline(data, Barang[index].kategori, '\n');
        index ++;
    }
    Data.close();
    ulang:
    while(true){
        cout << "Masukkan nama barang yang ingin dicari : " << nama;
        charactertemp = getch();
        cout << endl;
        system("cls");
        if (charactertemp == '\r'||charactertemp == '\n'){
            break;
        }
        if (charactertemp == '\b'){
            bool found = false;
            if(!nama.empty()){
                nama.pop_back();
                cout << "\b \b";
            }
            for (int i = 0; i < index; i++){
                if (Barang[i].nama.substr(0, nama.length()) == nama){
                    found = true;
                }
            }
            if (!nama.empty() && found == true) {
                print("===========================================================================================================================================================", GREEN);
                print("| NO |      Nama Barang      | Jumlah Barang | Harga Barang |        Waktu Input        |  Point Di Dapat  | Harga Point |            Kategori            |", GREEN);
                print("===========================================================================================================================================================", GREEN);

                for (int p = 0; p < index; p++) {
                    if (Barang[p].nama.substr(0, nama.length()) == nama) {
                        printnoendl("| ", GREEN); cout << setw(2) << p + 1 ;printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(21) << Barang[p].nama; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(13) << Barang[p].jumlah; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(12) << fixed << setprecision(2) << Barang[p].harga; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(12) << Barang[p].waktu; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(16) << Barang[p].pointmasuk; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(11) << Barang[p].pointkeluar; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(30) << Barang[p].kategori; printnoendl(" |", GREEN);
                        cout << endl;
                        found = true;
                    }
                }

                print("===========================================================================================================================================================", GREEN);
            } else {
                print("============================", GREEN);
                printnoendl("::", YELLOW); cout << "  Data Tidak Ditemukan  "; print("::", YELLOW);
                print("============================", GREEN);
            }
            
        }else{
            nama.push_back(charactertemp);
            bool found = false;
            for(int p = 0;p < index; p++){
                if(Barang[p].nama.substr(0, nama.length()) == nama){
                    found = true;

                }
            }
            if (!nama.empty() && found == true) {
                print("===========================================================================================================================================================", GREEN);
                print("| NO |      Nama Barang      | Jumlah Barang | Harga Barang |        Waktu Input        |  Point Di Dapat  | Harga Point |            Kategori            |", GREEN);
                print("===========================================================================================================================================================", GREEN);

                for (int p = 0; p < index; p++) {
                    if (Barang[p].nama.substr(0, nama.length()) == nama) {
                        printnoendl("| ", GREEN); cout << setw(2) << p + 1 ;printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(21) << Barang[p].nama; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(13) << Barang[p].jumlah; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(12) << fixed << setprecision(2) << Barang[p].harga; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(12) << Barang[p].waktu; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(16) << Barang[p].pointmasuk; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(11) << Barang[p].pointkeluar; printnoendl(" | ", GREEN);
                        printnoendl("", GREEN); cout << setw(30) << Barang[p].kategori; printnoendl(" |", GREEN);
                        cout << endl;
                        found = true;
                    }
                }

                print("===========================================================================================================================================================", GREEN);
            } else {
                print("============================", GREEN);
                printnoendl("::", YELLOW); cout << "  Data Tidak Ditemukan  "; print("::", YELLOW);
                print("============================", GREEN);
            }
        }

    }
    int ind = 0;
    bool pencarian = false;
    for(int i = 0; i < index; i++){
        if(nama == Barang[i].nama){
            ind = i+1;
            pencarian = true;
        }
    }
    if (pencarian == true){

        hapusatauubah(nama,ind);
    }else{
        print("Masukkan Nama Barang Dengan Lengkap",RED);
        goto ulang;
    }

}

void historyadmin(){
    ifstream Data("riwayatpembelian.csv");
    history member;
    bool found = false;
    print("==========================================================================================================================",GREEN);
    print("| Nama Pembeli |     Tanggal Pembelian    |       Nama Barang      |  Jumlah Harga  | Jumlah Barang |  Jenis Pembayaran  |" , GREEN);
    print("==========================================================================================================================",GREEN);
    string previd;
    string prevdate;
    int i=0;
    int panjang = length_riwayat();

    while(true){
        getline(Data, member.id, ',');
        if(member.id.empty()){
            break;
        }
        getline(Data, member.nama, ',');
        string harga_str;
        getline(Data, harga_str, ',');
        member.harga = stoi(harga_str);
        getline(Data, member.pembayaran, ',');
        string jumlah_str;
        getline(Data, jumlah_str, ',');
        member.jumlah = stoi(jumlah_str);
        getline(Data, member.tanggal);
        if (member.id == previd && member.tanggal == prevdate){
            printnoendl("|              ",GREEN);
            printnoendl("|                          ",GREEN);
        }else{
            printnoendl("| ",GREEN) ;cout << setw(12) << member.id<< " ";
            printnoendl("| ",GREEN); cout << setw(22) << member.tanggal << " ";
        }
        
        printnoendl("| ",GREEN); cout << setw(23) << member.nama;printnoendl("| ",GREEN);
        cout << setw(15) << member.harga; printnoendl("|  ",GREEN);
        cout << setw(13) << member.jumlah; printnoendl("|  ",GREEN); 
        cout << setw(18) << member.pembayaran; printnoendl("|  ",GREEN); cout << endl;
        prevdate = member.tanggal;
        previd = member.id;
    }
    print("==========================================================================================================================",GREEN);
    Data.close();
    system("pause");

    
}


void menuadmin(){
    adminmenu:
    system("cls");
    int pilihan = admin(0,7);
    enum fitur{CREATE = 0, READ, filter, SORT, SEARCH,HISTORY, EXIT};

    

    switch(pilihan){
        case CREATE:tambah();break;
        case READ:system("cls");tampil();system("pause");break;
        case filter:filteringkategori();break;
        case SORT:sort();break;
        case SEARCH:search();system("pause");break;
        case HISTORY:historyadmin();break;
        case EXIT:menu();break;
        
    }
    goto adminmenu;
    
}

void daftarmember() {
    cekcsv("pengguna.csv");
    system("cls");
    ofstream PenggunaFile;
    Pengguna pengguna;
    bool idSama = false;

    print("============================",CYAN);
    printnoendl("::", YELLOW);cout << "      REGISTRASI        "; print("::",YELLOW);
    print("============================",CYAN);

    cout << endl;
    pengguna.id = inputString("Masukkan ID : ", false);
    bool showPassword = false;
    string password;
    cout << "Tekan Arrow Atas Untuk Melihat Password" << endl;
    char pw;

    do {
        password.clear();
        cout << "Masukkan Password: ";

        while ((pw = _getch()) != '\r') {
            if (pw == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            } else if (pw == 0 || pw == 224 || pw == -32) {
                pw = _getch();
                if (pw == 72) {
                    showPassword = !showPassword;
                    cout << "\rMasukkan Password: ";
                    if (showPassword) {
                        cout << password;
                    } else {
                        for (char ch : password) {
                            cout << "*";
                        }
                    }
                } else {
                    cout << "\a";
                }
            } else if (pw == ' ') {
                cout << "\a";
            } else {
                if (isprint(pw)) {
                    password.push_back(pw);
                    if (showPassword) {
                        cout << pw;
                    } else {
                        cout << "*";
                    }
                } else {
                    cout << "\a";
                }
            }
        }
        cout << endl;

        if (!cekpassword(password)) {
            cout << "Password tidak boleh kosong. Silakan coba lagi.\n";
        }
    } while (!cekpassword(password));



    // cout << "Masukkan Password : ";

    // char pw;    
    // while((pw = getch()) != '\r'){
    //     if (pw == '\b'){
    //         if(!password.empty()){
    //             password.pop_back();
    //             cout << "\b \b";
    //         }
    //     }else if(pw == 0 || pw == 224 || pw == -32){

    //         pw = _getch();
    //         if(pw == 72){
    //             showPassword = !showPassword;
    //             cout << "\rMasukkan Password : ";
    //             if (showPassword) {
    //                 cout << password;
    //             } else {
    //                 for (int i = 0; i < password.length(); ++i) {
    //                     cout << "*";
    //                 }
    //             }
    //         }
    //     }else{
    //         password.push_back(pw);
    //         if (showPassword) {
    //             cout << pw;
    //         } else {
    //             cout << "*";
    //         }
    //     }
    // }
    cout << endl;
    pengguna.password = password;
    pengguna.point = 0;

    cout << endl;
    print("============================",CYAN);

    cout << endl;
    
    ifstream file("pengguna.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, password;
        getline(ss, id, ',');
        getline(ss, password, ',');
        if (id == pengguna.id) {
            idSama = true;
            break;
        }
    }
    if (idSama) {
        print("Registrasi gagal! ID telah digunakan oleh pengguna lain.", RED);

        system("pause");
        daftarmember();
    } else {
        
        PenggunaFile.open("pengguna.csv", ios::app);
        PenggunaFile << pengguna.id << "," << pengguna.password << "," << pengguna.point  << endl;
        PenggunaFile.close();
        print("Registrasi berhasil!!!", GREEN);
        print("Lanjutkan dengan Login!!!", GREEN);
    }
    cout << endl;
    print("============================",CYAN);

    system("pause");
    menu(); 
}

void loginadmin(){
    int coba = 0;
    loginadmin:
    system("cls");
    if (coba == 0){

        print("==============================================", CYAN);
        print("::                                          ::", YELLOW);
        printnoendl("::",YELLOW),cout << " [Silahkan Masukkan ID dan Password Anda] ";print("::", YELLOW);
        print("::                                          ::", YELLOW);
        print("==============================================", CYAN);

    }else if (coba > 0 && coba < 4){
        print("==============================================", CYAN);
        print("::                                          ::", YELLOW);
        printnoendl("::",YELLOW);printnoendl("   [Warning ID dan Password Anda Salah]   ",RED);print("::", YELLOW);
        printnoendl("::",YELLOW);printnoendl("  [Percobaan Tidak Boleh Lebih Dari 3x ]  ",RED);print("::", YELLOW);
        printnoendl("::",YELLOW);printnoendl("          [Percobaan Ke-",RED); cout<< coba; printnoendl(" Gagal]          ",RED);print("::", YELLOW);

        print("::                                          ::", YELLOW);
        print("==============================================", CYAN);
    }else if (coba == 4){
        print("=============================================", CYAN);
        print("::                                         ::", YELLOW);
        printnoendl("::",YELLOW);printnoendl("      [Silahkan Coba Lagi Nanti!!!]      ",RED);print("::", YELLOW);
        print("::                                         ::", YELLOW);
        print("=============================================", CYAN);
        exit(1);

    }

    cout << endl;
    cout << endl;

    bool showPassword = false;
    string id = inputString("Masukkan ID : ", true), password;
    cout << "Tekan Arrow Atas Untuk Melihat Password" << endl;
    cout << "Masukkan Password : ";
    char pw;    
    while((pw = getch()) != '\r'){
        if (pw == '\b'){
            if(!password.empty()){
                password.pop_back();
                cout << "\b \b";
            }
        }else if(pw == 0 || pw == 224 || pw == -32){

            pw = _getch();
            if(pw == 72){
                showPassword = !showPassword;
                cout << "\rMasukkan Password : ";
                if (showPassword) {
                    cout << password;
                } else {
                    for (int i = 0; i < password.length(); ++i) {
                        cout << "*";
                    }
                }
            }
        }else{
            password.push_back(pw);
            if (showPassword) {
                cout << pw;
            } else {
                cout << "*";
            }
        }
    }

    if(id == "admin" && password == "admin"){
        
        menuadmin();
    }else {
        coba ++;
    }
    goto loginadmin;

}

int point(string id, string password){
    
    int panjangData = length_user();
    Pengguna member[1000];
    int i = 0;
    
    Data.open("pengguna.csv", ios::in);
    while (!Data.eof() && i < 1000) {
        getline(Data, member[i].id, ','); 
        if (member[i].id.empty()) {
            break;
        }
        getline(Data, member[i].password, ','); 
        if (member[i].password.empty()) {
            break;
        }
        Data >> member[i].point;  
        Data.ignore(1); 
        i++;  
    }
    Data.close();
    int point;

    int j;
    for (j = 0;j < panjangData; ++j){

        if (id == member[j].id && password == member[j].password){
            
            return member[j].point;
            break;
            }

        }
}

void menuusermember(string id, string password){

    menu:
    int p = point(id, password); 
    int pilihan = 0;
    int item = 4;
    while(true){
        system("cls");
        
        print("============================", CYAN);
        print("::                        ::", YELLOW);
        printnoendl("::", YELLOW); cout << "      Shopping Mart     "; print("::", YELLOW);
        print("::                        ::", YELLOW);
        print("============================", CYAN);
        cout << ">> ID    : " << id << endl;
        cout << ">> POINT : " << p << endl;
        print("============================", CYAN);

        // Pilihan menu
        print("::                        ::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 0 ? ">" : " ") << "] Beli Barang       "; print("::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 1 ? ">" : " ") << "] Lihat History     "; print("::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 2 ? ">" : " ") << "] Ubah Password     "; print("::", YELLOW);
        printnoendl("::", YELLOW); cout << "  [" << (pilihan == 3 ? ">" : " ") << "] Kembali           "; print("::", YELLOW);
        print("::                        ::", YELLOW);
        print("============================", CYAN);

        int input = _getch();
            if (input == 72) {
                if (pilihan > 0) {
                    pilihan--;
                }
            } else if (input == 80) {
                if (pilihan < item - 1) {
                    pilihan++;
                }
            } else if (input == 13) {
                
                break; 
            }
    }
    enum fitur{BELI = 0, LIHAT_HISTORY, UBAH_PASSWORD, EXIT};

    switch(pilihan){
        case BELI:belibarang(id);goto menu;break;
        case LIHAT_HISTORY:system("cls");history_member(id);goto menu;break;
        case UBAH_PASSWORD:ubahPassword(id,password);break;
        case EXIT:menu();break;
        default:cout << "Anda Salah Input" << endl;break;
    }
}

void history_member(string id) {
    cekcsv("riwayatpembelian.csv");
    ifstream Data("riwayatpembelian.csv");
    if (!Data.is_open()) {
        cerr << "Error: File tidak bisa dibuka!" << endl;
        return;
    }
    history member;
    bool found = false;

    print("===========================================================================================================", GREEN);
    print("|     Tanggal Pembelian    |       Nama Barang      |  Jumlah Harga  | Jumlah Barang |  Jenis Pembayaran  |" , GREEN);
    print("===========================================================================================================", GREEN);

    // Variabel untuk menyimpan tanggal sebelumnya
    string previous_date;

    // Membaca data dari file CSV
    while (Data.good()) {
        getline(Data, member.id, ',');
        if (member.id.empty()) {
            // Jika ID kosong, lewati baris ini
            getline(Data, member.nama, ','); // Mengabaikan nilai nama
            getline(Data, member.pembayaran, ','); // Mengabaikan nilai pembayaran
            string temp; // Temporary variable untuk menampung nilai harga dan jumlah
            getline(Data, temp, '\n'); // Mengabaikan nilai harga, jumlah, dan tanggal
            continue;
        }
        
        getline(Data, member.nama, ',');
        string harga_str;
        getline(Data, harga_str, ',');
        
        member.harga = stoi(harga_str);
        getline(Data, member.pembayaran, ',');
        string jumlah_str;
        getline(Data, jumlah_str, ',');
        member.jumlah = stoi(jumlah_str);
        getline(Data, member.tanggal);

        // Mengecek apakah ID yang dibaca sama dengan ID yang diberikan sebagai parameter
        if (member.id == id) {
            found = true;
            // Memastikan tanggal saat ini tidak sama dengan tanggal sebelumnya
            if (member.tanggal != previous_date) {
                printnoendl("| ",GREEN); cout << setw(22) << member.tanggal << " ";
            } else {
                printnoendl("|                          ",GREEN);
            }

            printnoendl("| ",GREEN);cout << setw(22) << member.nama;printnoendl(" | ",GREEN);
            cout << setw(14) << member.harga;printnoendl(" | ",GREEN);
            cout << setw(13) << member.jumlah;printnoendl(" | ",GREEN);
            cout << setw(19) << member.pembayaran; printnoendl("|  ",GREEN); cout << endl;
            // Perbarui tanggal sebelumnya
            previous_date = member.tanggal;
        }
    }

    if (!found) {
        print("Tidak ada data pembelian.",RED); 
    }

    print("===========================================================================================================", GREEN);
    Data.close();
    system("pause");
}

void ubahPassword(string id, string password){

    int panjangData = length_user();
    Pengguna member[panjangData];
    int i = 0;
    
    Data.open("pengguna.csv", ios::in);
    while (!Data.eof() && i < panjangData) {
        getline(Data, member[i].id, ','); 
        if (member[i].id.empty()) {
            break;
        }
        getline(Data, member[i].password, ','); 
        if (member[i].password.empty()) {
            break;
        }
        Data >> member[i].point;  
        Data.ignore(1); 
        i++;  
    }
    Data.close();

    int j;
    for (j = 0;j < panjangData; ++j){

        if (id == member[j].id && password == member[j].password){
            bool showPassword = false;
            string password;
            cout << "Tekan Arrow Atas Untuk Melihat Password" << endl;
            char pw;

            do {
                password.clear();
                cout << "Masukkan Password: ";

                while ((pw = _getch()) != '\r') {
                    if (pw == '\b') {
                        if (!password.empty()) {
                            password.pop_back();
                            cout << "\b \b";
                        }
                    } else if (pw == 0 || pw == 224 || pw == -32) {
                        pw = _getch();
                        if (pw == 72) {
                            showPassword = !showPassword;
                            cout << "\rMasukkan Password: ";
                            if (showPassword) {
                                cout << password;
                            } else {
                                for (char ch : password) {
                                    cout << "*";
                                }
                            }
                        } else {
                            cout << "\a";
                        }
                    } else if (pw == ' ') {
                        cout << "\a";
                    } else {
                        if (isprint(pw)) {
                            password.push_back(pw);
                            if (showPassword) {
                                cout << pw;
                            } else {
                                cout << "*";
                            }
                        } else {
                            cout << "\a";
                        }
                    }
                }
                cout << endl;

                if (!cekpassword(password)) {
                    cout << "Password tidak boleh kosong. Silakan coba lagi.\n";
                }
            } while (!cekpassword(password));

            member[j].password = password;
            print("Password telah diubah, Silakah Login Kembali",GREEN);
            system("pause");
            
            Data.open("pengguna.csv", ios::out | ios::trunc);
            for (int k = 0; k < i; k++) {
                Data << member[k].id << ","
                     << member[k].password << ","
                     << member[k].point << endl;
            }
            Data.close();
            break;
            }

        }
}

void loginmember() {
    cekcsv("pengguna.csv");
    int coba = 0;
    Pengguna pengguna;
    while (true) {
        system("cls");

        if (coba == 0) {
            print("=============================================", CYAN);
            print("::                                          ::", YELLOW);
            printnoendl("::",YELLOW),cout << " [Silahkan Masukkan ID dan Password Anda] ";print("::", YELLOW);
            print("::                                          ::", YELLOW);
            print("=============================================", CYAN);
        } else if (coba > 0 && coba < 4) {
            print("==============================================", CYAN);
            print("::                                          ::", YELLOW);
            printnoendl("::",YELLOW);printnoendl("   [Warning ID dan Password Anda Salah]   ",RED);print("::", YELLOW);
            printnoendl("::",YELLOW);printnoendl("  [Percobaan Tidak Boleh Lebih Dari 3x ]  ",RED);print("::", YELLOW);
            printnoendl("::",YELLOW);printnoendl("          [Percobaan Ke-",RED); cout<< coba; printnoendl(" Gagal]          ",RED);print("::", YELLOW);

            print("::                                          ::", YELLOW);
            print("==============================================", CYAN);
        } else if (coba == 4) {
            print("=============================================", CYAN);
            print("::                                         ::", YELLOW);
            printnoendl("::",YELLOW);printnoendl("      [Silahkan Coba Lagi Nanti!!!]      ",RED);print("::", YELLOW);
            print("::                                         ::", YELLOW);
            print("=============================================", CYAN);
            system("pause");
            daftarmember();
            return;
        }


        cout << endl;
        cout << endl;
        string id = inputString("Masukkan ID : ", true);
        bool showPassword = false;
        string password;
        cout << "Tekan Arrow Atas Untuk Melihat Password" << endl;
        char pw;
        do {
            password.clear();
            cout << "Masukkan Password: ";

            while ((pw = _getch()) != '\r') {
                if (pw == '\b') {
                    if (!password.empty()) {
                        password.pop_back();
                        cout << "\b \b";
                    }
                } else if (pw == 0 || pw == 224 || pw == -32) {
                    pw = _getch();
                    if (pw == 72) {
                        showPassword = !showPassword;
                        cout << "\rMasukkan Password: ";
                        if (showPassword) {
                            cout << password;
                        } else {
                            for (char ch : password) {
                                cout << "*";
                            }
                        }
                    } else {
                        cout << "\a";
                    }
                } else if (pw == ' ') {
                    cout << "\a";
                } else {
                    if (isprint(pw)) {
                        password.push_back(pw);
                        if (showPassword) {
                            cout << pw;
                        } else {
                            cout << "*";
                        }
                    } else {
                        cout << "\a";
                    }
                }
            }
            cout << endl;

            if (!cekpassword(password)) {
                cout << "Password tidak boleh kosong. Silakan coba lagi.\n";
            }
        } while (!cekpassword(password));
        ifstream file("pengguna.csv");

        bool bisalogin = false;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, pengguna.id, ',');
            getline(ss, pengguna.password, ',');
            if (pengguna.id == id && pengguna.password == password) {
                bisalogin = true;
                break;
            }
        }
        file.close();
        if (bisalogin) {
            cout << "Login berhasil" << endl;
            menuusermember(id, password);
            return;
        } else {
            cout << "Login gagal" << endl;
            coba++;
        }
    }
}

// Perbaikan kode void belibarang() dengan fokus pada case KERANJANG
void belibarang(string id) {
    cekcsv("data.csv");
    int point = 0;
    int datak = 0;
    int panjangData = 0;
    int panjangdatabarang = length();
    int panjangkeranjang = length_riwayat();
    struct tempbarang{
        string nama;
        int jumlah;
        int harga;
        string waktu;
        int pointmasuk;
        int pointkeluar;
        string kategori;
    };
    struct Keranjangs {
        string nama;
        int harga;
        int jumlah;
        
    };
    Keranjangs keranjang[panjangkeranjang];
    tempbarang Barang[panjangdatabarang];
    
    ifstream data("data.csv");

    while (!data.eof() && panjangData < panjangdatabarang) {
        getline(data, Barang[panjangData].nama, ',');
        if (Barang[panjangData].nama.empty()) {
            break;
        }
        data >> Barang[panjangData].jumlah;
        data.ignore(1);
        data >> Barang[panjangData].harga;
        data.ignore(1);
        getline(data, Barang[panjangData].waktu, ',');
        data >> Barang[panjangData].pointmasuk;
        data.ignore(1);
        data >> Barang[panjangData].pointkeluar;
        data.ignore(1);
        getline(data, Barang[panjangData].kategori, '\n');
        panjangData++;
    }
    Data.close();
    ulang:
    enum Pilihan {CARI = 0, KERANJANG, KATEGORI, PEMBAYARAN, CANCEL};
    int pilihan = menubeli(0, 5);

    
    switch (pilihan) {
        case CARI: {
            string nama,input;
            char charactertemp;
            while (true){
                cout << "Masukkan Nama Yang ingin Di Cari : " << nama;
                charactertemp = getch();
                cout << endl;
                system("Cls");
                if (charactertemp == '\r'||charactertemp == '\n'){
                    break;
                }
                if (charactertemp == '\b'){
                    bool found = false;
                    if(!nama.empty()){
                        nama.pop_back();
                        cout << "\b \b";
                    }
                    for(int p = 0;p < panjangData; p++){
                        if(Barang[p].nama.substr(0, nama.length()) == nama){
                            found = true;

                        }
                    }
                    
                    
                    if(!nama.empty() && found == true){
                        
                        print("=================================================================================================================", GREEN);
                        print("| NO |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("=================================================================================================================", GREEN);
                        for(int p = 0;p < panjangData; p++){
                            if(Barang[p].nama.substr(0, nama.length()) == nama){
                                printnoendl("| ",GREEN);
                                cout<< setw(2) << p+1;printnoendl(" | ",GREEN);cout << setw(21) << Barang[p].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[p].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[p].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[p].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[p].pointkeluar; print(" |",GREEN);
                                found = true;
                            }
                        }
                        print("=================================================================================================================", GREEN);
                    }
                    else{
                        print("============================",CYAN);
                        printnoendl("::",YELLOW);cout << "  Data Tidak Ditemukan  ";print("::",YELLOW);
                        print("============================",CYAN);
                    }
                }else{
                    nama.push_back(charactertemp);
                    
                    bool found = false;
                    for(int p = 0;p < panjangData; p++){
                        if(Barang[p].nama.substr(0, nama.length()) == nama){
                            found = true;

                        }
                    }
                    if(found == true){
                        
                        print("=================================================================================================================", GREEN);
                        print("| NO |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("=================================================================================================================", GREEN);
                        for(int p = 0;p < panjangData; p++){
                            if(Barang[p].nama.substr(0, nama.length()) == nama){
                                printnoendl("| ",GREEN);
                                cout<< setw(2) << p+1;printnoendl(" | ",GREEN);cout << setw(21) << Barang[p].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[p].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[p].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[p].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[p].pointkeluar; print(" |",GREEN);
                                found = true;
                            }
                        }
                        print("=================================================================================================================", GREEN);
                    }
                    else{
                        print("============================",CYAN);
                        printnoendl("::",YELLOW);cout << "  Data Tidak Ditemukan  ";print("::",YELLOW);
                        print("============================",CYAN);
                    }
                }

            }
            bool cari = false;
            for (int j = 0; j < panjangData; j++) {
                if (nama == Barang[j].nama) {
                    cari = true;
                }

            }
            if (cari == true){
                int pilihanBeli = pilihb(0, 2);
                enum Menu {Y = 0, T};
                switch (pilihanBeli) {
                    case Y: {
                        int jumlah = beli(0, 999);
                        bool ditemukan = false;
                        for (int j = 0; j < panjangData; j++) {
                            if (nama == Barang[j].nama) {
                                ditemukan = true;
                                if (jumlah+1 > Barang[j].jumlah) {
                                    print("===================================================================",CYAN);
                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print(" ::",YELLOW);
                                    print("===================================================================",CYAN);
                                    system("pause");
                                    goto ulang;
                                } else {
                                    bool found = false;
                                    int size = sizeof(keranjang)/sizeof(keranjang[0]);
                                    for(int p = 0; p < size;p++){
                                        if (nama == keranjang[p].nama){
                                            int jumlahr = jumlah +1;
                                            int hargat = jumlahr * Barang[j].harga;
                                            keranjang[p].harga += hargat;
                                            keranjang[p].jumlah += jumlahr;
                                            found = true;
                                            Barang[j].jumlah -= jumlahr;
                                            if(id != "-"){
                                               point += Barang[j].pointmasuk*jumlahr; 
                                            }
                                          
                                        }
                                    }
                                    if (found == false){
                                        int jumlahr = jumlah + 1;
                                        Keranjangs temp;
                                        Barang[j].jumlah -= jumlahr;
                                        temp.nama = Barang[j].nama;
                                        temp.harga = Barang[j].harga * jumlahr;
                                        temp.jumlah = jumlahr;
                                        
                                       
                                        keranjang[datak] = temp; 
                                        if(id != "-"){
                                           point += Barang[j].pointmasuk*jumlahr; 
                                        }
                                        datak++;
                                    }


                                }
                                system("pause");
                                goto ulang;
                                break;
                            }
                      
                        }
                    }
                    case T: 
                    goto ulang;
                    break;
                }    

            }   
            else{
                print("=================================================",CYAN);
                printnoendl("::",YELLOW);cout << "            Barang tidak ditemukan           ";print("::",YELLOW);
                printnoendl("::",YELLOW);cout << "  Mohon Masukkan Nama Barang Dengan Lengkap  ";print("::",YELLOW);
                print("=================================================",CYAN);
                system("pause");
                goto ulang;
                break;
            }
            
        }
        case KERANJANG: {
            if (datak == 0) {
                cout << "==============================" << endl;
                cout << "::  Barang tidak ditemukan  ::" << endl;
                cout << "==============================" << endl;
                system("pause");
                goto ulang;
                break;

            }
            print("=====================================================================================================", GREEN);
            print("| NO |      Nama Barang      | Jumlah Barang | Harga Barang |   Point Di Dapat  | Beli Dengan Point |", GREEN);
            print("=====================================================================================================", GREEN);
            for (int k = 0; k < datak; k++) {
                printnoendl("| ",GREEN);cout<< setw(2) << k+1;printnoendl(" | ",GREEN);
                 cout << setw(21) << keranjang[k].nama ;printnoendl(" | ",GREEN);
                 cout << setw(12) << keranjang[k].jumlah;printnoendl(" | ",GREEN);
                 cout << setw(12) << keranjang[k].harga;printnoendl(" | ",GREEN);
                for(int l = 0; l < panjangData; l++){
                    if(keranjang[k].nama == Barang[l].nama){
                        cout << setw(18) << Barang[l].pointmasuk*keranjang[k].jumlah;printnoendl(" |",GREEN); 
                        cout << setw(18) << Barang[l].pointkeluar*keranjang[k].jumlah; print(" |",GREEN);  

                    }
                }
            }
            int totals = 0;
            for(int k = 0; k < datak; k++){
                totals += keranjang[k].harga;
            }
            print("=====================================================================================================", GREEN);
            
            cout << endl;
            print("============================", GREEN);
            printnoendl("| Total Harga :" , GREEN); cout << setw(12) << totals; print("|", GREEN);
            print("============================", GREEN);
            
        }
        system("pause");
        goto ulang;
        break;
        case KATEGORI:{
            enum kategori{makanan = 0, minuman, mainan, bahanpokok, pengharum, kebersihan, pakaian, sekolah, rumah, lainlain};
            int pilihkategori = kategorimenu(0,10);
            switch (pilihkategori){ 
                case makanan:{

                    bool kategori = false;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData; i++){
                        if(Barang[i].kategori == " Makanan" or Barang[i].kategori == "Makanan"){
                            kategori = true;
                        }
                    }
                    if(kategori == false){
                        print("===================================================", CYAN);
                        printnoendl("::", YELLOW);cout << "     Barang Dengan Kategori Makanan kosong     ";print("::", YELLOW);
                        print("===================================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");

                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == " Makanan" or Barang[z].kategori == "Makanan") {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);  

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }

                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {
                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    int size = sizeof(keranjang)/sizeof(keranjang[0]);
                                                    for(int p = 0; p < size ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                               point += Barang[j].pointmasuk*jumlahr; 
                                                            }
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
                                                        
                                                        keranjang[datak] = temp; 
                                                        datak++;
                                                        if(id != "-"){
                                                           point += Barang[j].pointmasuk*jumlahr; 
                                                        }
                                                        
                                                    }


                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        
                                        }
                                    }
                                    break;
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
                }
                case minuman:{
                    bool kategori = false ;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData;i++){
                        if(Barang[i].kategori==" Minuman" or Barang[i].kategori== "Minuman"){
                            kategori = true;

                        }
                    }
                    if(kategori == false){
                        print("===================================================", CYAN);
                        printnoendl("::", YELLOW); cout << "     Barang Dengan Kategori Minuman kosong     ";print("::", YELLOW);
                        print("===================================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");

                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == " Minuman" or Barang[z].kategori == "Minuman") {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);  

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }
                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {

                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
    
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    for(int p = 0; p < datak ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                               point += Barang[j].pointmasuk*jumlahr; 
                                                            }
                                                            
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
                                                        
                                                        keranjang[datak] = temp; 
                                                        datak++;
                                                        if(id != "-"){
                                                           point += Barang[j].pointmasuk*jumlahr; 
                                                        }
                                                    }


                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        
                                        }
                                    }
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
            
                }
                case mainan:{
                    bool kategori = false;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData; i++){
                        if(Barang[i].kategori == " Mainan" or Barang[i].kategori == "Mainan"){
                            kategori = true;
                        }
                    }
                    if(kategori == false){
                        print("====================================================", CYAN);
                        printnoendl("::", YELLOW); cout << "      Barang Dengan Kategori Mainan kosong      "; print("::", YELLOW);
                        print("====================================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");

                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == " Mainan" or Barang[z].kategori == "Mainan") {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);  

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }

                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {
                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    int size = sizeof(keranjang)/sizeof(keranjang[0]);
                                                    for(int p = 0; p < datak ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                               point += Barang[j].pointmasuk*jumlahr; 
                                                            }
                                                            
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
                                                        
                                                        keranjang[datak] = temp; 
                                                        datak++;
                                                        if(id != "-"){
                                                           point += Barang[j].pointmasuk*jumlahr; 
                                                        }
                                                    }


                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        
                                        }
                                    }
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
                }
                case bahanpokok:{
                    bool kategori = false;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData; i++){
                        if(Barang[i].kategori == " Bahan Pokok" or Barang[i].kategori == "Bahan Pokok"){
                            kategori = true;
                        }
                    }
                    if(kategori == false){
                        print("===================================================", CYAN);
                        printnoendl("::", YELLOW); cout << "   Barang Dengan Kategori Bahan Pokok kosong   "; print("::", YELLOW);
                        print("===================================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");

                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == " Bahan Pokok" or Barang[z].kategori == "Bahan Pokok") {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);  

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }

                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {
                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    int size = sizeof(keranjang)/sizeof(keranjang[0]);
                                                    for(int p = 0; p < datak ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                               point += Barang[j].pointmasuk*jumlahr; 
                                                            }
                                                            
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
                                                        
                                                        keranjang[datak] = temp; 
                                                        datak++;
                                                        if(id != "-"){
                                                           point += Barang[j].pointmasuk*jumlahr; 
                                                        }
                                                    }


                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        
                                        }
                                    }
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
                }
                case pengharum:{
                    bool kategori = false;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData; i++){
                        if(Barang[i].kategori == " Pengharum" or Barang[i].kategori == "Pengharum"){
                            kategori = true;
                        }
                    }
                    if(kategori == false){
                        print("===================================================", CYAN);
                        printnoendl("::", YELLOW); cout << "    Barang Dengan Kategori Pengharum kosong    "; print("::", YELLOW);
                        print("===================================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");

                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == " Pengharum" or Barang[z].kategori == "Pengharum") {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);  

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }

                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {
                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    for(int p = 0; p < datak ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                               point += Barang[j].pointmasuk*jumlahr; 
                                                            }
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
        
                                                        keranjang[datak] = temp; 
                                                        datak++;
                                                        if(id != "-"){
                                                           point += Barang[j].pointmasuk*jumlahr; 
                                                        }
                                                    }


                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        
                                        }
                                    }
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
                
                }
                case kebersihan:{
                                    bool kategori = false;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData; i++){
                        if(Barang[i].kategori == " Kebersihan" or Barang[i].kategori == "Kebersihan"){
                            kategori = true;
                        }
                    }
                    if(kategori == false){
                        print("====================================================", CYAN);
                        printnoendl("::", YELLOW); cout << "    Barang Dengan Kategori Kebersihan kosong    "; print("::", YELLOW);
                        print("====================================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");

                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == " Kebersihan" or Barang[z].kategori == "Kebersihan" ) {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);  

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }

                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {
                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    for(int p = 0; p < datak ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                               point += Barang[j].pointmasuk*jumlahr; 
                                                            }
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
                                                        
                                                        keranjang[datak] = temp; 
                                                        datak++;
                                                        if(id != "-"){
                                                           point += Barang[j].pointmasuk*jumlahr; 
                                                        }
                                                    }


                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        
                                        }
                                    }
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
                
                }
                case pakaian:{
                    bool kategori = false;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData; i++){
                        if(Barang[i].kategori == " Pakaian"  or Barang[i].kategori == "Pakaian" ){
                            kategori = true;
                        }
                    }
                    if(kategori == false){
                        print("===============================================", CYAN);
                        printnoendl("::", YELLOW); cout << "   Barang Dengan Kategori Pakaian kosong   "; print("::", YELLOW);
                        print("===============================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");

                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == " Pakaian" or Barang[z].kategori == "Pakaian") {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);  

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }

                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {
                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    for(int p = 0; p < datak ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                               point += Barang[j].pointmasuk*jumlahr; 
                                                            }
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
                                                        
                                                        keranjang[datak] = temp; 
                                                        datak++;
                                                        if(id != "-"){
                                                           point += Barang[j].pointmasuk*jumlahr; 
                                                        }
                                                    }


                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        
                                        }
                                    }
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
                                
                }
                case sekolah:{
                    bool kategori = false;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData; i++){
                        if(Barang[i].kategori == "Perlengkapan Sekolah" or Barang[i].kategori == " Perlengkapan Sekolah"){
                            kategori = true;
                        }
                    }
                    if(kategori == false){
                        print("================================================================", CYAN);
                        printnoendl("::", YELLOW); cout << "     Barang Dengan Kategori Perlengkapan Sekolah kosong     "; print("::", YELLOW);
                        print("================================================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");

                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == "Perlengkapan Sekolah" or Barang[z].kategori == " Perlengkapan Sekolah") {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);  

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }

                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {
                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    for(int p = 0; p < datak ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                               point += Barang[j].pointmasuk*jumlahr; 
                                                            }
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
                                                        
                                                        keranjang[datak] = temp; 
                                                        datak++;
                                                    }


                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        
                                        }
                                    }
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
                                
                }
                case rumah:{
                    bool kategori = false;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData; i++){
                        if(Barang[i].kategori == " Perlengkapan Rumah Tangga" or Barang[i].kategori == "Perlengkapan Rumah Tangga"){
                            kategori = true;
                        }
                    }
                    if(kategori == false){
                        print("=====================================================================", CYAN);
                        printnoendl("::", YELLOW); cout << "     Barang Dengan Kategori Perlengkapan Rumah Tangga kosong     "; print("::", YELLOW);
                        print("=====================================================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");

                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("=====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |          Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("=====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == " Perlengkapan Rumah Tangga" or Barang[z].kategori == "Perlengkapan Rumah Tangga") {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);   

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("=====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }

                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {
                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    for(int p = 0; p < datak ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                               point += Barang[j].pointmasuk*jumlahr; 
                                                            }
                                                            
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
                                                        
                                                        keranjang[datak] = temp; 
                                                        datak++;
                                                    }


                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        
                                        }
                                    }
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
                            
                }
                case lainlain:{
                    bool kategori = false;
                    int pilihankat = 0;
                    for(int i = 0; i < panjangData; i++){
                        if(Barang[i].kategori == " Lain-Lain" or Barang[i].kategori == "Lain-Lain"){
                            kategori = true;
                        }
                    }
                    if(kategori == false){
                        print("=====================================================", CYAN);
                        printnoendl("::", YELLOW); cout << "     Barang Dengan Kategori Lain-Lain kosong     "; print("::", YELLOW);
                        print("=====================================================", CYAN);
                        system("pause");
                        goto ulang;                    
                        break;
                    }
                    int input, var;
                    while (true) {
                        system("cls");
                        int count = 0;
                        int indeksTerpilih = -1; 
                        print("====================================================================================================================", GREEN);
                        print("| Pilih |      Nama Barang      | Harga Barang |         Kategori          |   Point Di Dapat  | Beli Dengan Point |", GREEN);
                        print("====================================================================================================================", GREEN);
                        for (int z = 0; z < panjangData; z++) {
                            if (Barang[z].kategori == " Lain-Lain" or Barang[z].kategori == "Lain-Lain") {
                                printnoendl("|   ",GREEN); cout << (pilihankat == count ? ">" : " "); printnoendl("   | " ,GREEN);
                                cout << setw(21) << Barang[z].nama ;printnoendl(" | ",GREEN);
                                cout<< setw(12) << Barang[z].harga;printnoendl(" | ",GREEN);
                                cout << setw(25) << Barang[z].kategori; printnoendl(" |",GREEN);
                                cout << setw(18) << Barang[z].pointmasuk;printnoendl(" |",GREEN); 
                                cout << setw(18) << Barang[z].pointkeluar; print(" |",GREEN);    

                    
                                if (pilihankat == count) {
                                    indeksTerpilih = z;
                                }
                                
                                count++;
                            }
                        }
                        print("====================================================================================================================", GREEN);
                        input = _getch();
                        if (input == 72) {  // Panah atas
                            if (pilihankat > 0) {
                                pilihankat--;
                            }
                        } else if (input == 80) {  // Panah bawah
                            if (pilihankat < count - 1) {
                                pilihankat++;
                            }
                        } else if (input == 13) {  // Enter
                            string nama =  Barang[indeksTerpilih].nama;
                            bool cari = false;
                            for (int j = 0; j < panjangData; j++) {
                                if (nama == Barang[j].nama) {
                                    cari = true;
                                }
                            }
                            if (cari == true){
                                int pilihanBeli = pilihb(0, 2);
                                enum Menu {Y = 0, T};
                                switch (pilihanBeli) {
                                    case Y: {
                                        int jumlah = beli(0, 999);
                                        bool ditemukan = false;
                                        for (int j = 0; j < panjangData; j++) {
                                            if (nama == Barang[j].nama) {
                                                ditemukan = true;
                                                if (jumlah+1 > Barang[j].jumlah) {
                                                    print("===================================================================",CYAN);
                                                    printnoendl("::",YELLOW); cout << "  Maaf, jumlah yang anda inginkan melebihi stok yang tersedia  ";print("::",YELLOW);
                                                    printnoendl("::",YELLOW); cout << "                     Stok yang tersedia: ";cout <<Barang[j].jumlah <<"                    "; print("::",YELLOW);
                                                    print("===================================================================",CYAN);
                                                    system("pause");
                                                    goto ulang;
                                                } else {
                                                    bool found = false;
                                                    for(int p = 0; p < datak ;p++){
                                                        if (nama == keranjang[p].nama){
                                                            int jumlahr = jumlah +1;
                                                            int hargat = jumlahr * Barang[j].harga;
                                                            keranjang[p].harga += hargat;
                                                            keranjang[p].jumlah += jumlahr;
                                                            found = true;
                                                            Barang[j].jumlah -= jumlahr;
                                                            if(id != "-"){
                                                                Barang[j].pointmasuk =+ point;
                                                            }
                                                        }
                                                    }
                                                    if (found == false){
                                                        int jumlahr = jumlah + 1;
                                                        Keranjangs temp;
                                                        Barang[j].jumlah -= jumlahr;
                                                        temp.nama = Barang[j].nama;
                                                        temp.harga = Barang[j].harga * jumlahr;
                                                        temp.jumlah = jumlahr;
                                                        
                                                        keranjang[datak] = temp;
                                                        if(id != "-"){
                                                            Barang[j].pointmasuk =+ point;
                                                        } 
                                                        datak++;
                                                    }
                                                }
                                                system("pause");
                                                goto ulang;
                                                break;
                                            }
                                        }
                                    }
                                    case T: goto ulang;break;
                                }    

                            }   
                            else{
                                print("==============================", CYAN);
                                printnoendl("::",YELLOW);cout << "  Barang tidak ditemukan  ";print("::",YELLOW);
                                print("==============================", CYAN);
                                goto ulang;
                                break;
                            }
                            break;
                        }
                    }
                    break;
                }  
            }
        }
        case PEMBAYARAN:{
            time_t now = time(nullptr);
            char* time = ctime(&now);
            string cleanTime(time);
            cleanTime.erase(cleanTime.find('\n'));
            int panjang = length_user();
            Pengguna member[panjang];
            
            ifstream files("pengguna.csv");
            int i=0;
            Data.open("pengguna.csv", ios::in);
            while(!files.eof()&& i < panjang){
                getline(files, member[i].id, ',');
                if (member[i].id.empty()){
                    break;
                }
                getline(files, member[i].password, ',');
                files >> member[i].point;
                files.ignore(1);
                i++;
            }
            Data.close();
            if(keranjang[0].nama.empty()){
                cout << "=========================================" << endl;
                cout << "::     Keranjang Anda Masih Kosong     ::" << endl;
                cout << "=========================================" << endl;
                system("pause");
                break;
            }
            if (id != "-"){
                belipake:
                int pilih = belipake(0,3);
                enum belipake{points=0,cash,back};
                switch(pilih){
                    case points:{
                        int jumlahharagco = 0;
                        for (int k = 0; k < datak; k++){
                            for(int l = 0; l < panjangData; l++){
                                if (keranjang[k].nama == Barang[l].nama){
                                    jumlahharagco += Barang[l].pointkeluar * keranjang[k].jumlah;

                                }

                            }
                        }
                        for(int j = 0; j < panjang; j++){
                            if (member[j].id == id){
                                if(member[j].point < jumlahharagco){
                                    cout << "===============================" << endl;
                                    cout << "::     Point tidak Cukup     ::" << endl;
                                    cout << "===============================" << endl;
                                    system("pause");
                                    goto belipake;
                                }
                                else{
                                   member[j].point -= jumlahharagco;
                                }
                            }
                        }
                        
                        Data.open("pengguna.csv", ios::out | ios::trunc);
                        for (int k = 0; k < i; k++){
                            Data << member[k].id << ","
                                << member[k].password << ","
                                << member[k].point << endl;
                        }
                        Data.open("data.csv", ios::out | ios::trunc);
                        for (int k = 0; k < panjangData; k++){
                            Data << Barang[k].nama << ","
                                << Barang[k].jumlah << ","
                                << Barang[k].harga << ","
                                << Barang[k].waktu << ","
                                << Barang[k].pointmasuk << ","
                                << Barang[k].pointkeluar << ","
                                << Barang[k].kategori<< endl;
                        }
                        Data.close();
                        
                        Data.open("riwayatpembelian.csv", ios::app);
                        for (int k = 0; k < datak; k++){

                            Data << id << ","
                                << keranjang[k].nama << ","
                                << keranjang[k].harga << ","
                                << "Point" << ","
                                << keranjang[k].jumlah << ","
                                << cleanTime << endl;
                        }
                        Data.close();
                        break;
                    }
                    case cash:{
                        for(int k=0;k<panjang; k++){
                            if(member[k].id == id){
                                member[k].point += point;
                            }
                        }
                        
                        Data.open("pengguna.csv", ios::out | ios::trunc);
                        for (int k = 0; k < i; k++){
                            Data << member[k].id << ","
                                << member[k].password << ","
                                << member[k].point << endl;
                        }
                        Data.close();
                        
                        Data.open("data.csv", ios::out | ios::trunc);
                        for (int k = 0; k < panjangData; k++){
                            Data << Barang[k].nama << ","
                                << Barang[k].jumlah << ","
                                << Barang[k].harga << ","
                                << Barang[k].waktu << ","
                                << Barang[k].pointmasuk << ","
                                << Barang[k].pointkeluar << ","
                                << Barang[k].kategori<< endl;
                        }
                        Data.close();
                        
                        Data.open("riwayatpembelian.csv", ios::app);
                        for (int k = 0; k < datak; k++){

                            Data << id << ","
                                << keranjang[k].nama << ","
                                << keranjang[k].harga << ","
                                << "Cash" << ","
                                << keranjang[k].jumlah << ","
                                << cleanTime << endl;
                        }
                        Data.close();
                        break;
                    }
                    case back:break;
                }
            }else{
                
                Data.open("data.csv", ios::out | ios::trunc);
                for (int k = 0; k < panjangData; k++){
                    Data << Barang[k].nama << ","
                        << Barang[k].jumlah << ","
                        << Barang[k].harga << ","
                        << Barang[k].waktu << ","
                        << Barang[k].pointmasuk << ","
                        << Barang[k].pointkeluar << ","
                        << Barang[k].kategori<< endl;
                }
                Data.close();
                
                Data.open("riwayatpembelian.csv", ios::app);
                for (int k = 0; k < datak; k++){

                    Data << id << ","
                        << keranjang[k].nama << ","
                        << keranjang[k].harga << ","
                        << "Cash" << ","
                        << keranjang[k].jumlah << ","
                        << cleanTime << endl;
                }
                Data.close();
            }
            break;
        }
        case CANCEL:{
            print("======================================", CYAN);
            cout << "::   Pembelian Berhasil Di cancel   ::" << endl;
            print("======================================", CYAN);
            system("pause");
            break;
        }
    }
}

void menu(){
    menu:
    system("cls");
    int pilihan = tampilkan_menu(0,5);
    enum pilihan{admin= 0,member,dfmember,beli,kembali};
    switch(pilihan){
        case admin:loginadmin();break;
        case member:loginmember();goto menu;break;
        case dfmember:daftarmember();break;
        case beli:belibarang("-");goto menu;break;
        case kembali:exit(1);break;
    }
}

int main(){
    menu();
    return 0;

}