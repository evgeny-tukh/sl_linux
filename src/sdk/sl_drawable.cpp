#include "sl_drawable.h"

Ui::DrawableObject::DrawableObject(Display *display, int x, int y, int width, int height, Window parent):
    _display(display),
    _x(x),
    _y(y),
    _width(width),
    _height(height),
    _parent(parent) {
}

void Ui::DrawableObject::setAnchorage(int flags, int xOffset, int yOffset) {
    _anchorage.flags = flags;
    _anchorage.xOffset = xOffset;
    _anchorage.yOffset = yOffset;
}

void Ui::DrawableObject::setAnchorage(int flags) {
    XWindowAttributes parentAttrs;

    XGetWindowAttributes(_display, _parent, &parentAttrs);
    
    _anchorage.flags = flags;

    if (flags & (int) AnchorageFlags::Left)
        _anchorage.xOffset = _x;
    else if (flags & (int) AnchorageFlags::Right)
        _anchorage.xOffset = parentAttrs.width - _width - _x;
    
    if (flags & (int) AnchorageFlags::Top)
        _anchorage.yOffset = _y;
    else if (flags & (int) AnchorageFlags::Bottom)
        _anchorage.yOffset = parentAttrs.height - _height - _y;
}

void Ui::DrawableObject::applyAnchorage() {
    if (_anchorage.flags) {
        XWindowAttributes parentAttrs;
        int x, y;

        XGetWindowAttributes(_display, _parent, &parentAttrs);

        if (_anchorage.flags & (int) AnchorageFlags::Left)
            x = _anchorage.xOffset;
        else if (_anchorage.flags & (int) AnchorageFlags::Right)
            x = parentAttrs.width - _anchorage.xOffset - _width;
        else
            x = _x;

        if (_anchorage.flags & (int) AnchorageFlags::Top)
            y = _anchorage.yOffset;
        else if (_anchorage.flags & (int) AnchorageFlags::Bottom)
            y = parentAttrs.height - _anchorage.yOffset - _height;
        else
            y = _y;

        move(x, y);
    }
}

void Ui::DrawableObject::resize(uint16_t width, uint16_t height) {
    _width = width;
    _height = height;
}

void Ui::DrawableObject::move(int x, int y) {
    _x = x;
    _y = y;
}
