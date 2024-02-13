#include "sl_text.h"

Ui::Text::Text(Display *display, const char *text, int x, int y, int width, int height, Window parent, int alignment, const char *fontName, bool transparent):
    Ui::DrawableObject(display, x, y, width, height, parent),
    _transparent(transparent),
    _fontName(fontName),
    _alignment(alignment) {
}

void Ui::Text::paint(GC ctx) const {
    XFontStruct *font = XLoadQueryFont(_display, getFontName().c_str());
    int textWidth = XTextWidth(font, _text.c_str(), _text.length());
    XSetFont(_display, ctx, font->fid);
    if (_transparent) {
        XSetForeground(_display, ctx, bgColor());
        XFillRectangle(_display, _parent, ctx, _x, _y, _width, _height);
    }
    
    XSetForeground(_display, ctx, fgColor());
    XDrawString(_display, _parent, ctx, _x, _y, _text.c_str(), _text.length());
    XUnloadFont(_display, font->fid);
}

const std::string& Ui::Text::getFontName() const {
    if (!_fontName.empty())
        return _fontName;

    return DrawableObject::getDefaultFontName();
}
