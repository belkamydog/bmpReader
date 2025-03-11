#include "BmpImageReader.h"

BmpImageReader::BmpImageReader() {}

BmpImageReader::~BmpImageReader() { bit_map.clear();}

void BmpImageReader::loadBmp(string path) {
    bit_map.clear();
    this->path = path;
    ifstream bmp_stream(path, ios::in);
    if (bmp_stream) {
        readImageHeaders(&bmp_stream);
        cout << info_header .height <<  " " << info_header.width << endl; 
        readPixelMap(&bmp_stream);
        bmp_stream.close();
    }
    else throw "No such file or directory!";
}

void  BmpImageReader::readImageHeaders(ifstream *in) {
    in->read((char *) &file_header, sizeof(BMPFileHeader));
    if (file_header.file_type != 0x4D42) throw "Uncorrected format of file";
    in->read((char *) &info_header, sizeof(BMPInfoHeader));
    in->seekg(file_header.offset_data, ios::beg);
}

void BmpImageReader::readPixelMap(ifstream *img_stream) {
    size_t rowSize = (info_header.width * sizeof(RgbColor) + 3) & (~3);
    size_t shift = file_header.offset_data;
    for (size_t y = 0; y < (size_t)info_header.height; y++) {
        img_stream->seekg(shift, ios::beg);
        for (size_t x = 0; x < (size_t)info_header.width; x++) {
            RgbColor pixel_color = {0, 0, 0};
            if (!img_stream->read((char*) &pixel_color, sizeof(RgbColor))) throw "Ошибка чтения данных!";
            bit_map.push_back(pixel_color);
        }
        shift += rowSize;
    }
}

void BmpImageReader::renderBmp() {
    for (int i = 0; i < (int) info_header.height; i++){
        for (int j = 0; j < (int) info_header.width; j++) {
            RgbColor pixel = bit_map.at((info_header.height-1-i)*info_header.width+j);
            if (pixel.rgbBlue < 0 && pixel.rgbGreen < 0 && pixel.rgbRed < 0) cout<< WHITE_COLOR;
            else cout << BLACK_COLOR;
        }
        cout << endl;
    }
}

void BmpImageReader::saveBmp(string path) {
    copyFile(path);
    std::fstream output(path, std::ios::in | std::ios::out | std::ios::binary);
    size_t rowSize = (info_header.width * sizeof(RgbColor) + 3) & (~3);
    size_t shift = file_header.offset_data + info_header.size_image;
    for (int i = 0; i < (int)info_header.height; i++) {
        output.seekg(shift, ios::beg);
        for (int j = 0; j < (int)info_header.width; j++) {
            RgbColor pixel_color = bit_map.at((info_header.height-1-i)*info_header.width+j);
            output.write((char*) &pixel_color, sizeof(RgbColor));
        }
        shift -= rowSize;
    }
    output.close();
}

void BmpImageReader::copyFile(string path_to_coped) {
    std::ofstream new_bmp(path_to_coped, std::ios::binary);
    std::ifstream current_bmp(this->path, std::ios::binary);
    new_bmp << current_bmp.rdbuf();
    new_bmp.close();
    current_bmp.close();
}

void BmpImageReader::fillPixel(size_t x, size_t y) {
    bit_map.at(x + y * info_header.width).rgbBlue = 0;
    bit_map.at(x + y * info_header.width).rgbGreen = 0;
    bit_map.at(x + y * info_header.width).rgbRed = 0;
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
    drawLine(0, 0, info_header.width-1, info_header.height-1);
    drawLine(info_header.width-1, 0, 0, info_header.height-1);
}
