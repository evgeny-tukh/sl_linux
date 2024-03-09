#include "sl_labeled_value.h"

namespace {
const int LABEL_HEIGHT = 40;
const int FIELD_HEIGHT = 40;
const int WIDTH = 100;
}

LabeledValue::LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent):
    LabeledValue(display, label, valueGetter, x, y, parent, WIDTH) {    
}

LabeledValue::LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent, int width):
    Ui::DrawableObject(display, x, y, width, LABEL_HEIGHT + FIELD_HEIGHT, parent),
    _label(display, label, x, y, width, LABEL_HEIGHT, parent),
    _field(display, valueGetter, x, y + LABEL_HEIGHT, width, FIELD_HEIGHT, parent) {

}

void LabeledValue::paint(GC ctx) const {
    _label.paint(ctx);
    _field.paint(ctx);
}

void LabeledValue::updateUi() {
    _field.updateUi();
}

void LabeledValue::show(bool showFlag) {
    Ui::DrawableObject::show(showFlag);
    _label.show(showFlag);
    _field.show(showFlag);
}

