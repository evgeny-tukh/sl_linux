#include "sl_util.h"

unsigned long Ui::Util::allocateColor(uint8_t red, uint8_t green, uint8_t blue, Display *display, Colormap palette) {
    XColor clr;
    clr.red = red * 256;
    clr.green = green * 256;
    clr.blue = blue * 256;

    if (!palette)
        palette = DefaultColormap(display, DefaultScreen(display));

    XAllocColor(display, palette, &clr);

    return clr.pixel;
}

