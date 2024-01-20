#include "sl_range_inc_but.h"
#include "sl_res.h"

namespace {

const int BUT_X = 10;
const int BUT_Y = 300;
const int BUT_WIDTH = 250;
const int BUT_HEIGHT = 109;

RangeIncButton::ButProperties props;

}

RangeIncButton::ButProperties::ButProperties() {
    (*this) [Ui::Wnd::Property::X] = BUT_X;
    (*this) [Ui::Wnd::Property::Y] = BUT_Y;
    (*this) [Ui::Wnd::Property::Width] = BUT_WIDTH;
    (*this) [Ui::Wnd::Property::Height] = BUT_HEIGHT;
}

RangeIncButton::RangeIncButton(Ui::Wnd& parent):
    Ui::Button((uint16_t) Ui::Resources::IncreaseRange, nullptr, props, parent) {
    loadNormalImg("/home/jeca/work/bin/res/Range +/RangePlusActivated-250x109.bmp");
}
