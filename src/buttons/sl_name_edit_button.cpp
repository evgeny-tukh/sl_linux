#include "sl_name_edit_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/name"};
const char BUT_TEXT[] {"NAME"};
const int Y = 30;
const int RIGHT_OFFSET = 100;
}

NameEditButton::NameEditButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, parent.width() - RIGHT_OFFSET, Y) {
}
