#include "bmp_reader.h"

BmpImageReader::BmpImageReader() {}

BmpImageReader::~BmpImageReader() { bmp_data.clear();}

void BmpImageReader::loadBmp(string path) {
    bmp_data.clear();
    this->path = path;
    ifstream bmp_stream(path, ios::in);
    if (bmp_stream) {
        readImageParams(&bmp_stream);
        readImageData(&bmp_stream);
        bmp_stream.close();
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

void BmpImageReader::saveBmp(string path_var) {
    std::ofstream new_bmp(path_var, std::ios::binary);
    std::ifstream current_bmp(this->path, std::ios::binary);
    new_bmp << current_bmp.rdbuf();
    new_bmp.close();
    current_bmp.close();
    std::fstream output(path_var, std::ios::in | std::ios::out | std::ios::binary);
    end = (start + high * 4) - 3;
    for (int i = 0; i < bmp_data.size();){
        end--;
        output.seekp(end);
        output.put(bmp_data.at(i));
        i++;
        end++;
        output.seekp(end);
        output.put(bmp_data.at(i));
        i++;
        end -= 4;
    }
    output.close();
}

void BmpImageReader::fillPixel(size_t x, size_t y) {
    size_t col = x >= 0 && x <= 7 ? 0 : 1;
    int mask = 1;
    mask = mask << (7 - (x % 8));
    bmp_data.at(col + y * 2)  &= (~mask);
}

void BmpImageReader::drawLine(size_t x_beg, size_t y_beg, size_t x_end,
                              size_t y_end) {
    fillPixel(x_beg, y_beg);
    while (1){
        fillPixel(x_beg, y_beg);
        if(x_beg == x_end && y_beg == y_end) break;
        if (x_beg < x_end) x_beg++;
        else if (x_beg == x_end);
        else x_beg--;
        if (y_beg < y_end) y_beg++;
        else if (y_beg == y_end);
        else y_beg--;
    }
    fillPixel(x_end, y_end);

    
}

void BmpImageReader::drawCross() {
    drawLine(0, 0, width-1, high-1);
    drawLine(width-1, 0, 0, high-1);
}

// void BmpImageReader::drawLine(size_t x_beg, size_t y_beg, size_t x_end,
//     size_t y_end) {
//     int dx = abs(int(x_end - x_beg));
//     int dy = abs(int(y_end - y_beg));
//     int sx = (x_beg < x_end) ? 1 : -1;
//     int sy = (y_beg < y_end) ? 1 : -1;
//     int err = dx - dy;
//     while (1) {
//         fillPixel(x_beg, y_beg);
//         if (x_beg == x_end && y_beg == y_end) break;
//         int e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x_beg += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y_beg += sy;
//         }
//     }
// }


