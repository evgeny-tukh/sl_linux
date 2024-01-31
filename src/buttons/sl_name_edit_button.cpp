#include "sl_name_edit_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/bin/res/buttonImages/name"};
const std::string NORMAL {"normal.bmp"};
const int WIDTH = 100;
const int HEIGHT = 100;
}

NameEditButton::NameEditButton(Ui::Wnd& parent, int x, int y): 
    Ui::Button((uint16_t) Ui::Resources::ToggleName, "Name", x, y, WIDTH, HEIGHT, parent) {
    _activeBgClr = Ui::Util::allocateColor(255, 255, 255, parent.display());
    _bgClr = Ui::Util::allocateColor(180, 180, 180, parent.display());
    _disabledFgClr = Ui::Util::allocateColor(100, 100, 100, parent.display());
    _fgClr = Ui::Util::allocateColor(0, 0, 0, parent.display());
}

void NameEditButton::loadImages() {
    loadImage(Ui::Button::ImageIndex::Normal, FOLDER + NORMAL);
}

const std::string& NameEditButton::getFontName() const {
    const static std::string DEF_FONT_NAME{"*7x14*"/*"*12x24*"*/};

    return DEF_FONT_NAME;
}

int NameEditButton::getTextY() const {
    return 30;
}

int NameEditButton::getImageY() const {
    return _height >> 1;
}

