#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#include "sl_util.h"

namespace {
    const char *DISPLAY = "DISPLAY";
    const int QUARTER = 90 * 64;
}

namespace Ui {
namespace Util {
    struct Circle {
        XPoint offsets[361];

        Circle(int radius) {
            for (int angle = 0; angle < 360; ++ angle) {
                double dir = angle * M_PI / 180.0;
                offsets[angle].x = (double) radius * sin(dir);
                offsets[angle].y = - (double) radius * cos(dir);
            }

            offsets[360].x = offsets[0].x;
            offsets[360].y = offsets[0].y;
        }

        void get(int dir, int centerX, int centerY, XPoint& pt) {
            pt.x = centerX + offsets[dir].x;
            pt.y = centerY + offsets[dir].y;
        }
    };
}
}
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

Display *Ui::Util::openDisplay() {
    char *displayEnv = getenv(DISPLAY);

    if (!displayEnv)
        return nullptr;

    return XOpenDisplay(displayEnv);
}

void Ui::Util::fillRondedRect(Display *display, Drawable drawable, GC ctx, int x, int y, int width, int height, int radius) {
    std::vector<XPoint> vertices;
    Circle circle(radius);

    vertices.resize(91 * 4);

    int count = 0;
    for (int i = 0; i <= 90; ++ i, ++ count)
        circle.get(i, x + width - 1 - radius, y + radius - 1, vertices[count]);
    for (int i = 90; i <= 180; ++ i, ++ count)
        circle.get(i, x + width - 1 - radius, y + height - 1 - radius, vertices[count]);
    for (int i = 180; i <= 270; ++ i, ++ count)
        circle.get(i, x + radius - 1, y + height - 1 - radius, vertices[count]);
    for (int i = 270; i <= 360; ++ i, ++ count)
        circle.get(i, x + radius - 1, y + radius - 1, vertices[count]);
    XFillPolygon(display, drawable, ctx, vertices.data(), count, Convex, CoordModeOrigin);
}

void Ui::Util::drawRoundedRect(Display *display, Drawable drawable, GC ctx, int x, int y, int width, int height, int radius) {
    std::vector<XPoint> vertices;
    Circle circle(radius);

    vertices.resize(91 * 4 + 1);

    int count = 0;
    for (int i = 0; i <= 90; ++ i, ++ count)
        circle.get(i, x + width - 1 - radius, y + radius - 1, vertices[count]);
    for (int i = 90; i <= 180; ++ i, ++ count)
        circle.get(i, x + width - 1 - radius, y + height - 1 - radius, vertices[count]);
    for (int i = 180; i <= 270; ++ i, ++ count)
        circle.get(i, x + radius - 1, y + height - 1 - radius, vertices[count]);
    for (int i = 270; i <= 360; ++ i, ++ count)
        circle.get(i, x + radius - 1, y + radius - 1, vertices[count]);
    vertices[count].x = vertices.front().x;
    vertices[count].y = vertices.front().y;
    ++count;
    XDrawLines(display, drawable, ctx, vertices.data(), count, CoordModeOrigin);
}

void Ui::Util::getScreenSize(Display *display, uint16_t& width, uint16_t& height) {
    width = DisplayWidth(display, DefaultScreen(display));
    height = DisplayHeight(display, DefaultScreen(display));
}

int Ui::Util::setLineWidth(Display *display, GC ctx, int width) {
    XGCValues savedValues, newValues;

    newValues.line_width = width;

    XGetGCValues(display, ctx, GCLineWidth, &savedValues);
    XChangeGC(display, ctx, GCLineWidth, &newValues);

    return savedValues.line_width;
}
