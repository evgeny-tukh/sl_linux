#include "sl_settings_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/settings"};
const char BUT_TEXT[] {"SETTINGS"};
const int Y = 30;
const int RIGHT_OFFSET = 400;
}

SettingsButton::SettingsButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, parent.width() - RIGHT_OFFSET, Y) {
}
