#pragma once

#include <X11/Xlib.h> 

#include <cstdint>
#include <string>
#include <memory>

#include "sl_wnd.h"
#include "sl_bitmap.h"

namespace Ui {

class ImageHolder: public Wnd {
    public:
        ImageHolder(Properties& props, Wnd& parent);
        ImageHolder(Display *display, Properties& props, Window parent);
        ImageHolder(int x, int y, int width, int height, Wnd& parent);
        ImageHolder(Display *display, int x, int y, int width, int height, Window parent);
        virtual ~Button() {}

        void create() override;

        void connect(Event::EventHandler handler);

        void enable(bool enableFlag);

        void loadImage(ImageType imgType, const char *path);
        void loadImage(ImageType imgType, const std::string path) { loadImage(imgType, path.c_str()); }

    protected:
        unsigned long _activeBgClr;
        unsigned long _fgClr;
        unsigned long _disabledFgClr;
        std::string _text;
        int _status;
        uint16_t _id;
        Event::EventHandler _handler;
        std::unique_ptr<Bitmap> _normalImg;
        std::unique_ptr<Bitmap> _hoveredImg;
        std::unique_ptr<Bitmap> _pressedImg;
        std::unique_ptr<Bitmap> _disabledImg;

        void onButtonPress(XButtonPressedEvent& evt) override;
        void onButtonRelease(XButtonReleasedEvent& evt) override;
        void onMouseEnter(XCrossingEvent& evt) override;
        void onMouseLeave(XCrossingEvent& evt) override;

        void paint(GC ctx) override;
};

}
