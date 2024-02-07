#include "sl_range_red_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/range"};
const char BUT_TEXT[] {"RANGE -"};
const int BOTTOM_OFFSET = 250;
const int RIGHT_OFFSET = 400;
}

RangeReduceButton::RangeReduceButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, parent.width() - RIGHT_OFFSET, parent.height() - BOTTOM_OFFSET) {
}
