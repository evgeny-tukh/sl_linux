#pragma once

#include <sl_drawable.h>
#include <sl_bitmap.h>

namespace Ui {

class ImageContainer: public DrawableObject {
    public:
        ImageContainer(Display *display, const char *imgPath, int x, int y, int width, int height, Window parent);

        virtual void paint(GC ctx) const;

    protected:
        Wnd& _parentInst;
        Bitmap _bmp;
};

}