#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include <X11/Xlib.h> 

#include "sl_button.h"
#include "sl_wnd.h"
#include "sl_event.h"
#include "sl_bitmap.h"

enum class Controls: uint16_t {
    OK,
    Cancel,
};

struct Context {
    int mainWndWidth = 0;
    int mainWndHeight = 0;
};

namespace Const {
    const char *DISPLAY = "DISPLAY";

    const int LEFT = 10;
    const int TOP = 10;
    const int WIDTH = 500;
    const int HEIGHT = 500;
    const int BORDER_WIDTH = 5;
}

Context ctx;

class MainWnd: public Ui::Wnd {
    public:
        MainWnd(Display *display, Ui::Wnd::Properties& props);

    protected:
        Ui::Button *_butDisable;
        Ui::Button *_butClose;
        std::shared_ptr<Ui::Bitmap> _img;
        bool _closeDisabled;

        void paint(GC ctx) const override;
};

MainWnd::MainWnd(Display *display, Ui::Wnd::Properties& props):
    Ui::Wnd(display, props, RootWindow(display, DefaultScreen(display))),
    _butDisable(nullptr),
    _butClose(nullptr),
    _closeDisabled(false) {
    auto screen = DefaultScreen(display);
    auto borderClr = BlackPixel(display, screen);
    auto bgClr = WhitePixel(display, screen);
    auto palette = DefaultColormap(display, screen);

    XColor extraLightGrayRef;
    extraLightGrayRef.red = 200 * 256;
    extraLightGrayRef.green = 200 * 256;
    extraLightGrayRef.blue = 200 * 256;

    XColor lightGrayRef;
    lightGrayRef.red = 150 * 256;
    lightGrayRef.green = 150 * 256;
    lightGrayRef.blue = 150 * 256;

    XColor darkGrayRef;
    darkGrayRef.red = 120 * 256;
    darkGrayRef.green = 120 * 256;
    darkGrayRef.blue = 120 * 256;

    bool res;
    res = XAllocColor(display, palette, &extraLightGrayRef);
    res = XAllocColor(display, palette, &lightGrayRef);
    res = XAllocColor(display, palette, &darkGrayRef);

    create();

    Ui::Wnd::Properties butProps;
    butProps[Ui::Wnd::Property::X] = 50;
    butProps[Ui::Wnd::Property::Y] = 50;
    butProps[Ui::Wnd::Property::Width] = 80;
    butProps[Ui::Wnd::Property::Height] = 40;
    butProps[Ui::Wnd::Property::BorderColor] = borderClr;
    butProps[Ui::Wnd::Property::FgColor] = BlackPixel(display, screen);
    butProps[Ui::Wnd::Property::DisabledFgColor] = darkGrayRef.pixel;
    butProps[Ui::Wnd::Property::ActiveBgColor] = extraLightGrayRef.pixel;
    butProps[Ui::Wnd::Property::BgColor] = lightGrayRef.pixel;
    butProps[Ui::Wnd::Property::BorderWidth] = 1;
    _butDisable = dynamic_cast<Ui::Button *>(addChild((uint16_t) Controls::OK, std::make_shared<Ui::Button>((uint16_t) Controls::OK, "Ok", display, butProps, _wnd)));

    butProps[Ui::Wnd::Property::X] = 150;
    _butClose = dynamic_cast<Ui::Button *>(addChild((uint16_t) Controls::Cancel, std::make_shared<Ui::Button>((uint16_t) Controls::Cancel, "Close", display, butProps, _wnd)));

    selectInput(SubstructureRedirectMask | StructureNotifyMask | SubstructureNotifyMask | ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);
    show(true);

    _butDisable->create();
    _butDisable->show(true);
    _butDisable->connect([this] (Ui::Event&) {
        _closeDisabled = !_closeDisabled;
        _butClose->enable(!_closeDisabled);
    });

    _butClose->create();
    _butClose->connect([this] (Ui::Event&) {
        destroy();
    });
    _butClose->show(true);

    _img = std::make_shared<Ui::Bitmap>(*this);
    //_img->loadBmp("/home/jeca/work/bin/res/Range +/RangePlusActivated.bmp");
    _img->loadBmpFile("/home/jeca/work/bin/res/Range +/RangePlusActivated.bmp");
    //_img->loadXbm("/home/jeca/work/bin/res/Range +/RangePlusActivated.xbm");
}

void MainWnd::paint(GC ctx) const {
    XSetForeground(_display, ctx, _borderClr);
    XSetBackground(_display, ctx, _bgClr);
    XDrawString(_display, _wnd, ctx, 50, 50, "hello!", 6);
    _img->drawTo(*this, 10, 200, 0, 0, ctx);
}

int main(int argCount, char *args[]) {
    char *displayEnv = getenv(Const::DISPLAY);

    if (!displayEnv) {
        printf("No display environment variable!\n");
        return 0;
    }

    Display *display = XOpenDisplay(displayEnv);

    if (!display) {
        printf("Unable to connect display server!\n");
        return 0;
    }

    Ui::Wnd::Properties props;
    props[Ui::Wnd::Property::X] = Const::LEFT;
    props[Ui::Wnd::Property::Y] = Const::TOP;
    props[Ui::Wnd::Property::Width] = Const::WIDTH;
    props[Ui::Wnd::Property::Height] = Const::HEIGHT;
    props[Ui::Wnd::Property::BorderColor] = BlackPixel(display, DefaultScreen(display));
    props[Ui::Wnd::Property::BgColor] = WhitePixel(display, DefaultScreen(display));
    props[Ui::Wnd::Property::BorderWidth] = Const::BORDER_WIDTH;
    
    MainWnd wndMain(display, props);
    wndMain.eventLoop([] (Ui::Wnd& wnd, XEvent&) { return true; });

    XCloseDisplay(display);

    return 0;
}

