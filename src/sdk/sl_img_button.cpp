#include "sl_img_button.h"

UiButton::UiButton(Ui::Wnd& parent, const std::string& folder, uint16_t cmd, int x, int y, int width, int height):
    Ui::Button(cmd, nullptr, x, y, width, height, parent) {
    _bordwerWidth = 0;
    loadImage(Ui::Button::ImageType::Pressed, folder + "/pressed.bmp");
    loadImage(Ui::Button::ImageType::Normal, folder + "/normal.bmp");
    loadImage(Ui::Button::ImageType::Disabled, folder + "/disabled.bmp");
    loadImage(Ui::Button::ImageType::Hovered, folder + "/hovered.bmp");
}
