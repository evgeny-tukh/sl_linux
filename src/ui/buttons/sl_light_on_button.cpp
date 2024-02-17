#include "sl_light_on_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/light"};
const char BUT_TEXT[] {"LIGHT ON"};
}

LightOnButton::LightOnButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, 0, 0) {
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Bottom, UiButtonsLayout::SECOND_COL_RIGHT, UiButtonsLayout::SECOND_ROW_BOTTOM);
}
