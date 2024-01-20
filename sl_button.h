#pragma once

#include <X11/Xlib.h> 

#include <cstdint>
#include <string>
#include <memory>

#include "sl_wnd.h"
#include "sl_event.h"
#include "sl_button.h"
#include "sl_bitmap.h"

namespace Ui {

class Button: public Wnd {
    public:
        Button(uint16_t id, const char *text, Properties& props, Wnd& parent);
        Button(uint16_t id, const char *text, Display *display, Properties& props, Window parent);
        virtual ~Button() {}

        enum class ButtonStatus: int {
            Default = 0,
            Pressed = 1,
            Hovered = 2,
            Disabled = 4,
            Text = 8,
            Image = 16,
        };

        void create() override;

        void connect(Event::EventHandler handler);

        void enable(bool enableFlag);

        void loadNormalImg(const char *path);
        void loadPressedImg(const char *path);
        void loadHoveredImg(const char *path);

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

        void onButtonPress(XButtonPressedEvent& evt) override;
        void onButtonRelease(XButtonReleasedEvent& evt) override;
        void onMouseEnter(XCrossingEvent& evt) override;
        void onMouseLeave(XCrossingEvent& evt) override;

        void paint(GC ctx) const override;
};

}
