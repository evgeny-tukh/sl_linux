#pragma once

#include <string>

#include "sl_button.h"

class UiButton: public Ui::Button {
    public:
        UiButton(Ui::Wnd& parent, const std::string& folder, uint16_t cmd, int x, int y, int width, int height);
};
