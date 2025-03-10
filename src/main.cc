#include  "bmp_reader/bmp_reader.h"
#include <iostream>
#include <string>

int main(){
    string path1 = "../resources/it.bmp";
    string path2 = "../out/empty.bmp";
    try {
        BmpImageReader *reader = new BmpImageReader();
        reader->loadBmp(path1);
        reader->printBmp();
    } catch(const char* msg) {
        std::cerr << msg << '\n';
    }
    
    return 0;
}