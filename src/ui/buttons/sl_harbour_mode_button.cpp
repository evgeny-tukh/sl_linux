#include "sl_harbour_mode_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/sound"};
const char BUT_TEXT[] {"HRB MODE"};
}

HarbourModeButton::HarbourModeButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, 0, 0) {
    setCheckable(true);
    setChecked(false);
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::FOURTH_COL_RIGHT, UiButtonsLayout::TOP_ROW_Y);
}
