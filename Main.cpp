#include <iostream>
#include <string>
#include <fstream>
#include <limits>

//windows gcc compiler
struct Mahasiswa {
    int pk;
    char nim[16];
    char nama[40];
    char jurusan[40];
};

//another compiler
// struct Mahasiswa {
//     int pk;
//     std::string nim;
//     std::string nama;
//     std::string jurusan;
// };

std::string multiplyString(const std::string &str, int n);

void checkDatabase(std::fstream &data);

int showMenu();

int getDataSize(std::fstream &data);

Mahasiswa readData(std::fstream &data, int size);

void writeData(std::fstream &data, int position, Mahasiswa &input_mahasiswa);

void insertMahasiswa(std::fstream &data);

void showMahasiswa(std::fstream &data);

void updateMahasiswa(std::fstream &data);

int main () {

    std::fstream data;

    checkDatabase(data);

    int user_option = showMenu();
    char is_continue;
    enum options {CREATE = 1, READ, UPDATE, DELETE, FINISH};

    while(user_option != FINISH) {    
        switch(user_option) {
            case CREATE:
                std::cout << "Menambah data Mahasiswa" << std::endl;
                insertMahasiswa(data);
                break;
            case READ:
                std::cout << "Menampilkan data Mahasiswa" << std::endl;
                showMahasiswa(data);
                break;
            case UPDATE:
                std::cout << "Mengubah data Mahasiswa" << std::endl;
                showMahasiswa(data);
                updateMahasiswa(data);
                showMahasiswa(data);
                break;
            case DELETE:
                std::cout << "Menghapus data Mahasiswa" << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak ditemukan." << std::endl;
                break;
        }
            label_continue:
            std::cout << "Lanjutkan? [y/n]: " << std::endl;
            std::cin >> is_continue;
            if((is_continue == 'y') | (is_continue == 'Y')) {
                user_option = showMenu();
            } else if ((is_continue == 'n') | (is_continue == 'N')) {
                break;
            } else {
                goto label_continue;
            }
    }

    std::cout << "Program berakhir..." << std::endl;

    std::cin.get();
    return 0;
}

void checkDatabase(std::fstream& data) {
    data.open("data.bin", std::ios::out | std::ios::in | std::ios::binary); //reading file

    if(data.is_open()) {
        std::cout << "Data tersedia" << std::endl;
    } else {
        data.close(); //close current stream

        data.open("data.bin", std::ios::trunc | std::ios::out | std::ios::in | std::ios::binary); //create new file and open stream
    }
}

std::string multiplyString(const std::string& str, int n) {
    std::string result;
    for (int i = 0; i < n; i++) {
        result += str;
    }
    return result;
}

int getDataSize(std::fstream &data) {
    int start, end;

    data.seekg(0, std::ios::beg); //move pointer into the begin of data
    start = data.tellg();

    data.seekg(0, std::ios::end); //move pointer into the end of data
    end = data.tellg();

    return (end-start)/sizeof(Mahasiswa);

}

Mahasiswa readData(std::fstream &data, int position) {
    Mahasiswa last_inserted_mahasiswa;
    data.seekg((position - 1)*sizeof(Mahasiswa), std::ios::beg);
    data.read(reinterpret_cast<char*>(&last_inserted_mahasiswa),sizeof(Mahasiswa));
    return last_inserted_mahasiswa;
}

void writeData(std::fstream &data, int position, Mahasiswa &input_mahasiswa) {
    data.seekp((position - 1)*sizeof(Mahasiswa), std::ios::beg); //move pointer into the begin of data (using size of struct)
    data.write(reinterpret_cast<char*>(&input_mahasiswa),sizeof(Mahasiswa)); //writing data
}

int showMenu() {
    int input;
    system("cls");

    std::cout << "\nSistem Informasi Mahasiswa" << std::endl;
    std::cout << multiplyString("=",30) << std::endl;
    std::cout << "1. Tambah data Mahasiswa" << std::endl;
    std::cout << "2. Tampilkan data Mahasiswa" << std::endl;
    std::cout << "3. Ubah data Mahasiswa" << std::endl;
    std::cout << "4. Hapus data Mahasiswa" << std::endl;
    std::cout << "5. Keluar" << std::endl;
    std::cout << multiplyString("=",30) << std::endl;
    std::cout << "Pilih [1-5]: ";

    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //remove newline in input stream
    return input;
}

void insertMahasiswa(std::fstream &data) {
    Mahasiswa input_mahasiswa, last_inserted_mahasiswa;
    
    int size = getDataSize(data);

    if(size == 0) {
        input_mahasiswa.pk = 1;
    } else {
        last_inserted_mahasiswa = readData(data, size);
        input_mahasiswa.pk = last_inserted_mahasiswa.pk+1;
    }

    std::cout << "NIM: ";
    std::cin.getline(input_mahasiswa.nim, 16); //get array of char input (can read space, newline, etc.)
    std::cout << "Nama: ";
    std::cin.getline(input_mahasiswa.nama, 40);
    std::cout << "Jurusan: ";
    std::cin.getline(input_mahasiswa.jurusan, 40);

    writeData(data, size + 1, input_mahasiswa);
}

void showMahasiswa(std::fstream &data) {
    int size = getDataSize(data);
    Mahasiswa mahasiswa;
    std::cout << "no.\tpk.\tNIM.\tNama.\tJurusan." << std::endl;
    for (int i = 1; i <= size; i++) {
        mahasiswa = readData(data, i);
        std::cout << i << "\t";
        std::cout << mahasiswa.pk << "\t";
        std::cout << mahasiswa.nim << "\t";
        std::cout << mahasiswa.nama << "\t";
        std::cout << mahasiswa.jurusan << std::endl;
    }
}

void updateMahasiswa(std::fstream &data) {
    int number;
    Mahasiswa mahasiswa;
    std::cout << "Pilih no: ";
    std::cin >> number;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    mahasiswa = readData(data, number);
    std::cout << "\n\nPilihan data:" << std::endl;
    std::cout << "NIM: " << mahasiswa.nim << std::endl;
    std::cout << "Nama: " << mahasiswa.nama << std::endl;
    std::cout << "Jurusan: " << mahasiswa.jurusan << std::endl;
    
    std::cout << "\nMerubah data: " << std::endl;
    std::cout << "NIM: ";
    std::cin.getline(mahasiswa.nim, 16);
    std::cout << "Nama: ";
    std::cin.getline(mahasiswa.nama, 40);
    std::cout << "Jurusan: ";
    std::cin.getline(mahasiswa.jurusan, 40);
    
    writeData(data, number, mahasiswa);
}