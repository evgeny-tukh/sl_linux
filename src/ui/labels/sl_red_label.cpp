#include <sl_util.h>
#include "sl_red_label.h"

namespace {
    const char FONT_NAME[] {"*12x24*"};
}

RedLabel::RedLabel(Display *display, const char *text, int x, int y, int width, int height, Window parent):
    Ui::Text(display, text, x, y, width,  height, parent, (int) Text::Alignment::LeftMiddle, FONT_NAME) {

    auto redClr = Ui::Util::allocateColor(255, 0, 0, display);
    setFgColor(redClr);
}
