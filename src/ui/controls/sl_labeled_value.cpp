#include "sl_labeled_value.h"

LabeledValue::LabeledValue(Display *display, const char *label, ValueField::Getter valueGetter, int x, int y, Window parent):
    Ui::DrawableObject(display, x, y, 100, 100, parent),
    _label(display, label, x, y, 100, 50, parent),
    _field(display, valueGetter, x, y + 50, 100, 50, parent) {

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

