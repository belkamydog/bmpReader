#include  "bmp_reader/bmp_reader.h"
#include <iostream>
#include <string>

int main(){
    string path;
    try {
        cout << ">> Enter input BMP file name: ";
        cin >> path;
        BmpImageReader reader;
        reader.loadBmp(path);
        reader.printBmp();
        cout << endl;
        reader.drawCross();
        reader.printBmp();
        cout << ">> Enter input BMP file name for save: ";
        cin >> path;
        reader.saveBmp(path);
    } catch(const char* msg) {
        std::cerr << msg << '\n';
    }
    return 0;
}