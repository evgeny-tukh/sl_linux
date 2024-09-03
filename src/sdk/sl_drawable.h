#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <vector>

#include <X11/Xlib.h> 

namespace Ui {

class DrawableObject {
    public:
        enum AnchorageFlags {
            NoAnchorage = 0,
            Left = 1,
            Top = 2,
            Right = 4,
            Bottom = 8,
            ParentBase = 16,
            FitLeft = 32,
        };

        struct Anchorage {
            int flags;
            int xOffset;
            int yOffset;
            int xMax;
            int yMax;

            Anchorage(): flags(0), xOffset(0), yOffset(0) {}
        };

        static const std::string& getDefaultFontName();

        Window parent() const;
        
        DrawableObject(Display *display, int x, int y, int width, int height, Window parent);
        DrawableObject(Display *display, int x, int y, int width, int height, DrawableObject *parent);

        void setBgColor(unsigned long color) { _bgClr = color; }
        unsigned long bgColor() const { return _bgClr; }
        
        void setAnchorage(int flags, int xOffset, int yOffset, int xMax = 0, int yMax = 0);
        void setAnchorage(int flags);
        void applyAnchorage();

        int width() const { return _width; }
        int height() const { return _height; }

        virtual void resize(uint16_t width, uint16_t height);
        virtual void move(int x, int y);

        virtual void show(bool showFlag) { _visible = showFlag; }

        virtual void onParentSizeChanged(int width, int height) {}

        virtual void onMouseEnter(XCrossingEvent& evt) {}
        virtual void onMouseLeave(XCrossingEvent& evt) {}

        virtual bool isWindow() const { return false; }

        virtual void paint(GC ctx) {}

        virtual void updateUi() {}

        uint32_t style() const { return _style; }
        bool styleFlag(uint32_t mask) const;
        void setStyle(uint32_t mask, uint32_t value);
        void setStyle(uint32_t mask, bool flag);

        void drawLine(GC ctx, int x1, int y1, int x2, int y2) const;

        void addChildDrawableObject (DrawableObject *child);
        void setParentDrawableObject (DrawableObject *parent);

        virtual void setupLayout(int xParam = 0, int yParam = 0) {}

    protected:
        Window _parent;
        Display *_display;
        DrawableObject *_parentDrawable;
        unsigned long _bgClr;
        uint32_t _style;
        int _width;
        int _height;
        int _x;
        int _y;
        bool _visible;
        Anchorage _anchorage;
        std::vector<DrawableObject *> _childDrawables;

        // Find a window that actually owns the drawable
        // If the drawable is window the function returns its own handle
        Window getOwner();

        // Calculates both hor & ver offsets related to (0, 0) of owner window client area
        // If the drawable is window the function returns 0, 0
        // All anchorages are taking into account
        void getOwnerClientOffset(int& xOffset, int& yOffset);

        // Enumerates all drawables up until own window
        void enumDrawablesUntilOwnWindow(std::function<void(DrawableObject *)>);

        virtual const std::string& getFontName() const;
};

}
