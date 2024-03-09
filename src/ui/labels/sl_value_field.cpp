#include <sl_util.h>
#include "sl_value_field.h"

namespace {
    const char FONT_NAME[] {"*12x24*"};
}

ValueField::ValueField(Display *display, Getter getter, int x, int y, int width, int height, Window parent, Painter painter):
    Ui::Text(display, "", x, y, width,  height, parent, (int) Text::Alignment::Center, FONT_NAME),
    _getter(getter),
    _painter(painter) {

    auto whiteClr = Ui::Util::allocateColor(255, 255, 255, display);
    setFgColor(whiteClr);
    setStyle(Style::Border, true);
}

void ValueField::updateUi() {
    _text = _getter();
}

void ValueField::paint(GC ctx) const {
    if (_painter) {
        _painter(ctx);
    } else {
        Ui::Text::paint(ctx);

        if (styleFlag(Style::Border))
            Ui::Util::drawRondedRect(_display, _parent, ctx, _x, _y, _width, _height, 5);
    }
}