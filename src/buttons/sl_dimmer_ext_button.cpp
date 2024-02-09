#include "sl_dimmer_ext_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/dimmer"};
const char BUT_TEXT[] {"DIMMER +"};
}

DimmerExtendButton::DimmerExtendButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, 0, 0) {
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Bottom, UiButtonsLayout::THIRD_COL_RIGHT, UiButtonsLayout::SECOND_ROW_BOTTOM);
}
