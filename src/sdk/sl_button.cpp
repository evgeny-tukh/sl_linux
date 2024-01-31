#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include "sl_button.h"
#include "sl_event.h"

Ui::Button::Button(uint16_t id, const char *text, Properties& props, Wnd& parent):
    Ui::Button::Button(id, text, parent.display(), props, parent.handle()) {
    if (text && *text)
        _status |= (int) ButtonStatus::Text;
}

Ui::Button::Button(uint16_t id, const char *text, int x, int y, int width, int height, Wnd& parent):
    Ui::Button::Button(id, text, parent.display(), x, y, width, height, parent.handle()) {
    if (text && *text)
        _status |= (int) ButtonStatus::Text;
}

Ui::Button::Button(uint16_t id, const char *text, Display *display, Properties& props, Window parent):
    Ui::Wnd::Wnd(display, props, parent),
    _id(id),
    _text(text ? text : ""),
    _status((int) ButtonStatus::Default),
    _activeBgClr(props.get(Wnd::Property::ActiveBgColor)),
    _fgClr(props.get(Wnd::Property::FgColor)),
    _disabledFgClr(props.get(Wnd::Property::DisabledFgColor)),
    _handler(Event::defEventHandler) {
    if (text && *text)
        _status |= (int) ButtonStatus::Text;
}

Ui::Button::Button(uint16_t id, const char *text, Display *display, int x, int y, int width, int height, Window parent):
    Ui::Wnd::Wnd(display, x, y, width, height, parent),
    _id(id),
    _text(text ? text : ""),
    _status((int) ButtonStatus::Default),
    _handler(Event::defEventHandler) {
    if (text && *text)
        _status |= (int) ButtonStatus::Text;
}

void Ui::Button::enable(bool enableFlag) {
    if (enableFlag)
        _status &= ~((int) ButtonStatus::Disabled);
    else
        _status |= (int) ButtonStatus::Disabled;

    forceRedraw();
}

void Ui::Button::create() {
    Ui::Wnd::create();
    selectInput(ButtonPressMask|ButtonReleaseMask|EnterWindowMask|LeaveWindowMask);
    loadImages();
}

void Ui::Button::onButtonPress(XButtonPressedEvent& evt) {
    if ((_status & (int) ButtonStatus::Disabled) == 0) {
        _status |= (int) ButtonStatus::Pressed;

        if (_status & (int) ButtonStatus::Image)
            forceRedraw();
    }
}

void Ui::Button::onButtonRelease(XButtonReleasedEvent& evt) {
    if ((_status & (int) ButtonStatus::Disabled) == 0) {
        _status &= ~((int) ButtonStatus::Pressed);

        if (_status & (int) ButtonStatus::Image)
            forceRedraw();

        Ui::Event butEvt(Event::Type::Command, _handler);
        butEvt.id = _id;
        pushEvent(butEvt);
    }
}

void Ui::Button::connect(Event::EventHandler handler) {
    _handler = handler;
}

const std::string& Ui::Button::getFontName() const {
    const static std::string DEF_FONT_NAME{"*7x14*"};

    return DEF_FONT_NAME;
}

int Ui::Button::getTextY() const {
    return (_height >> 1) + 5;
}

int Ui::Button::getImageY() const {
    return 0;
}

void Ui::Button::drawText(GC ctx) const {
    XFontStruct *font = XLoadQueryFont(_display, getFontName().c_str());
    int textWidth = XTextWidth(font, _text.c_str(), _text.length());
    XSetFont(_display, ctx, font->fid);
    unsigned long fg, bg;
    if ((_status & (int) ButtonStatus::Hovered) == 0)
        bg = _bgClr;
    else
        bg = _activeBgClr;
    if ((_status & (int) ButtonStatus::Disabled) == 0)
        fg = _fgClr;
    else
        fg = _disabledFgClr;
    XSetForeground(_display, ctx, bg);
    XFillRectangle(_display, _wnd, ctx, _bordwerWidth, _bordwerWidth, _width - _bordwerWidth * 2, _height - _bordwerWidth * 2);
    XSetForeground(_display, ctx, fg);
    XDrawString(_display, _wnd, ctx, (_width - textWidth) >> 1, getTextY(), _text.c_str(), _text.length());
    XUnloadFont(_display, font->fid);
}

void Ui::Button::paint(GC ctx) const {
    if (_status & (int) ButtonStatus::Text) {
        drawText(ctx);
    }
    
    if (_status & (int) ButtonStatus::Image) {
        const BmpPtr& bmp = getImage();
            
        if (bmp)
            bmp->putTo(*this, 0, getImageY(), 0, 0, ctx);
    }
}

void Ui::Button::onMouseEnter(XCrossingEvent& evt) {
    int newStatus = _status | (int) Button::ButtonStatus::Hovered;

    if (newStatus != _status) {
        _status = newStatus;
        forceRedraw();
    }
}

void Ui::Button::onMouseLeave(XCrossingEvent& evt) {
    int newStatus = _status & ~((int) Button::ButtonStatus::Hovered);

    if (newStatus != _status) {
        _status = newStatus;
        forceRedraw();
    }
}

const Ui::Button::BmpPtr& Ui::Button::getImage(int index) const {
    auto pos = _images.find(index);

    if (pos == _images.end())
        return _noImage;

    return pos->second;
}

const Ui::Button::BmpPtr& Ui::Button::getImage() const {
    const BmpPtr& normalImg = getImage(ImageIndex::Normal);
    const BmpPtr& hoveredImg = getImage(ImageIndex::Hovered);
    const BmpPtr& pressedImg = getImage(ImageIndex::Pressed);
    const BmpPtr& disabledImg = getImage(ImageIndex::Disabled);

    if (_status & (int) ButtonStatus::Disabled) {
        if (disabledImg)
            return disabledImg;
        else if (normalImg)
            return normalImg;
        else
            return _noImage;
    } else if (_status & (int) ButtonStatus::Pressed) {
        if (pressedImg)
            return pressedImg;
        else if (hoveredImg)
            return hoveredImg;
        else if (normalImg)
            return normalImg;
    } else if (_status & (int) ButtonStatus::Hovered) {
        if (hoveredImg)
            return hoveredImg;
        else if (normalImg)
            return normalImg;
    } else if (normalImg) {
        return normalImg;
    }
        
    return _noImage;
}

void Ui::Button::loadImage(int imgType, const char *path) {
    BmpPtr bmp;
    bmp.reset(new Ui::Bitmap(*this));
    
    bmp->loadBmpFile(path);

    _status |= (int) Button::ButtonStatus::Image;

    auto pos = _images.find(imgType);

    if (pos == _images.end())
        _images.emplace(std::pair<int, BmpPtr>(imgType, std::move(bmp)));
    else
        pos->second.swap(bmp);
}

