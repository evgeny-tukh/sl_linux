#include "sl_bitmap.h"

#include <X11/Xutil.h> 
#include <Imlib2.h>

#include <memory.h>

#pragma pack(1)
union Rgb {
    struct {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    };
    uint32_t clr;

    Rgb(): clr(0) {}
};
#pragma pack()

Ui::Bitmap::Bitmap(Wnd& compatibleWnd):
    _compatibleWnd(compatibleWnd),
    _width(0),
    _height(0),
    _baseX(0),
    _baseY(0),
    _image(0) {
}

Ui::Bitmap::~Bitmap() {
    if (_image)
        XFreePixmap(_compatibleWnd.display(), _image);
}

bool Ui::Bitmap::loadBmp(const char *file) {
    Imlib_Image img = imlib_load_image(file);

    if (!img)
        return false;

    imlib_context_set_image(img);

    int width = imlib_image_get_width();
    int height = imlib_image_get_height();
    auto screen = DefaultScreenOfDisplay(_compatibleWnd.display());

    _image = XCreatePixmap(_compatibleWnd.display(), _compatibleWnd.handle(), width, height, DefaultDepthOfScreen(screen));

    if (!_image) {
        imlib_free_image();
        return false;
    }

    imlib_context_set_display(_compatibleWnd.display());
    imlib_context_set_visual(DefaultVisualOfScreen(screen));
    imlib_context_set_colormap(DefaultColormapOfScreen(screen));
    imlib_context_set_drawable(_image);
    imlib_render_image_on_drawable(0, 0);
    //imlib_free_image();

    return true;
}

bool Ui::Bitmap::loadXbm(const char *file) {
    auto result = XReadBitmapFile(_compatibleWnd.display(), _compatibleWnd.handle(), file, &_width, &_height, &_image, &_baseX, &_baseY);
    return result == BitmapSuccess;
}

bool Ui::Bitmap::drawTo(const Wnd& wnd, int destX, int destY, int srcX, int srcY, GC ctx) {
    if (!_image)
        return false;

    GC localCtx = ctx ? ctx : XCreateGC(wnd.display(), wnd.handle(), 0, nullptr);

    return XCopyPlane(wnd.display(), _image, wnd.handle(), localCtx, srcX, srcY, _width, _height, destX, destY, 8) == Success;
}

bool Ui::Bitmap::loadBmpFile(const char *file) {
    FILE *bmp = fopen(file, "rb+");

    if (!bmp)
        return false;

    BitmapFileHeader fileHeader;

    if (fread(&fileHeader, sizeof(fileHeader), 1, bmp) < 1) {
        fclose(bmp);
        return false;
    }

    uint8_t *buffer = (uint8_t *) malloc(fileHeader.fileSize);

    if (!buffer) {
        fclose(bmp);
        return false;
    }

    BitmapFileHeader *bmpFileHeader = (BitmapFileHeader *) buffer;
    *bmpFileHeader = fileHeader;
    BitmapInfoHeader *bmpInfoHeader = (BitmapInfoHeader *) (bmpFileHeader + 1);
    size_t bytesToRead = fileHeader.fileSize - sizeof(BitmapFileHeader);

    if (fread(buffer + sizeof(BitmapFileHeader), 1, bytesToRead, bmp) < bytesToRead) {
        free(buffer);
        fclose(bmp);
        return false;
    }

    auto display = _compatibleWnd.display();
    auto screen = DefaultScreen(display);
    auto palette = DefaultColormap(display, screen);
    auto depth = DefaultDepthOfScreen(DefaultScreenOfDisplay(display));

    _width = bmpInfoHeader->width;
    _height = bmpInfoHeader->height;
    _image = XCreatePixmap(display, _compatibleWnd.handle(), _width, _height, bmpInfoHeader->bitsPerPixel);

    uint32_t bitsPerLine = bmpInfoHeader->width * bmpInfoHeader->bitsPerPixel;

    if (bitsPerLine % 8)
        bitsPerLine ++;

    uint32_t bytesPerLine = (bitsPerLine >> 3);
    bytesPerLine = ((((bmpInfoHeader->width * bmpInfoHeader->bitsPerPixel) + 31) & ~31) >> 3);
    uint8_t *lineStart = buffer + bmpFileHeader->imageDataOffset;
    auto gc = XCreateGC(display, _image, 0, nullptr);
    XSetPlaneMask(display, gc, AllPlanes);
    int res;

    for (uint32_t y = 0; y < bmpInfoHeader->height; ++ y) {
        uint8_t *curByte = lineStart;
        for (uint32_t x = 0; x < bmpInfoHeader->width; ++x) {
            XColor clr;

            switch (bmpInfoHeader->bitsPerPixel) {
                case 24: {
                    clr.pixel = 0;
                    clr.red = (*(curByte++)) << 8;
                    clr.green = (*(curByte++)) << 8;
                    clr.blue = (*curByte++) << 8;
                    
                    res = XAllocColor(display, palette, &clr);
                    break;
                }
                case 1: {
                    int bitIndex = x % 8;
                    int mask = 0x80 >> bitIndex;
                    
                    if (((*curByte) & mask) == 0)
                        clr.pixel = WhitePixel(display, screen);
                    else
                        clr.pixel = BlackPixel(display, screen);

                    if (bitIndex == 7)
                        ++curByte;
                    
                    break;
                }
                default: {
                    continue;
                }
            }

            res = XSetForeground(display, gc, clr.pixel);
            res = XDrawPoint(display, _image, gc, x, _height - y - 1);
        }

        lineStart += bytesPerLine;
    }

    XFreeGC(display, gc);
    free(buffer);
    fclose(bmp);

    return true;
}