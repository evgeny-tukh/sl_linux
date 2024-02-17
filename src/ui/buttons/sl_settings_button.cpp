#include "sl_settings_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/settings"};
const char BUT_TEXT[] {"SETTINGS"};
}

SettingsButton::SettingsButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, 0, 0) {
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::FIRST_COL_RIGHT, UiButtonsLayout::TOP_ROW_Y);
}
