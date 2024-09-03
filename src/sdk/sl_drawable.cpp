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

    // looking for first windowed parent and take Window of it
    while (parent) {
        if (parent->_parent) {
            _parent = parent->_parent;
            break;
        }

        parent = parent->_parentDrawable;
    }

    if (parent)
        parent->addChildDrawableObject(this);
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

void Ui::DrawableObject::addChildDrawableObject (DrawableObject *child) {
    _childDrawables.push_back(child);
}

void Ui::DrawableObject::setParentDrawableObject (DrawableObject *parent) {
    _parentDrawable = parent;
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
    int parentWidth, parentHeight;

    if ((flags & (int) AnchorageFlags::ParentBase) == 0) {
        XWindowAttributes parentAttrs;

        XGetWindowAttributes(_display, _parent, &parentAttrs);

        parentWidth = parentAttrs.width;
        parentHeight = parentAttrs.height;
    } else {
        parentWidth = _parentDrawable->_width;
        parentHeight = _parentDrawable->_height;
    }
    
    _anchorage.flags = flags;

    if (flags & (int) AnchorageFlags::Left)
        _anchorage.xOffset = _x;
    else if (flags & (int) AnchorageFlags::Right)
        _anchorage.xOffset = parentWidth - _width - _x;
    
    if (flags & (int) AnchorageFlags::Top)
        _anchorage.yOffset = _y;
    else if (flags & (int) AnchorageFlags::Bottom)
        _anchorage.yOffset = parentHeight - _height - _y;
}

void Ui::DrawableObject::applyAnchorage() {
    if (_anchorage.flags) {
        int parentWidth, parentHeight;

        if ((_anchorage.flags & (int) AnchorageFlags::ParentBase) == 0) {
            XWindowAttributes parentAttrs;

            XGetWindowAttributes(_display, _parent, &parentAttrs);

            parentWidth = parentAttrs.width;
            parentHeight = parentAttrs.height;
        } else {
            parentWidth = _parentDrawable->_width;
            parentHeight = _parentDrawable->_height;
        }
    
        int x, y;

        if (_anchorage.flags & (int) AnchorageFlags::Left)
            x = _anchorage.xOffset;
        else if (_anchorage.flags & (int) AnchorageFlags::Right)
            x = parentWidth - _anchorage.xOffset - _width;
        else if (_anchorage.flags & (int) AnchorageFlags::ParentBase)
            x = _parentDrawable->_x + _anchorage.xOffset;
        else
            x = _x;

        if (_anchorage.flags & (int) AnchorageFlags::Top)
            y = _anchorage.yOffset;
        else if (_anchorage.flags & (int) AnchorageFlags::Bottom)
            y = parentHeight - _anchorage.yOffset - _height;
        else if (_anchorage.flags & (int) AnchorageFlags::ParentBase)
            y = _parentDrawable->_y + _anchorage.yOffset;
        else
            y = _y;

        move(x, y);

        for (auto child: _childDrawables)
            child->applyAnchorage();
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

// Find a window that actually owns the drawable
// If the drawable is window the function returns its own handle
Window Ui::DrawableObject::getOwner() {

}

// Calculates both hor & ver offsets related to (0, 0) of owner window client area
// If the drawable is window the function returns 0, 0
// All anchorages are taking into account
void Ui::DrawableObject::getOwnerClientOffset(int& xOffset, int& yOffset) {

}

// Enumerates all drawables up until own window
void Ui::DrawableObject::enumDrawablesUntilOwnWindow(std::function<void(Ui::DrawableObject *)> cb) {
    Ui::DrawableObject *drawable = this;

    while (!drawable->isWindow()) {
        cb(drawable);

        drawable = drawable->_parentDrawable;
    }

    if (drawable)
        cb(drawable);
}
