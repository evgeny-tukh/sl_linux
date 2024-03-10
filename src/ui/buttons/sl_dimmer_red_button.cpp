#include "sl_dimmer_red_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/dimmer"};
const char BUT_TEXT[] {"DIMMER +"};
}

DimmerReduceButton::DimmerReduceButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, 0, 0) {
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Bottom, UiButtonsLayout::FIFTH_COL_RIGHT, UiButtonsLayout::THIRD_ROW_BOTTOM);
}
