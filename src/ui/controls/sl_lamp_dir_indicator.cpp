#include <sl_util.h>
#include "sl_lamp_dir_indicator.h"

namespace {
const int WIDTH = 140;
const int LBL_WIDTH = 40;
const int HEIGHT = 35;
}

LampDirIndicator::LampDirIndicator(Display *display, ValueField::Getter valueGetter, int x, int y, int lampIndex, Window parent):
    Ui::DrawableObject(display, x, y, WIDTH, HEIGHT, parent),
    _label(display, [lampIndex] () { return std::to_string(lampIndex + 1); }, x, y, LBL_WIDTH, HEIGHT, parent),
    _value(display, valueGetter, x + LBL_WIDTH, y, WIDTH - LBL_WIDTH, HEIGHT, parent),
    _lampIndex(lampIndex) {
    _label.setStyle(ValueField::Style::Border, false);
    _label.setParentDrawableObject(this);
    _value.setStyle(ValueField::Style::Border, false);
    _value.setParentDrawableObject(this);
    addChildDrawableObject(&_label);
    addChildDrawableObject(&_value);
}

void LampDirIndicator::setupLayout(int xParam, int yParam) {
    setAnchorage(AnchorageFlags::ParentBase, xParam, yParam);
    applyAnchorage();
    _label.setAnchorage(AnchorageFlags::ParentBase, 0 /*+ xParam, yParam*/, 0);
    _label.applyAnchorage();
    _value.setAnchorage(AnchorageFlags::ParentBase, 40 /*+ xParam, yParam*/, 0);
    _value.applyAnchorage();
}


void LampDirIndicator::show(bool showFlag) {
    _label.show(showFlag);
    _value.show(showFlag);
}

void LampDirIndicator::paint(GC ctx) {
    _label.paint(ctx);
    _value.paint(ctx);

    Ui::Util::drawRondedRect(_display, _parent, ctx, _x, _y, _width, _height, 5);
    XSetForeground(_display, ctx, _label.fgColor());
    drawLine(ctx, LBL_WIDTH, 0, LBL_WIDTH, HEIGHT - 2);
}

void LampDirIndicator::updateUi() {
    applyAnchorage();
    _label.updateUi();
    _value.updateUi();
}

int LampDirIndicator::getLampIndicatorWidth() {
    return WIDTH;
}

int LampDirIndicator::getLampIndicatorHeight() {
    return HEIGHT;
}
