#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include <X11/Xlib.h> 

#include "sl_button.h"
#include "sl_wnd.h"
#include "sl_event.h"

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

void paintMainWindow(Display *display, int screen, Window wnd) {
    XFillRectangle(display, wnd, DefaultGC(display, screen), 20, 20, 10, 10); 
}

void onWndConfigurationChanged(Display *display, int screen, Window wnd, XConfigureEvent& evt) {
    if (evt.width != ctx.mainWndWidth)
        ctx.mainWndWidth = evt.width;
    if (evt.height != ctx.mainWndHeight)
        ctx.mainWndHeight = evt.height;
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

    auto screen = DefaultScreen(display);
    auto palette = DefaultColormap(display, screen);
    auto borderClr = BlackPixel(display, screen);
    auto bgClr = WhitePixel(display, screen);

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

    Ui::Wnd::Properties props;
    props[Ui::Wnd::Property::X] = Const::LEFT;
    props[Ui::Wnd::Property::Y] = Const::TOP;
    props[Ui::Wnd::Property::Width] = Const::WIDTH;
    props[Ui::Wnd::Property::Height] = Const::HEIGHT;
    props[Ui::Wnd::Property::BorderColor] = borderClr;
    props[Ui::Wnd::Property::BgColor] = bgClr;
    props[Ui::Wnd::Property::BorderWidth] = Const::BORDER_WIDTH;
    Ui::Wnd wndMain(display, props, RootWindow(display, screen));

    wndMain.create();

    /*auto wnd = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        Const::LEFT,
        Const::TOP,
        Const::WIDTH,
        Const::HEIGHT,
        Const::BORDER_WIDTH,
        borderClr,
        bgClr
    );*/

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
    Ui::Button *okBut = dynamic_cast<Ui::Button *>(wndMain.addChild((uint16_t) Controls::OK, std::make_shared<Ui::Button>((uint16_t) Controls::OK, "Ok", display, butProps, wndMain.handle())));
    butProps[Ui::Wnd::Property::X] = 150;
    Ui::Button *closeBut = dynamic_cast<Ui::Button *>(wndMain.addChild((uint16_t) Controls::Cancel, std::make_shared<Ui::Button>((uint16_t) Controls::Cancel, "Close", display, butProps, wndMain.handle())));

    wndMain.selectInput(SubstructureRedirectMask | StructureNotifyMask | SubstructureNotifyMask | ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);
    wndMain.show(true);

    bool disabled = false;
    okBut->create();
    closeBut->create();
    okBut->show(true);
    okBut->connect([&closeBut, &disabled] (Ui::Event&) {
        disabled = !disabled;
        closeBut->enable(!disabled);
    });
    closeBut->connect([&wndMain] (Ui::Event&) {
        wndMain.destroy();
    });
    closeBut->show(true);
    //XMapWindow(display, /*wnd*/wndMain.handle());

    //bool keepRunning = true;

    auto eventHandler = [screen, display] (Ui::Wnd& wnd, XEvent& evt) {
        switch (evt.type) {
            case ConfigureNotify:
                onWndConfigurationChanged(display, screen, wnd.handle(), evt.xconfigure); break;
            case Expose:
                paintMainWindow(display, screen, wnd.handle()); break;
            case DestroyNotify:
            //case KeyPress:
                return false;
        }

        return true;
    };

    wndMain.eventLoop(eventHandler);
    #if 0
    while (keepRunning) {
        XEvent evt;

        try {
            XNextEvent(display, &evt);
        } catch (...) {
            break;
        }

        printf("Evt %d\n", evt.type);

        switch (evt.type) {
            case ConfigureNotify:
                onWndConfigurationChanged(display, screen, /*wnd*/wndMain.handle(), evt.xconfigure); break;
            case Expose:
                paintMainWindow(display, screen, /*wnd*/wndMain.handle()); break;
            case DestroyNotify:
            case KeyPress:
                keepRunning = false; break;
        }
    }
    #endif

    XCloseDisplay(display);

    return 0;
}

