#include "sl_name_edit_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/name"};
const char BUT_TEXT[] {"NAME"};
}

NameEditButton::NameEditButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, 0, 0) {
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::FIFTH_COL_RIGHT, UiButtonsLayout::TOP_ROW_Y);
}
