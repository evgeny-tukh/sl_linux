#pragma once

#include <X11/Xlib.h> 
#include <cstdint>

namespace Ui {
namespace Util {

unsigned long allocateColor(uint8_t red, uint8_t green, uint8_t blue, Display *display, Colormap palette = 0);
Display *openDisplay();
void fillRondedRect(Display *display, Drawable drawable, GC ctx, int x, int y, int width, int height, int radius);
void drawRondedRect(Display *display, Drawable drawable, GC ctx, int x, int y, int width, int height, int radius);
void getScreenSize(Display *display, uint16_t& width, uint16_t& height);

}
}