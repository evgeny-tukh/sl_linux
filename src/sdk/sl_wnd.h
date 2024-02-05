#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
#include <vector>
#include <memory>

#include <X11/Xlib.h> 

namespace Ui {

class Wnd {
    public:
        enum class Property {
            X,
            Y,
            Width,
            Height,
            BorderWidth,
            BorderColor,
            BgColor,
            ActiveBgColor,
            FgColor,
            DisabledFgColor,
            TextY,
            ImageY,
            Command,
        };

        class Properties: public std::unordered_map<Property, uint32_t> {
            public:
                Properties() {}
                Properties (uint32_t x, uint32_t y, uint32_t width, uint32_t height);

                static const uint32_t UNDEFINED = 0xFFFFFFFF;
                
                uint32_t get(Property prop);

                static Properties& populate(Properties& props, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        };

        Wnd(Display *display, Properties& props, Window parent);
        Wnd(Display *display, int x, int y, int width, int height, Window parent);
        virtual ~Wnd();

        virtual void create();
        virtual void destroy();

        Window handle() const { return _wnd; }
        Display *display() const { return _display; }

        void selectInput(long mask) const;

        void show(bool showFlag) const;

        void eventLoop(std::function<bool(Wnd& wnd, XEvent&)> cb);

        void forceRedraw();

        Wnd *addChild(uint16_t id, std::shared_ptr<Wnd> wnd);
        Wnd *findChildByHandle(Window handle) const;
        Wnd *findChildById(uint16_t id) const;
        
    protected:
        Window _wnd;
        Window _parent;
        Display *_display;
        unsigned long _bgClr;
        unsigned long _borderClr;
        int _bordwerWidth;
        int _width;
        int _height;
        int _x;
        int _y;
        std::unordered_map<uint16_t, std::shared_ptr<Wnd>> _children;

        virtual uint32_t getDefaultPropValue(Property prop);

        virtual void onConfigurationChanged(XConfigureEvent& evt);
        virtual void onPaint(XExposeEvent& evt);
        virtual void onButtonPress(XButtonPressedEvent& evt) {}
        virtual void onButtonRelease(XButtonReleasedEvent& evt) {}
        virtual void onMouseEnter(XCrossingEvent& evt) {}
        virtual void onMouseLeave(XCrossingEvent& evt) {}

        virtual void paint(GC ctx) const;

        void textOut(int x, int y, GC ctx, const char *txt) const;
};

}
