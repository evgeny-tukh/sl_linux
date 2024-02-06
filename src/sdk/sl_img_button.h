#pragma once

#include <string>

#include "sl_button.h"

namespace Ui {

class ImgButton: public Ui::Button {
    public:
        ImgButton(Ui::Wnd& parent, const std::string& folder, uint16_t cmd, int x, int y, int width, int height);
};

}