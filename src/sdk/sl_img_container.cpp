#include "sl_img_container.h"

Ui::ImageContainer::ImageContainer(Display *display, const char *imgPath, int x, int y, int width, int height, Window parent):
    Ui::DrawableObject(display, x, y, width, height, parent),
    _bmp(display),
    _parentInst(*Wnd::attach(display, parent)) {
    _bmp.loadBmpFile(imgPath);
}

void Ui::ImageContainer::paint(GC ctx) const {
    _bmp.putTo(_parentInst, _x, _y, 0, 0, ctx);
}