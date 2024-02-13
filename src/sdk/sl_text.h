#pragma once

#include <string>

#include "sl_drawable.h"

namespace Ui {

class Text: public DrawableObject {
    public:
        enum class Alignment {
            Left,
            HCenter,
            Right,
            Top,
            VCenter,
            Bottom,
        };

        Text(
            Display *display,
            const char *text,
            int x,
            int y,
            int width,
            int height,
            Window parent,
            int alignment = (int) Alignment::HCenter | (int) Alignment::VCenter,
            const char *fontName = "",
            bool transparent = true
        );

        void setFgColor(unsigned long color) { _fgClr = color; }
        unsigned long fgColor() const { return _fgClr; }

        void setFontName(const char *fontName) { _fontName = fontName; }

    protected:
        std::string _text;
        unsigned long _fgClr;
        std::string _fontName;
        int _alignment;
        bool _transparent;

        const std::string& getFontName() const override;

        void paint(GC ctx) const override;
};

}
