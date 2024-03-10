#include "sl_range_red_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/range"};
const char BUT_TEXT[] {"RANGE -"};
}

RangeReduceButton::RangeReduceButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, 0, 0) {
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Bottom, UiButtonsLayout::THIRD_COL_RIGHT, UiButtonsLayout::THIRD_ROW_BOTTOM);
}
