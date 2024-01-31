#include "sl_name_edit_button.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/bin/res/buttonImages/name"};
const std::string NORMAL {"normal.bmp"};
const int WIDTH = 100;
const int HEIGHT = 100;
}

NameEditButton::NameEditButton(Ui::Wnd& parent, int x, int y): 
    Ui::Button(Ui::Resources::ToggleName, "Name", x, y, WIDTH, HEIGHT, parent.handle()) {
}

void NameEditButton::loadImages() {
    loadImage(Ui::Button::ImageIndex::Normal, FOLDER + NORMAL);
}

const std::string& NameEditButton::getFontName() const {
    const static std::string DEF_FONT_NAME{"*12x24*"};

    return DEF_FONT_NAME;
}

int NameEditButton::getTextY() const {
    return 0;
}

int NameEditButton::getImageY() const {
    return _height >> 1;
}

