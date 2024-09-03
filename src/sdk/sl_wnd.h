#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
#include <vector>
#include <memory>

#include <X11/Xlib.h> 

#include "sl_drawable.h"

namespace Ui {

class Wnd: public DrawableObject {
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

        static std::shared_ptr<Wnd> attach(Display *display, Window wnd);

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

        void show(bool showFlag) override;

        void eventLoop(std::function<bool(Wnd& wnd, XEvent&)> cb);

        void forceRedraw();

        DrawableObject *addChild(uint16_t id, std::shared_ptr<DrawableObject> child);
        Wnd *findChildByHandle(Window handle) const;
        DrawableObject *findChildById(uint16_t id) const;

        void resize(uint16_t width, uint16_t height) override;
        void move(int x, int y) override;

        virtual bool isWindow() const { return true; }

        bool getActualSize(int& width, int& height);

    protected:
        Window _wnd;
        unsigned long _borderClr;
        int _bordwerWidth;
        int _actualWidth;
        int _actualHeight;
        std::unordered_map<uint16_t, std::shared_ptr<DrawableObject>> _children;

        virtual uint32_t getDefaultPropValue(Property prop);

        virtual void onConfigurationChanged(XConfigureEvent& evt);
        virtual void onPaint(XExposeEvent& evt);
        virtual void onButtonPress(XButtonPressedEvent& evt) {}
        virtual void onButtonRelease(XButtonReleasedEvent& evt) {}
        virtual void onParentSizeChanged(int width, int height) override;
        virtual void onSizeChanged(int width, int height, bool& notifyChildren);

        void paint(GC ctx) override;

        void textOut(int x, int y, GC ctx, const char *txt) const;
};

}
