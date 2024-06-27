#include <iostream>
#include <string>

std::string multiplyString(const std::string& str, int n);

int showMenu();

int main () {
    int user_option = showMenu();
    char is_continue;
    enum options {CREATE = 1, READ, UPDATE, DELETE, FINISH};

    while(user_option != FINISH) {    
        switch(user_option) {
            case CREATE:
                std::cout << "Menambah data Mahasiswa" << std::endl;
                break;
            case READ:
                std::cout << "Menampilkan data Mahasiswa" << std::endl;
                break;
            case UPDATE:
                std::cout << "Mengubah data Mahasiswa" << std::endl;
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

std::string multiplyString(const std::string& str, int n) {
    std::string result;
    for (int i = 0; i < n; i++) {
        result += str;
    }
    return result;
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
    return input;
}