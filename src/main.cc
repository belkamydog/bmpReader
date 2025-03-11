#include  "bmp_image_reader/BmpImageReader.h"
#include <iostream>
#include <string>

int main(){
    string path;
    try {
        cout << ">> Enter input BMP file name: ";
        cin >> path;
        BmpImageReader reader;
        reader.loadBmp(path);
        reader.renderBmp();
        cout << endl << endl << endl << endl;
        reader.drawCross();
        reader.renderBmp();
        cout << ">> Enter input BMP file name for save: ";
        cin >> path;
        reader.saveBmp(path);
    } catch(const char* msg) {
        std::cerr << msg << '\n';
    }
    return 0;
}