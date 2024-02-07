#include "sl_light_on_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/light"};
const char BUT_TEXT[] {"LIGHT ON"};
const int BOTTOM_OFFSET = 400;
const int RIGHT_OFFSET = 250;
}

LightOnButton::LightOnButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, parent.width() - RIGHT_OFFSET, parent.height() - BOTTOM_OFFSET) {
}
