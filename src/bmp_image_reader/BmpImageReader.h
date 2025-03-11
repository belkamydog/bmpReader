#ifndef BMPX_SRC_BMP_READER_H
#define BMPX_SRC_BMP_READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define BLACK_COLOR "\033[1;40m "
#define WHITE_COLOR "\033[1;47m "

#pragma pack(2) 
struct BMPFileHeader {
    uint16_t file_type;                  // File type always BM which is 0x4D42
    uint32_t file_size;                  // Size of the file (in bytes)
    uint16_t reserved1;                  // Reserved, always 0
    uint16_t reserved2;                  // Reserved, always 0
    uint32_t offset_data;                // Start position of pixel data (bytes from the beginning of the file)
};
#pragma pack() 

struct BMPInfoHeader {
    uint32_t size;                      // Size of this header (in bytes)
    int32_t width;                      // width of bitmap in pixels
    int32_t height;                     // width of bitmap in pixels
                                        //       (if positive, bottom-up, with origin in lower left corner)
                                        //       (if negative, top-down, with origin in upper left corner)
    uint16_t planes;                    // No. of planes for the target device, this is always 1
    uint16_t bit_count;                 // No. of bits per pixel
    uint32_t compression;               // 0 or 3 - uncompressed.
    uint32_t size_image;                // 0 - for uncompressed images
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
    uint32_t colors_important;          // No. of colors used for displaying the bitmap. If 0 all colors are required
};

struct RgbColor {
   int8_t rgbBlue;
   int8_t rgbGreen;
   int8_t rgbRed;
 };

using namespace std;

class BmpImageReader {
    public:
        BmpImageReader();
        ~BmpImageReader();
        void loadBmp(string path);
        void renderBmp();
        void saveBmp(string path);
        void drawCross();
    
    private:
        string path;
        struct BMPFileHeader file_header;
        struct BMPInfoHeader info_header;
        vector <RgbColor> bit_map;
 
    private:
        void copyFile(string path_to_coped);
        void fillPixel(size_t x, size_t y);
        void drawLine(size_t x_beg, size_t y_beg, size_t x_end, size_t y_end);
        void readImageHeaders(ifstream *in);
        void readPixelMap(ifstream *img_stream);
};

#endif // BMPX_SRC_BMP_READER_H