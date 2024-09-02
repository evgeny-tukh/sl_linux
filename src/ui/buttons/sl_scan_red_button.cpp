#include "sl_scan_red_button.h"
#include "../sdk/sl_util.h"
#include "../sl_res.h"

namespace {
const std::string FOLDER {"/home/jeca/work/sl/bin/res/buttonImages/scan"};
const char BUT_TEXT[] {"SCAN -"};
}

ScanReduceButton::ScanReduceButton(Ui::Wnd& parent): 
    UiButton(parent, FOLDER, BUT_TEXT, 0, 0) {
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Bottom, UiButtonsLayout::SECOND_COL_RIGHT, UiButtonsLayout::THIRD_ROW_BOTTOM);
}
