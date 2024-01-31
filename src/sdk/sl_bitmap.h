#pragma once

#include <X11/Xlib.h> 

#include <cstdint>
#include <vector>
#include <memory>

#include "sl_wnd.h"

namespace Ui {

#pragma pack(1)

struct BitmapFileHeader {
    char type[2];           // should be BM for BMP file
    uint32_t fileSize;
    uint16_t reserved[2];
    uint32_t imageDataOffset;
};

struct BitmapInfoHeader {
    uint32_t structSize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t pixelsPerMeterHor;
    uint32_t pixelsPerMeterVer;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};

#pragma pack()

class Bitmap {
    public:
        Bitmap(Wnd& compatibleWnd);
        ~Bitmap();

        bool loadXbm(const char *file);
        bool loadBmp(const char *file);
        bool loadBmpFile(const char *file);

        bool drawTo(const Wnd& wnd, int destX, int destY, int srcX = 0, int srcY = 0, GC ctx = nullptr);
        bool putTo(const Wnd& wnd, int destX, int destY, int srcX = 0, int srcY = 0, GC ctx = nullptr);

        unsigned int width() const { return _width; }
        unsigned int height() const { return _height; }

    protected:
        Wnd& _compatibleWnd;
        unsigned int _width;
        unsigned int _height;
        int _baseX;
        int _baseY;
        Pixmap _image;
        std::unique_ptr<XImage> _img;
        std::vector<char> _imgData;
};

}