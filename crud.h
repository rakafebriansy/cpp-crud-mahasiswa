#include <string>
#include <fstream>

namespace crud {
        
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

    void deleteMahasiswa(std::fstream &data);
}