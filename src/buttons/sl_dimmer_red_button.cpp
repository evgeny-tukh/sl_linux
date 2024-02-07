#include "sl_dimmer_red_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/dimmer"};
const char BUT_TEXT[] {"DIMMER +"};
const int BOTTOM_OFFSET = 250;
const int RIGHT_OFFSET = 100;
}

DimmerReduceButton::DimmerReduceButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, parent.width() - RIGHT_OFFSET, parent.height() - BOTTOM_OFFSET) {
}
