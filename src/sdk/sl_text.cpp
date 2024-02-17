#include "sl_text.h"

Ui::Text::Text(Display *display, const char *text, int x, int y, int width, int height, Window parent, int alignment, const char *fontName, bool transparent, bool border):
    Ui::DrawableObject(display, x, y, width, height, parent),
    _text(text),
    _transparent(transparent),
    _fontName(fontName),
    _alignment(alignment),
    _border(border) {
}

void Ui::Text::paint(GC ctx) const {
    if (_visible && !_text.empty()) {
        XFontStruct *font = XLoadQueryFont(_display, getFontName().c_str());
        if (font) {
            int textWidth = XTextWidth(font, _text.c_str(), _text.length());
            int textHeight = font->ascent + font->descent;
            XSetFont(_display, ctx, font->fid);
            
            if (!_transparent) {
                XSetForeground(_display, ctx, bgColor());
                XFillRectangle(_display, _parent, ctx, _x, _y, _width, _height);
            }

            XSetForeground(_display, ctx, fgColor());

            if (_border)
                XDrawRectangle(_display, _parent, ctx, _x, _y, _width, _height);
            
            int textX, textY;

            if (isAlignedTo(Alignment::Left))
                textX = _x;
            else if (isAlignedTo(Alignment::Right))
                textX = _x + _width - textWidth - 1;
            else if (isAlignedTo(Alignment::HCenter))
                textX = _x + ((_width - textWidth) >> 1) - 1;

            if (isAlignedTo(Alignment::Top))
                textY = _y + textHeight;
            else if (isAlignedTo(Alignment::Bottom))
                textY = _y + _height - 1;
            else if (isAlignedTo(Alignment::VCenter))
                textY = _y + _height - ((_height - textHeight) >> 1) - 1;

            XDrawString(_display, _parent, ctx, textX, textY, _text.c_str(), _text.length());
            XUnloadFont(_display, font->fid);
        }
    }
}

const std::string& Ui::Text::getFontName() const {
    if (!_fontName.empty())
        return _fontName;

    return DrawableObject::getDefaultFontName();
}
