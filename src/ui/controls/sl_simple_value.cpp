#include <sl_util.h>
#include "sl_simple_value.h"

namespace {
const int FLD_HEIGHT = 35;
const int EDGE = 5;
const int CTL_HEIGHT = FLD_HEIGHT + EDGE * 2;
}

SimpleValue::SimpleValue(Display *display, ValueField::Getter valueGetter, int x, int y, int width, int height, Window parent):
    Ui::DrawableObject(display, x, y, width, CTL_HEIGHT, parent),
    _field(display, valueGetter, x, y, width, height, parent) {
    _field.setParentDrawableObject(this);
    addChildDrawableObject(&_field);
}

void SimpleValue::setupLayout(int xOffset, int yOffset) {
    applyAnchorage();
    _field.setAnchorage(AnchorageFlags::ParentBase, EDGE, yOffset + EDGE);
    _field.applyAnchorage();
}

void SimpleValue::paint(GC ctx) {
    _field.paint(ctx);

    //Ui::Util::drawRondedRect(_display, _parent, ctx, _x, _y, _width, _height, 5);
}

void SimpleValue::updateUi() {
    applyAnchorage();
    _field.updateUi();
}

void SimpleValue::show(bool showFlag) {
    Ui::DrawableObject::show(showFlag);
    _field.show(showFlag);
}

