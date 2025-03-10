#ifndef BMPX_SRC_BMP_READER_H
#define BMPX_SRC_BMP_READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define BLACK_COLOR "\033[1;40m "
#define WHITE_COLOR "\033[1;47m "

using namespace std;

const size_t START_BYTE = 10;
const size_t WIDE_BYTE = 18;
const size_t HIGH_BYTE = 22;
const size_t BPX_BYTE = 28;

class BmpImageReader {
    public:
        BmpImageReader();
        ~BmpImageReader();
        void loadBmp(string path);
        void printBmp();
        void saveBmp(string path_var);
        void fillPixel(size_t x, size_t y);
        void drawLine(size_t x_beg, size_t y_beg, size_t x_end, size_t y_end);
        void drawCross();
    
    private: 
        size_t width, high, bpx, start, end;
        string path;
        vector <int8_t> bmp_data;
        void readImageParams(ifstream *in);
        void readImageData(ifstream *img_stream);
        void readBitsAndPrint(int8_t value);

};


#endif // BMPX_SRC_BMP_READER_H