#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include <unistd.h>
#include <X11/Xlib.h> 

#include "sl_button.h"
#include "sl_wnd.h"
#include "sl_event.h"
#include "sl_bitmap.h"
#include "sl_range_inc_but.h"
#include "sl_range_dec_but.h"
#include "sl_res.h"
#include "sl_main_wnd.h"
#include "sl_util.h"

enum class Controls: uint16_t {
    OK,
    Cancel,
    ShowSM,
};

struct Context {
    int mainWndWidth = 0;
    int mainWndHeight = 0;
};

namespace Const {
    const int LEFT = 10;
    const int TOP = 10;
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int BORDER_WIDTH = 5;
}

Context ctx;

class MainWnd: public Ui::Wnd {
    public:
        MainWnd(Display *display, Ui::Wnd::Properties& props);

    protected:
        Ui::Button *_butDisable;
        Ui::Button *_butClose;
        Ui::Button *_butShowSM;
        std::shared_ptr<RangeIncButton> _butRangeInc;
        std::shared_ptr<RangeDecButton> _butRangeDec;
        std::shared_ptr<SearchMasterWnd> _smWindow;
        bool _closeDisabled;

        void paint(GC ctx) const override;
};

MainWnd::MainWnd(Display *display, Ui::Wnd::Properties& props):
    Ui::Wnd(display, props, RootWindow(display, DefaultScreen(display))),
    _butDisable(nullptr),
    _butClose(nullptr),
    _butShowSM(nullptr),
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

    XAllocColor(display, palette, &extraLightGrayRef);
    XAllocColor(display, palette, &lightGrayRef);
    XAllocColor(display, palette, &darkGrayRef);

    create();

    Ui::Wnd::Properties butProps;
    butProps[Ui::Wnd::Property::X] = 50;
    butProps[Ui::Wnd::Property::Y] = 60;
    butProps[Ui::Wnd::Property::Width] = 80;
    butProps[Ui::Wnd::Property::Height] = 40;
    butProps[Ui::Wnd::Property::BorderColor] = borderClr;
    butProps[Ui::Wnd::Property::FgColor] = BlackPixel(display, screen);
    butProps[Ui::Wnd::Property::DisabledFgColor] = darkGrayRef.pixel;
    butProps[Ui::Wnd::Property::ActiveBgColor] = extraLightGrayRef.pixel;
    butProps[Ui::Wnd::Property::BgColor] = lightGrayRef.pixel;
    butProps[Ui::Wnd::Property::BorderWidth] = 1;
    _butDisable = dynamic_cast<Ui::Button *>(addChild((uint16_t) Controls::OK, std::make_shared<Ui::Button>((uint16_t) Controls::OK, "Toggle", display, butProps, _wnd)));

    butProps[Ui::Wnd::Property::X] = 150;
    _butClose = dynamic_cast<Ui::Button *>(addChild((uint16_t) Controls::Cancel, std::make_shared<Ui::Button>((uint16_t) Controls::Cancel, "Close", display, butProps, _wnd)));

    butProps[Ui::Wnd::Property::X] = 50;
    butProps[Ui::Wnd::Property::Y] = 110;
    _butShowSM = dynamic_cast<Ui::Button *>(addChild((uint16_t) Controls::ShowSM, std::make_shared<Ui::Button>((uint16_t) Controls::ShowSM, "Show SM", display, butProps, _wnd)));

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

    _butShowSM->create();
    _butShowSM->connect([this] (Ui::Event&) {
        _smWindow->create();
        _smWindow->show(true);
        //_smWindow->forceRedraw();
        _smWindow->eventLoop([] (Ui::Wnd& wnd, XEvent&) { return true; });
    });
    _butShowSM->show(true);

    _butRangeInc.reset(new RangeIncButton(*this));
    addChild((uint16_t) Ui::Resources::IncreaseRange, _butRangeInc);
    _butRangeInc->create();
    _butRangeInc->show(true);

    _butRangeDec.reset(new RangeDecButton(*this));
    addChild((uint16_t) Ui::Resources::DecreaseRange, _butRangeDec);
    _butRangeDec->create();
    _butRangeDec->show(true);

    _smWindow.reset(new SearchMasterWnd(Ui::Util::openDisplay()));
    //addChild((uint16_t) Ui::Resources::SeacrhMaster, _smWindow);
    //_smWindow->create();
}

void MainWnd::paint(GC ctx) const {
    XSetPlaneMask(_display, ctx, AllPlanes);
    XSetForeground(_display, ctx, _borderClr);
    XSetBackground(_display, ctx, _bgClr);
    XSetFunction(_display, ctx, GXcopy);
    XDrawString(_display, _wnd, ctx, 50, 50, "hello!", 6);
}

int main(int argCount, char *args[]) {
    Display *display = Ui::Util::openDisplay();

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

