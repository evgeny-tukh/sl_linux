#include "sl_labeled_value.h"

namespace {
const int LABEL_HEIGHT = 35;
const int FIELD_HEIGHT = 35;
const int WIDTH = 100;
}

LabeledValue::LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent):
    LabeledValue(display, label, valueGetter, x, y, parent, WIDTH) {    
}

LabeledValue::LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent, int width):
    LabeledValue(display, label, valueGetter, x, y, parent, width, LABEL_HEIGHT + FIELD_HEIGHT) {
}


LabeledValue::LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent, int width, int height):
    Ui::DrawableObject(display, x, y, width, height, parent),
    _label(display, label, x, y, width, LABEL_HEIGHT, parent),
    _field(display, valueGetter, x, y + LABEL_HEIGHT, width, height - LABEL_HEIGHT, parent) {
    _label.setParentDrawableObject(this);
    _field.setParentDrawableObject(this);
    addChildDrawableObject(&_label);
    addChildDrawableObject(&_field);
}

void LabeledValue::setupLayout(int xOffset, int yOffset) {
    applyAnchorage();
    _label.setAnchorage(AnchorageFlags::ParentBase, xOffset, yOffset);
    _label.applyAnchorage();
    _field.setAnchorage(AnchorageFlags::ParentBase, xOffset, yOffset + LABEL_HEIGHT);
    _field.applyAnchorage();
    _field.setBgColor(0);
}

void LabeledValue::paint(GC ctx) {
    _label.paint(ctx);
    _field.paint(ctx);
}

void LabeledValue::updateUi() {
    applyAnchorage();
    _field.updateUi();
}

void LabeledValue::show(bool showFlag) {
    Ui::DrawableObject::show(showFlag);
    _label.show(showFlag);
    _field.show(showFlag);
}

