#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstring>
#include "crud.h"

void crud::checkDatabase(std::fstream& data) {
    data.open("data.bin", std::ios::out | std::ios::in | std::ios::binary); //reading file

    if(data.is_open()) {
        std::cout << "Data tersedia" << std::endl;
    } else {
        data.close(); //close current stream

        data.open("data.bin", std::ios::trunc | std::ios::out | std::ios::in | std::ios::binary); //create new file and open stream
    }
}

std::string crud::multiplyString(const std::string& str, int n) {
    std::string result;
    for (int i = 0; i < n; i++) {
        result += str;
    }
    return result;
}

int crud::getDataSize(std::fstream &data) {
    int start, end;

    data.seekg(0, std::ios::beg); //move pointer into the begin of data
    start = data.tellg();

    data.seekg(0, std::ios::end); //move pointer into the end of data
    end = data.tellg();

    return (end-start)/sizeof(crud::Mahasiswa);

}

crud::Mahasiswa crud::readData(std::fstream &data, int position) {
    crud::Mahasiswa last_inserted_mahasiswa;
    data.seekg((position - 1)*sizeof(crud::Mahasiswa), std::ios::beg);
    data.read(reinterpret_cast<char*>(&last_inserted_mahasiswa),sizeof(crud::Mahasiswa));
    return last_inserted_mahasiswa;
}

void crud::writeData(std::fstream &data, int position, crud::Mahasiswa &input_mahasiswa) {
    data.seekp((position - 1)*sizeof(crud::Mahasiswa), std::ios::beg); //move pointer into the begin of data (using size of struct)
    data.write(reinterpret_cast<char*>(&input_mahasiswa),sizeof(crud::Mahasiswa)); //writing data
}

int crud::showMenu() {
    int input;
    system("cls");

    std::cout << "\nSistem Informasi Mahasiswa" << std::endl;
    std::cout << crud::multiplyString("=",30) << std::endl;
    std::cout << "1. Tambah data Mahasiswa" << std::endl;
    std::cout << "2. Tampilkan data Mahasiswa" << std::endl;
    std::cout << "3. Ubah data Mahasiswa" << std::endl;
    std::cout << "4. Hapus data Mahasiswa" << std::endl;
    std::cout << "5. Keluar" << std::endl;
    std::cout << crud::multiplyString("=",30) << std::endl;
    std::cout << "Pilih [1-5]: ";

    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //remove newline in input stream
    return input;
}

void crud::insertMahasiswa(std::fstream &data) {
    crud::Mahasiswa input_mahasiswa, last_inserted_mahasiswa;
    
    int size = crud::getDataSize(data);

    if(size == 0) {
        input_mahasiswa.pk = 1;
    } else {
        last_inserted_mahasiswa = crud::readData(data, size);
        input_mahasiswa.pk = last_inserted_mahasiswa.pk+1;
    }

    std::cout << "NIM: ";
    std::cin.getline(input_mahasiswa.nim, 16); //get array of char input (can read space, newline, etc.)
    std::cout << "Nama: ";
    std::cin.getline(input_mahasiswa.nama, 40);
    std::cout << "Jurusan: ";
    std::cin.getline(input_mahasiswa.jurusan, 40);

    crud::writeData(data, size + 1, input_mahasiswa);
}

void crud::showMahasiswa(std::fstream &data) {
    int size = crud::getDataSize(data);
    crud::Mahasiswa mahasiswa;
    std::cout << "no.\tpk.\tNIM.\tNama.\tJurusan." << std::endl;
    for (int i = 1; i <= size; i++) {
        mahasiswa = crud::readData(data, i);
        std::cout << i << "\t";
        std::cout << mahasiswa.pk << "\t";
        std::cout << mahasiswa.nim << "\t";
        std::cout << mahasiswa.nama << "\t";
        std::cout << mahasiswa.jurusan << std::endl;
    }
}

void crud::updateMahasiswa(std::fstream &data) {
    int number;
    crud::Mahasiswa mahasiswa;
    std::cout << "Pilih no: ";
    std::cin >> number;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    mahasiswa = crud::readData(data, number);
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
    
    crud::writeData(data, number, mahasiswa);
}

void crud::deleteMahasiswa(std::fstream &data) {
    int number, size, offset;
    crud::Mahasiswa temp_mahasiswa;
    crud::Mahasiswa blank_mahasiswa = {};
    std::fstream temp_data;

    size = crud::getDataSize(data);

    std::cout << "Hapus nomor: ";
    std::cin >> number;

    crud::writeData(data, number, blank_mahasiswa);

    temp_data.open("temp.dat", std::ios::trunc | std::ios::out | std::ios::in | std::ios::binary);
    offset = 0;
    for (int i = 1; i <= size; i++) {
        temp_mahasiswa = crud::readData(data,i);
        if (std::strcmp(temp_mahasiswa.nama, "") != 0) {
            crud::writeData(temp_data,i - offset,temp_mahasiswa);
        } else {
            offset++;
        }
    }
    data.close();

    data.open("data.bin", std::ios::trunc | std::ios::out | std::ios::binary);
    data.close();

    size = crud::getDataSize(temp_data);
    data.open("data.bin", std::ios::out | std::ios::in | std::ios::binary);
    for (int i = 1; i <= size; i++) {
        temp_mahasiswa = crud::readData(temp_data,i);
        crud::writeData(data,i,temp_mahasiswa);
    }
    data.close();
}