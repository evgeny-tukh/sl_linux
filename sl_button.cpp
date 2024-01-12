#include <stdlib.h>
#include <stdio.h>

#include "sl_button.h"
#include "sl_event.h"

Ui::Button::Button(uint16_t id, const char *text, Display *display, Properties& props, Window parent):
    Ui::Wnd::Wnd(display, props, parent),
    _id(id),
    _text(text),
    _status((int) ButtonStatus::Default),
    _activeBgClr(props.get(Wnd::Property::ActiveBgColor)),
    _fgClr(props.get(Wnd::Property::FgColor)),
    _disabledFgClr(props.get(Wnd::Property::DisabledFgColor)),
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
    if ((_status & (int) ButtonStatus::Disabled) == 0)
        _status |= (int) ButtonStatus::Pressed;
}

void Ui::Button::onButtonRelease(XButtonReleasedEvent& evt) {
    if ((_status & (int) ButtonStatus::Disabled) == 0) {
        _status &= ~((int) ButtonStatus::Pressed);

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

