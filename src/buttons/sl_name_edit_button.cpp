#include "sl_name_edit_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/bin/res/buttonImages/name"};
const std::string NORMAL {"normal.bmp"};
const int WIDTH = 100;
const int HEIGHT = 100;
const int BORDER_EDGE = 2;
const char BUT_TEXT[] {"NAME"};
const std::string DEF_FONT_NAME{/*"*8x13*"*/"*12x24*"};
}

NameEditButton::NameEditButton(Ui::Wnd& parent, int x, int y): 
    Ui::Button((uint16_t) Ui::Resources::ToggleName, BUT_TEXT, x, y, WIDTH, HEIGHT, parent) {
    _whiteClr = Ui::Util::allocateColor(255, 255, 255, parent.display());
    _blackClr = Ui::Util::allocateColor(0, 0, 0, parent.display());
    _activeBgClr = _whiteClr;
    _bgClr = _blackClr;
    _disabledFgClr = Ui::Util::allocateColor(100, 100, 100, parent.display());
    _fgClr = _blackClr;
    _borderClr = _whiteClr;
    _bordwerWidth = 0;
}

void NameEditButton::loadImages() {
    loadImage(Ui::Button::ImageIndex::Normal, FOLDER + NORMAL);
}

const std::string& NameEditButton::getFontName() const {
    return DEF_FONT_NAME;
}

int NameEditButton::getTextY() const {
    return 30;
}

int NameEditButton::getImageY() const {
    return _height >> 1;
}

void NameEditButton::paint(GC ctx) const {
    XSetForeground(_display, ctx, _whiteClr);
    XSetBackground(_display, ctx, _whiteClr);
    //XDrawRectangle(display(), handle(), ctx, BORDER_EDGE, BORDER_EDGE, _width - BORDER_EDGE * 2, _height - BORDER_EDGE * 2);
    Ui::Util::fillRondedRect(_display, _wnd, ctx, 0, 0, _width, _height, 15);
    drawText(ctx, false);
    XSetBackground(_display, ctx, _blackClr);
    Ui::Util::fillRondedRect(_display, _wnd, ctx, 1, _height - 31, _width - 2, 30, 15);
    XFillRectangle(_display, _wnd, ctx, 1, 40, _width - 3, _height - 55);
    drawImage(ctx);

    //Ui::Button::paint(ctx);
}