#include "bmp_reader.h"

BmpImageReader::BmpImageReader() {}

BmpImageReader::~BmpImageReader() { bmp_data.clear();}

void BmpImageReader::loadBmp(string path) {
    this->path = path;
    ifstream bmp_stream(path, ios::in);
    if (bmp_stream) {
        readImageParams(&bmp_stream);
        readImageData(&bmp_stream);
        bmp_stream.close();
        cout << "w: " << width << " " << "h:" << high << endl; 
    }
    else throw "No such file or directory!";
}

void BmpImageReader::readImageParams(ifstream *in) {
  in->seekg(START_BYTE);
  start = in->get();
  in->seekg(WIDE_BYTE);
  width = in->get();
  in->seekg(HIGH_BYTE);
  high = in->get();
  in->seekg(BPX_BYTE);
  bpx = in->get();
  end = (start + high * 4) - 3;
}

void BmpImageReader::readImageData(ifstream * img_stream) {
    for (int i = 0; i < high; i++){
        end--;
        img_stream->seekg(end);
        bmp_data.push_back(img_stream->get());
        end++;
        img_stream->seekg(end);
        bmp_data.push_back(img_stream->get());
        end -= 4;
    }
}

void BmpImageReader::readBitsAndPrint(int8_t value){
    int8_t mask = 0b10000000;
    for (size_t i = 0; i < 8; i++) {
        int res = (value & mask) ? 1 : 0;
        if (res == 0)  cout << BLACK_COLOR;
        else cout << WHITE_COLOR;
        value <<= 1;
    } 
}

void BmpImageReader::printBmp() {
    for (size_t i = 0 , k = 0; i < high; i++) {
        for (size_t j = 0; j < 2; j++){
            readBitsAndPrint(bmp_data.at(k));
            k++;
        }
        cout << endl;
    }
}




