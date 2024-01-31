#pragma once

#include <X11/Xlib.h> 
#include <cstdint>

namespace Ui {
namespace Util {

unsigned long allocateColor(uint8_t red, uint8_t green, uint8_t blue, Display *display, Colormap palette = 0);

}
}