#include <string>

#include "sl_drawable.h"

namespace {
    const static std::string DEF_FONT_NAME{"*7x14*"};
}

const std::string& Ui::DrawableObject::getDefaultFontName() {
    return DEF_FONT_NAME;
}

Ui::DrawableObject::DrawableObject(Display *display, int x, int y, int width, int height, DrawableObject *parent):
    _parentDrawable(parent),
    _display(display),
    _x(x),
    _y(y),
    _width(width),
    _height(height),
    _parent(0) {
}

Ui::DrawableObject::DrawableObject(Display *display, int x, int y, int width, int height, Window parentWnd):
    _parentDrawable(nullptr),
    _display(display),
    _x(x),
    _y(y),
    _width(width),
    _height(height),
    _parent(parentWnd) {
}

Window Ui::DrawableObject::parent() const {
    if (_parent)
        return _parent;

    if (_parentDrawable)
        return _parentDrawable->parent();

    return 0;
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

const std::string& Ui::DrawableObject::getFontName() const {
    return DEF_FONT_NAME;
}

bool Ui::DrawableObject::styleFlag(uint32_t mask) const {
    return _style & mask;
}

void Ui::DrawableObject::setStyle(uint32_t mask, uint32_t value) {
    _style &= (~mask);
    _style |= value;
}

void Ui::DrawableObject::setStyle(uint32_t mask, bool flag) {
    if (flag)    
        _style |= mask;
    else
        _style &= (~mask);
}

void Ui::DrawableObject::drawLine(GC ctx, int x1, int y1, int x2, int y2) const {
    XDrawLine(_display, _parent, ctx, _x + x1, _y + y1, _x + x2, _y + y2);
}