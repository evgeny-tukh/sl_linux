#pragma once

#include <sdk/sl_text.h>

class RedLabel: public Ui::Text {
    public:
        RedLabel(Display *display, const char *text, int x, int y, int width, int height, Window parent);
        RedLabel(Display *display, const char *text, int x, int y, int width, int height, DrawableObject *parent);
};
