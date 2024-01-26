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

void Ui::Button::paint(GC ctx) const {
    if (_status & (int) ButtonStatus::Text) {
        XFontStruct *font = XLoadQueryFont(_display, "*7x14*");
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
        XDrawString(_display, _wnd, ctx, (_width - textWidth) >> 1, (_height >> 1) + 5, _text.c_str(), _text.length());
        XUnloadFont(_display, font->fid);
    } else if (_status & (int) ButtonStatus::Image) {
        Bitmap *bmp;
        if (_status & (int) ButtonStatus::Disabled) {
            if (_disabledImg)
                bmp = _disabledImg.get();
            else if (_normalImg)
                bmp = _normalImg.get();
            else
                bmp = nullptr;
        } else if (_status & (int) ButtonStatus::Pressed) {
            if (_pressedImg)
                bmp = _pressedImg.get();
            else if (_hoveredImg)
                bmp = _hoveredImg.get();
            else if (_normalImg)
                bmp = _normalImg.get();
            else
                bmp = nullptr;
        } else if (_status & (int) ButtonStatus::Hovered) {
            if (_hoveredImg)
                bmp = _hoveredImg.get();
            else if (_normalImg)
                bmp = _normalImg.get();
            else
                bmp = nullptr;
        } else if (_normalImg) {
            bmp = _normalImg.get();
        } else {
            bmp = nullptr;
        }
            
        if (bmp)
            bmp->putTo(*this, 0, 0, 0, 0, ctx);
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

void Ui::Button::loadImage(ImageType imgType, const char *path) {
    std::unique_ptr<Bitmap> *bmp;
    switch (imgType) {
        case ImageType::Normal:
            _normalImg.reset(new Ui::Bitmap(*this));
            
            if (_normalImg->loadBmpFile(path))
                _status |= (int) Button::ButtonStatus::Image;    
            
            break;
        case ImageType::Disabled:
            _disabledImg.reset(new Ui::Bitmap(*this));
            _disabledImg->loadBmpFile(path);
            break;
        case ImageType::Hovered:
            _hoveredImg.reset(new Ui::Bitmap(*this));
            _hoveredImg->loadBmpFile(path);
            break;
        case ImageType::Pressed:
            _pressedImg.reset(new Ui::Bitmap(*this));
            _pressedImg->loadBmpFile(path);
            break;
        default:
            return;
    }
}

