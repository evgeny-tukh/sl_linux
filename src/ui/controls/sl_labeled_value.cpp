#include "sl_labeled_value.h"

LabeledValue::LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent, int width):
    Ui::DrawableObject(display, x, y, width, 100, parent),
    _label(display, label, x, y, width, 50, parent),
    _field(display, valueGetter, x, y + 50, width, 50, parent) {

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

