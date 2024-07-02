#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstring>
#include "crud.h"

int main () {

    std::fstream data;

    crud::checkDatabase(data);

    int user_option = crud::showMenu();
    char is_continue;
    enum options {CREATE = 1, READ, UPDATE, DELETE, FINISH};

    while(user_option != FINISH) {    
        switch(user_option) {
            case CREATE:
                std::cout << "Menambah data Mahasiswa" << std::endl;
                crud::insertMahasiswa(data);
                break;
            case READ:
                std::cout << "Menampilkan data Mahasiswa" << std::endl;
                crud::showMahasiswa(data);
                break;
            case UPDATE:
                std::cout << "Mengubah data Mahasiswa" << std::endl;
                crud::showMahasiswa(data);
                crud::updateMahasiswa(data);
                crud::showMahasiswa(data);
                break;
            case DELETE:
                std::cout << "Menghapus data Mahasiswa" << std::endl;
                crud::showMahasiswa(data);
                crud::deleteMahasiswa(data);
                crud::checkDatabase(data);
                crud::showMahasiswa(data);
                break;
            default:
                std::cout << "Pilihan tidak ditemukan." << std::endl;
                break;
        }
            label_continue:
            std::cout << "Lanjutkan? [y/n]: " << std::endl;
            std::cin >> is_continue;
            if((is_continue == 'y') | (is_continue == 'Y')) {
                user_option = crud::showMenu();
            } else if ((is_continue == 'n') | (is_continue == 'N')) {
                break;
            } else {
                goto label_continue;
            }
    }

    std::cout << "Program berakhir..." << std::endl;

    return 0;
}