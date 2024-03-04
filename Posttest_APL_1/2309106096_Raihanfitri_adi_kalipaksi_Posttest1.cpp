#include <iostream>

using namespace std;

int main() {
    string nim, nama, id, pw, pilih;
    int percobaan;
    float suhu, konversi;
    percobaan = 0;
    while (percobaan < 3) {
        cout << "1. login" << endl;
        cout << "2. exit" << endl;
        cout << "========================" << endl;
        cout << "Masukkan pilihan anda: ";
        getline(cin,pilih);
        if (pilih == "1"){

            cout << "Masukan Nama: ";
            getline(cin,nama);
            cout << "Masukkan Nim: ";
            getline(cin,nim);
            id = "raihanfitri adi kalipaksi";
            pw = "2309106096";
            if (nama == id && nim == pw) {
                break;
            }else {
                percobaan++;
                cout << "Percobaan Tersisa: " << 3 - percobaan << endl;
            }  
        } else if (pilih == "2"){
            cout << "Terimakasih..." << endl;
            exit(0);
        }else{
            cout << "input tidak valid !!!" << endl;
        }
            
    }


    while (percobaan < 3) {

        cout << "1. Konversi Celcius" << endl;
        cout << "2. Konversi Reamur" << endl;
        cout << "3. Konversi Fahrenheit" << endl;
        cout << "4. Konversi Kelvin" << endl;
        cout << "5. Keluar" << endl;
        cout << "========================" << endl;
        cout << "Masukkan Pilihan Anda: ";
        cin >> pilih;

        if (pilih == "1") {
            cout << "1. Konversi Celcius > Reamur" << endl;
            cout << "2. Konversi Celcius > Fahrenheit" << endl;
            cout << "3. Konversi Celcius > kelvin" << endl;
            cout << "========================" << endl;
            cout << "Masukkan Pilihan Anda: ";
            cin >> pilih;
            if (pilih == "1") {
                cout << "Masukkan Suhu Celciusnya: ";
                cin >> suhu;
                konversi = suhu * 4 / 5;
                cout << "Hasil Konversi Celcius Ke Reamur Adalah :" << konversi << endl;
            }
            else if (pilih == "2") {
                cout << "Masukkan Suhu Celciusnya: ";
                cin >> suhu;
                konversi = (suhu * 9 / 5) + 32;
                cout << "Hasil Konversi Celcius Ke Fahrenheit Adalah :" << konversi << endl;
            }
            else if (pilih == "3") {
                cout << "Masukkan Suhu Celciusnya: ";
                cin >> suhu;
                konversi = suhu + 273.15;
                cout << "Hasil Konversi Celcius Ke Kelvin Adalah :" << konversi << endl;
            }
            else {
                cout << "Input Tidak Valid !!!" << endl;
            }
        }
        else if (pilih == "2") {
            cout << "1. Konversi Reamur > Celcius" << endl;
            cout << "2. Konversi Reamur > Fahrenheit" << endl;
            cout << "3. Konversi Reamur > kelvin" << endl;
            cout << "========================" << endl;
            cout << "Masukkan Pilihan Anda: ";
            cin >> pilih;
            if (pilih == "1") {
                cout << "Masukkan Suhu Reamurnya: ";
                cin >> suhu;
                konversi = suhu * 5 / 4;
                cout << "Hasil Konversi Reamur Ke Celcius Adalah :" << konversi << endl;
            }
            else if (pilih == "2") {
                cout << "Masukkan Suhu Reamurnya: ";
                cin >> suhu;
                konversi = (suhu * 9 / 4) + 32;
                cout << "Hasil Konversi Reamur Ke Fahrenheit Adalah :" << konversi << endl;

            }
            else if (pilih == "3") {
                cout << "Masukkan Suhu Reamurnya: ";
                cin >> suhu;
                konversi = (suhu * 5 / 4) + 273.15;
                cout << "Hasil Konversi Reamur Ke Kelvin Adalah :" << konversi << endl;
            }
            else {
                cout << "Input Tidak Valid !!!" << endl;
            }

        }
        else if (pilih == "3") {
            cout << "1. Konversi Fahrenheit > Celcius" << endl;
            cout << "2. Konversi Fahrenheit > Reamur" << endl;
            cout << "3. Konversi Fahrenheit > kelvin" << endl;
            cout << "========================" << endl;
            cout << "Masukkan Pilihan Anda: ";
            cin >> pilih;
            if (pilih == "1") {
                cout << "Masukkan Suhu Fahrenheitnya: ";
                cin >> suhu;
                konversi = (suhu - 32) * 5 / 9;
                cout << "Hasil Konversi Fahrenheit Ke Celcius Adalah :" << konversi << endl;
            }
            else if (pilih == "2") {
                cout << "Masukkan Suhu Fahrenheitnya: ";
                cin >> suhu;
                konversi = (suhu - 32) * 4 / 9;
                cout << "Hasil Konversi Fahrenheit Ke Reamur Adalah :" << konversi << endl;
            }
            else if (pilih == "3") {
                cout << "Masukkan Suhu Fahrenheitnya: ";
                cin >> suhu;
                konversi = (suhu - 32) * 5 / 9 + 273.15;
                cout << "Hasil Konversi Fahrenheit Ke Kelvin Adalah :" << konversi << endl;
            }
            else {
                cout << "Input Tidak Valid !!!" << endl;
            }
        }
        else if (pilih == "4") {
            cout << "1. Konversi Kelvin > Celcius" << endl;
            cout << "2. Konversi Kelvin > Reamur" << endl;
            cout << "3. Konversi Kelvin > Fahrenheit" << endl;
            cout << "========================" << endl;
            cout << "Masukkan Pilihan Anda: ";
            cin >> pilih;
            if (pilih == "1") {
                cout << "Masukkan Suhu Kelvinnya: ";
                cin >> suhu;
                konversi = suhu - 273.15;
                cout << "Hasil Konversi Kelvin Ke Celcius Adalah :" << konversi << endl;
            }
            else if (pilih == "2") {
                cout << "Masukkan Suhu Kelvinnya: ";
                cin >> suhu;
                konversi = (suhu - 273.15) * 4 / 9;
                cout << "Hasil Konversi Kelvin Ke Reamur Adalah :" << konversi << endl;
            }
            else if (pilih == "3") {
                cout << "Masukkan Suhu Kelvinnya: ";
                cin >> suhu;
                konversi = (suhu - 273.15) * 9 / 5;
                cout << "Hasil Konversi Kelvin Ke Fahrenheit Adalah :" << konversi << endl;
            }
            else {
                cout << "Input Tidak Valid !!!" << endl;
            }

        }
        else if (pilih == "5") {
            cout << "Terimakasih..." << endl ;
            break;
        }
        else {
            cout << "Input Tidak Valid !!!" << endl;
        }

    }
    return 0;
}