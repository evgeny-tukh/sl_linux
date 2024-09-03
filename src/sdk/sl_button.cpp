#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include "sl_button.h"
#include "sl_event.h"

Ui::Button::Button(uint16_t id, const char *text, Properties& props, Wnd& parent):
    Ui::Button::Button(id, text, parent.display(), props, parent.handle()) {
    if (text && *text)
        setStatusFlag(ButtonStatus::Text);
}

Ui::Button::Button(uint16_t id, const char *text, int x, int y, int width, int height, Wnd& parent):
    Ui::Button::Button(id, text, parent.display(), x, y, width, height, parent.handle()) {
    if (text && *text)
        setStatusFlag(ButtonStatus::Text);
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
        setStatusFlag(ButtonStatus::Text);
}

Ui::Button::Button(uint16_t id, const char *text, Display *display, int x, int y, int width, int height, Window parent):
    Ui::Wnd::Wnd(display, x, y, width, height, parent),
    _id(id),
    _text(text ? text : ""),
    _status((int) ButtonStatus::Default),
    _handler(Event::defEventHandler) {
    if (text && *text)
        setStatusFlag(ButtonStatus::Text);
}

void Ui::Button::enable(bool enableFlag) {
    if (enableFlag)
        clearStatusFlag(ButtonStatus::Disabled);
    else
        setStatusFlag(ButtonStatus::Disabled);

    forceRedraw();
}

void Ui::Button::create() {
    Ui::Wnd::create();
    selectInput(ButtonPressMask|ButtonReleaseMask|EnterWindowMask|LeaveWindowMask);
    loadImages();
}

void Ui::Button::onButtonPress(XButtonPressedEvent& evt) {
    if (!getStatusFlag(ButtonStatus::Disabled)) {
        setStatusFlag(ButtonStatus::Pressed);

        if (getStatusFlag(ButtonStatus::Image))
            forceRedraw();
    }
}

void Ui::Button::onButtonRelease(XButtonReleasedEvent& evt) {
    if (!getStatusFlag(ButtonStatus::Disabled)) {
        if (getStatusFlag(ButtonStatus::Checkable)) {
            if (canBeToggled())
                toggle();
        }
        
        clearStatusFlag(ButtonStatus::Pressed);

        if (getStatusFlag(ButtonStatus::Image))
            forceRedraw();

        Ui::Event butEvt(Event::Type::Command, _handler);
        butEvt.id = _id;
        pushEvent(butEvt);
    }
}

void Ui::Button::connect(Event::EventHandler handler) {
    _handler = handler;
}

int Ui::Button::getTextY() const {
    return (_height >> 1) + 5;
}

int Ui::Button::getImageX(const BmpPtr&) const {
    return 0;
}

int Ui::Button::getImageY(const BmpPtr&) const {
    return 0;
}

void Ui::Button::drawText(GC ctx, bool fillBgRect) const {
    XFontStruct *font = XLoadQueryFont(_display, getFontName().c_str());
    int textWidth = XTextWidth(font, _text.c_str(), _text.length());
    XSetFont(_display, ctx, font->fid);
    unsigned long fg, bg;
    if (!getStatusFlag(ButtonStatus::Hovered))
        bg = getBgColor();
    else
        bg = getActiveBgColor();
    if (!getStatusFlag(ButtonStatus::Disabled))
        fg = getFgColor();
    else
        fg = getDisabledFgColor();

    if (fillBgRect) {
        XSetForeground(_display, ctx, bg);
        XFillRectangle(_display, _wnd, ctx, _bordwerWidth, _bordwerWidth, _width - _bordwerWidth * 2, _height - _bordwerWidth * 2);
    }
    
    auto text = getText();

    XSetForeground(_display, ctx, fg);
    XDrawString(_display, _wnd, ctx, (_width - textWidth) >> 1, getTextY(), text.c_str(), text.length());
    XUnloadFont(_display, font->fid);
}

void Ui::Button::drawImage(GC ctx) const {
    const BmpPtr& bmp = getImage();
        
    if (bmp)
        bmp->putTo(*this, getImageX(bmp), getImageY(bmp), 0, 0, ctx);
}

void Ui::Button::paint(GC ctx) {
    if (getStatusFlag(ButtonStatus::Text)) {
        drawText(ctx);
    }
    
    if (getStatusFlag(ButtonStatus::Image)) {
        drawImage(ctx);
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
    const BmpPtr& checkedNormalImg = getImage(ImageIndex::CheckedNormal);
    const BmpPtr& checkedHoveredImg = getImage(ImageIndex::CheckedHovered);
    const BmpPtr& checkedPressedImg = getImage(ImageIndex::CheckedPressed);

    bool checkable = getStatusFlag(ButtonStatus::Checkable);
    bool checked = checkable ? getStatusFlag(ButtonStatus::Checked) : false;

    if (getStatusFlag(ButtonStatus::Disabled)) {
        if (disabledImg)
            return disabledImg;
        else if (normalImg)
            return checked ? checkedNormalImg : normalImg;
        else
            return _noImage;
    } else if (getStatusFlag(ButtonStatus::Pressed)) {
        if (pressedImg)
            return checked ? checkedPressedImg : pressedImg;
        else if (hoveredImg)
            return checked ? checkedHoveredImg : hoveredImg;
        else if (normalImg)
            return checked ? checkedNormalImg : normalImg;
    } else if (getStatusFlag(ButtonStatus::Hovered)) {
        if (hoveredImg)
            return checked ? checkedHoveredImg : hoveredImg;
        else if (normalImg)
            return checked ? checkedNormalImg : normalImg;
    } else if (normalImg) {
        return checked ? checkedNormalImg : normalImg;
    }
        
    return _noImage;
}

void Ui::Button::loadImage(int imgType, const char *path) {
    BmpPtr bmp;
    bmp.reset(new Ui::Bitmap(*this));
    
    bmp->loadBmpFile(path);

    setStatusFlag(Button::ButtonStatus::Image);

    auto pos = _images.find(imgType);

    if (pos == _images.end())
        _images.emplace(std::pair<int, BmpPtr>(imgType, std::move(bmp)));
    else
        pos->second.swap(bmp);
}

void Ui::Button::setStatusFlag(ButtonStatus flag) {
    _status |= (int) flag;
}

void Ui::Button::clearStatusFlag(ButtonStatus flag) {
    _status &= ~((int) flag);
}

bool Ui::Button::getStatusFlag(ButtonStatus flag) const {
    return (_status & (int) flag) != 0;
}

void Ui::Button::setCheckable(bool flag) {
    if (flag)
        setStatusFlag(ButtonStatus::Checkable);
    else
        clearStatusFlag(ButtonStatus::Checkable);
}

bool Ui::Button::checkable() {
    return getStatusFlag(ButtonStatus::Checkable);
}

void Ui::Button::setChecked(bool flag) {
    if (flag)
        setStatusFlag(ButtonStatus::Checked);
    else
        clearStatusFlag(ButtonStatus::Checked);
}

bool Ui::Button::checked() {
    return getStatusFlag(ButtonStatus::Checked);
}

void Ui::Button::toggle() {
    if (getStatusFlag(ButtonStatus::Checked))
        clearStatusFlag(ButtonStatus::Checked);
    else
        setStatusFlag(ButtonStatus::Checked);
}

