#include "sl_main_wnd.h"
#include "sl_util.h"

namespace {
    const int X = 100, Y = 100, WIDTH = 1800, HEIGHT = 800;
}


SearchMasterWnd::SearchMasterWnd(Display *display):
    Ui::Wnd(display, X, Y, WIDTH, HEIGHT, /*parent.handle()*/RootWindow(display, DefaultScreen(display))) {
    auto screen = DefaultScreen(display);
    _borderClr = WhitePixel(display, screen);
    _bgClr = BlackPixel(display, screen);
    _yellowClr = Ui::Util::allocateColor(255, 127, 0, display);
    _img.reset(new Ui::Bitmap(*this));
    _img->loadBmpFile("/home/jeca/work/sl/bin/res/buttonImages/name/hovered.bmp");
}

void SearchMasterWnd::create() {
    Ui::Wnd::create();
    selectInput(ButtonPressMask|ButtonReleaseMask|EnterWindowMask|LeaveWindowMask|SubstructureRedirectMask|StructureNotifyMask|SubstructureNotifyMask |ExposureMask |KeyPressMask);

    initButton<NameEditButton>(_butNameEdit, Ui::Resources::ToggleName);
    initButton<HarbourModeButton>(_butHarbourModeSwitch, Ui::Resources::ToggleHarbourMode);
    initButton<SettingsButton>(_butSettings, Ui::Resources::Settings);
    initButton<RangeExtendButton>(_butRangeExt, Ui::Resources::RangeExt);
    initButton<RangeReduceButton>(_butRangeRed, Ui::Resources::RangeRed);
    initButton<LightOnButton>(_butLightOn, Ui::Resources::LightOn);
    initButton<LightOffButton>(_butLightOff, Ui::Resources::LightOff);
    initButton<DimmerExtendButton>(_butDimmerExt, Ui::Resources::IncreaseDimmer);
    initButton<DimmerReduceButton>(_butDimmerRed, Ui::Resources::DecreaseDimmer);
}

void SearchMasterWnd::paint(GC ctx) const {
    auto font = XLoadQueryFont(_display, "*12x24*");
    XSetFont(_display, ctx, font->fid);
    XSetPlaneMask(_display, ctx, AllPlanes);
    XSetForeground(_display, ctx, WhitePixel(_display, DefaultScreen(_display)));
    XSetBackground(_display, ctx, WhitePixel(_display, DefaultScreen(_display)));
    XFillRectangle(_display, _wnd, ctx, 50, 50, 800, 400);
    XSetForeground(_display, ctx, BlackPixel(_display, DefaultScreen(_display)));
    XFillRectangle(_display, _wnd, ctx, 60, 60, 780, 380);
    XSetForeground(_display, ctx, _yellowClr);
    XFillArc(_display, _wnd, ctx, 200, 200, 100, 100, 0, 360 * 64);
    textOut(120, 100, ctx, "NAME");
    XUnloadFont(_display, font->fid);
    _img->putTo(*this, 100, 100, 0, 0, ctx);
}

void onParentSizeChanged(int width, int height) {
    
}