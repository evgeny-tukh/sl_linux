#pragma once

#include <X11/Xlib.h> 

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>

#include "sl_wnd.h"
#include "sl_event.h"
#include "sl_button.h"
#include "sl_bitmap.h"

namespace Ui {

class Button: public Wnd {
    public:
        Button(uint16_t id, const char *text, Properties& props, Wnd& parent);
        Button(uint16_t id, const char *text, Display *display, Properties& props, Window parent);
        Button(uint16_t id, const char *text, int x, int y, int width, int height, Wnd& parent);
        Button(uint16_t id, const char *text, Display *display, int x, int y, int width, int height, Window parent);
        virtual ~Button() {}

        enum class ButtonStatus: int {
            Default = 0,
            Pressed = 1,
            Hovered = 2,
            Disabled = 4,
            Text = 8,
            Image = 16,
        };

        enum class ImageIndex: int {
            Normal = 0,
            Hovered,
            Pressed,
            Disabled,
            FirstUserImage,
        };

        void create() override;

        void connect(Event::EventHandler handler);

        void enable(bool enableFlag);

        void loadImage(int imgType, const char *path);
        void loadImage(int imgType, const std::string path) { loadImage(imgType, path.c_str()); }
        void loadImage(ImageIndex imgType, const char *path) { loadImage((int) imgType, path); }
        void loadImage(ImageIndex imgType, const std::string path) { loadImage((int) imgType, path.c_str()); }

    protected:
        typedef std::unique_ptr<Ui::Bitmap> BmpPtr;

        unsigned long _activeBgClr;
        unsigned long _fgClr;
        unsigned long _disabledFgClr;
        std::string _text;
        int _status;
        uint16_t _id;
        Event::EventHandler _handler;
        std::unordered_map<int, BmpPtr> _images;
        BmpPtr _noImage;

        void onButtonPress(XButtonPressedEvent& evt) override;
        void onButtonRelease(XButtonReleasedEvent& evt) override;
        void onMouseEnter(XCrossingEvent& evt) override;
        void onMouseLeave(XCrossingEvent& evt) override;

        void paint(GC ctx) const override;

        virtual void loadImages() {}
        virtual const BmpPtr& getImage() const;

        const BmpPtr& getImage(int index) const;
        const BmpPtr& getImage(ImageIndex index) const { return getImage((int) index); }

        virtual void drawText(GC ctx, bool fillBgRect = true) const;
        virtual void drawImage(GC ctx) const;

        virtual const std::string& getFontName() const;
        virtual int getTextY() const;
        virtual int getImageX(const BmpPtr&) const;
        virtual int getImageY(const BmpPtr&) const;

        virtual unsigned long getFgColor() const { return _fgClr; }
        virtual unsigned long getBgColor() const { return _bgClr; }
};

}
