#include "sl_ui_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string NORMAL {"normal.bmp"};
const std::string HOVERED {"hovered.bmp"};
const std::string PRESSED {"pressed.bmp"};
const int WIDTH = 140;
const int HEIGHT = 140;
const int BORDER_EDGE = 2;
const std::string DEF_FONT_NAME{/*"*8x13*"*/"*12x24*"};
}

UiButton::UiButton(Ui::Wnd& parent, const std::string& folder, const std::string& text, int x, int y): 
    Ui::ImgButton(parent, folder, (uint16_t) Ui::Resources::ToggleName, x, y, WIDTH, HEIGHT) {
    _text = text;
    _whiteClr = Ui::Util::allocateColor(255, 255, 255, parent.display());
    _blackClr = Ui::Util::allocateColor(0, 0, 0, parent.display());
    _redClr = Ui::Util::allocateColor(255, 0, 0, parent.display());
    _yellowClr = Ui::Util::allocateColor(255, 127, 0, parent.display());
    _activeBgClr = _whiteClr;
    _bgClr = _blackClr;
    _disabledFgClr = Ui::Util::allocateColor(100, 100, 100, parent.display());
    _fgClr = _blackClr;
    _borderClr = _whiteClr;
    _bordwerWidth = 0;
}

const std::string& UiButton::getFontName() const {
    return DEF_FONT_NAME;
}

int UiButton::getTextY() const {
    return 30;
}

int UiButton::getImageY(const BmpPtr& bmp) const {
    return (_height >> 1) - 20;
}

int UiButton::getImageX(const BmpPtr& bmp) const {
    if (!bmp)
        return 0;

    return (_height - bmp->width()) >> 1;
}

void UiButton::paint(GC ctx) {
    XSetForeground(_display, ctx, getBgColor());
    XSetBackground(_display, ctx, getBgColor());
    XSetPlaneMask(_display, ctx, AllPlanes);
    XSetFunction(_display, ctx, GXcopy);
    Ui::Util::fillRondedRect(_display, _wnd, ctx, 0, 0, _width, _height, 15);
    drawText(ctx, false);
    XSetBackground(_display, ctx, _blackClr);
    Ui::Util::fillRondedRect(_display, _wnd, ctx, 1, _height - 31, _width - 2, 30, 15);
    XFillRectangle(_display, _wnd, ctx, 1, 40, _width - 3, _height - 55);
    drawImage(ctx);
}

unsigned long UiButton::getBgColor() const {
    if (_status & (int) Ui::Button::ButtonStatus::Pressed)
        return _redClr;

    if (_status & (int) Ui::Button::ButtonStatus::Hovered)
        return _yellowClr;

    return WhitePixel(_display, DefaultScreen(_display));
}
