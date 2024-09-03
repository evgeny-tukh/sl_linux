#pragma once

#include <string>

#include "sl_drawable.h"

namespace Ui {

class Text: public DrawableObject {
    public:
        enum class Alignment {
            Left = 1,
            HCenter = 2,
            Right = 4,
            Top = 8,
            VCenter = 16,
            Bottom = 32,
            Center = HCenter + VCenter,
            LeftTop = Left + Top,
            RightTop = Right + Top,
            CenterTop = HCenter + Top,
            LeftBottom = Left + Bottom,
            RightBottom = Right + Bottom,
            CenterBottom = HCenter + Bottom,
            LeftMiddle = Left + VCenter,
            RightMiddle = Right + VCenter,
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
            bool transparent = true,
            bool border = false
        );
        Text(
            Display *display,
            const char *text,
            int x,
            int y,
            int width,
            int height,
            DrawableObject *parent,
            int alignment = (int) Alignment::HCenter | (int) Alignment::VCenter,
            const char *fontName = "",
            bool transparent = true,
            bool border = false
        );

        void setFgColor(unsigned long color) { _fgClr = color; }
        unsigned long fgColor() const { return _fgClr; }

        void setFontName(const char *fontName) { _fontName = fontName; }

        void setBorder(bool enable) { _border = enable; }
        void setAlignment(int mask) { _alignment = mask; }

        void paint(GC ctx) override;

    protected:
        std::string _text;
        unsigned long _fgClr;
        std::string _fontName;
        int _alignment;
        bool _transparent;
        bool _border;

        const std::string& getFontName() const override;

        virtual std::string getText() const { return _text; }

        bool isAlignedTo(Alignment alignment) const { return (_alignment & (int) alignment) != 0; }
};

}
