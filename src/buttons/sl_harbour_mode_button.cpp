#include "sl_harbour_mode_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/harbour_mode"};
const char BUT_TEXT[] {"HRB MODE"};
const int Y = 30;
const int RIGHT_OFFSET = 250;
}

HarbourModeButton::HarbourModeButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, parent.width() - RIGHT_OFFSET, Y) {
}
