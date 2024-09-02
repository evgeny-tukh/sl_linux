#pragma once

#include <X11/Xlib.h> 

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>

#include "sl_wnd.h"
#include "sl_event.h"
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
            Checkable = 32,
            Checked = 64,
        };

        enum class ImageIndex: int {
            Normal = 0,
            Hovered,
            Pressed,
            Disabled,
            FirstUserImage,
            CheckedNormal,
            CheckedHovered,
            CheckedPressed,
        };

        void create() override;

        void connect(Event::EventHandler handler);

        void enable(bool enableFlag);

        void loadImage(int imgType, const char *path);
        void loadImage(int imgType, const std::string path) { loadImage(imgType, path.c_str()); }
        void loadImage(ImageIndex imgType, const char *path) { loadImage((int) imgType, path); }
        void loadImage(ImageIndex imgType, const std::string path) { loadImage((int) imgType, path.c_str()); }

        void setCheckable(bool);
        bool checkable();
        void setChecked(bool);
        bool checked();
        void toggle();

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

        virtual int getTextY() const;
        virtual int getImageX(const BmpPtr&) const;
        virtual int getImageY(const BmpPtr&) const;

        virtual unsigned long getFgColor() const { return _fgClr; }
        virtual unsigned long getCheckedFgColor() const { return getFgColor(); }
        virtual unsigned long getBgColor() const { return _bgClr; }
        virtual unsigned long getCheckedBgColor() const { return getBgColor(); }
        virtual unsigned long getActiveBgColor() const { return _activeBgClr; }
        virtual unsigned long getCheckedActiveBgColor() const { return getActiveBgColor(); }
        virtual unsigned long getDisabledFgColor() const { return _disabledFgClr; }

        virtual bool canBeToggled() const { return true; }

        virtual std::string getText() const { return _text; }

        void setStatusFlag(ButtonStatus flag);
        void clearStatusFlag(ButtonStatus flag);
        bool getStatusFlag(ButtonStatus flag) const;
};

}
