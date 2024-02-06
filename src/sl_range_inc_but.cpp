#include "sl_range_inc_but.h"
#include "sl_res.h"

namespace {

const int BUT_WIDTH = 250;
const int BUT_HEIGHT = 109;
const int BUT_X = 800 - BUT_WIDTH - 10;
const int BUT_Y = 10;
}

RangeIncButton::RangeIncButton(Ui::Wnd& parent):
    Ui::ImgButton(parent, "/home/jeca/work/sl/bin/res/Range +", (uint16_t) Ui::Resources::DecreaseRange, BUT_X, BUT_Y, BUT_WIDTH, BUT_HEIGHT) {
}
