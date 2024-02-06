#include "sl_img_button.h"

Ui::ImgButton::ImgButton(Ui::Wnd& parent, const std::string& folder, uint16_t cmd, int x, int y, int width, int height):
    Ui::Button(cmd, nullptr, x, y, width, height, parent) {
    _bordwerWidth = 0;
    loadImage(Ui::Button::ImageIndex::Pressed, folder + "/pressed.bmp");
    loadImage(Ui::Button::ImageIndex::Normal, folder + "/normal.bmp");
    loadImage(Ui::Button::ImageIndex::Disabled, folder + "/disabled.bmp");
    loadImage(Ui::Button::ImageIndex::Hovered, folder + "/hovered.bmp");
}
