#include <cstdint>

#include <math.h>

#include "sl_display.h"
#include "sl_util.h"

namespace {

const uint16_t EDGE = 20;
const uint16_t PADDING = 40;
const uint16_t TICK_LENGTH = 15;
const uint16_t TEN_DEGREES_EXTENT = 5;
const uint16_t TAG_EXTENT = 10;
const double PI = 3.1415926535897932384626433832795;

uint16_t getWidthHeight(Display *display) {
    uint16_t width, height;
    Ui::Util::getScreenSize(display, width, height);

    if (width < height)
        return width - EDGE * 2;

    return height - EDGE * 2;
}

}

TargetDisplay::TargetDisplay(const ValueStorage& storage, Display *display, Window parent):
    Wnd(display, EDGE, EDGE, getWidthHeight(display), getWidthHeight(display), parent), _storage(storage), _vesselShape() {
    for (int i = 0; i < 360; ++i) {
        double angle = PI * (double) i / 180.0;
        _sinuses[i] = sin(angle);
        _cosinuses[i] = cos(angle);
    }
}
/*
void TargetDisplay::onSizeChanged(int width, int height, bool& notifyChildren) {
    populateTicksArray();
}

void TargetDisplay::setupLayout(int xParam, int yParam) {
    populateTicksArray();
}
*/
void TargetDisplay::paint(GC ctx) {
    auto bg = Ui::Util::allocateColor(0, 0, 0, _display);
    auto fg = Ui::Util::allocateColor(255, 255, 255, _display);
    auto shipBg = Ui::Util::allocateColor(255, 255, 0, _display);
    setBgColor(bg);
    XSetForeground(_display, ctx, bg);
    XFillRectangle(_display, _wnd, ctx, 0, 0, _width, _height);

    populateTicksArray();

    int oldLineWidth = Ui::Util::setLineWidth(_display, ctx, 2);
    XSetForeground(_display, ctx, fg);
    XDrawSegments(_display, _wnd, ctx, _ticks.data(), _ticks.size());
    Ui::Util::setLineWidth(_display, ctx, oldLineWidth);

    std::vector<XPoint> shape;
    _vesselShape.getShape(_storage.valueOf(Types::DataType::HDG, 0.0), _x + _width / 2, _y + _height / 2, shape, 2.0);
    XSetBackground(_display, ctx, shipBg);
    XSetForeground(_display, ctx, shipBg);
    XFillPolygon(_display, _wnd, ctx, shape.data(), shape.size(), Nonconvex, CoordModeOrigin);
}

void TargetDisplay::populateTicksArray() {
    double centerX = ((double) _width) * 0.5;
    double centerY = ((double) _height) * 0.5;
    double radius1 = (double) (_width - PADDING * 2) * 0.5;
    double radius2 = radius1 - TICK_LENGTH;
    double radius3 = radius1 + TEN_DEGREES_EXTENT;

    for (int i = 0, j = 0; i < 360; ++i) {
        bool tenDegrees = ((i % 10) != 0);
        double radius = tenDegrees ? radius1 : radius1 + TEN_DEGREES_EXTENT;
        double x1 = centerX + radius * _sinuses[i];
        double x2 = centerX + radius2 * _sinuses[i];
        double y1 = centerY - radius * _cosinuses[i];
        double y2 = centerY - radius2 * _cosinuses[i];

        _ticks[i].x1 = x1;
        _ticks[i].y1 = y1;
        _ticks[i].x2 = x2;
        _ticks[i].y2 = y2;

        if (tenDegrees) {
            double x = centerX + (radius + TAG_EXTENT) * _sinuses[i];
            double y = centerY - (radius + TAG_EXTENT) * _cosinuses[i];

            _tagPos[i/10].x = x;
            _tagPos[i/10].y = y;
        }
    }
}