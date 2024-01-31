#include "sl_main_wnd.h"
#include "sl_util.h"

namespace {
    const int X = 0, Y = 0, WIDTH = 1600, HEIGHT = 800;
}

SearchMasterWnd::SearchMasterWnd(Display *display):
    Ui::Wnd(display, X, Y, WIDTH, HEIGHT, RootWindow(display, DefaultScreen(display))) {
    auto screen = DefaultScreen(display);
    _borderClr = WhitePixel(display, screen);
    _bgClr = BlackPixel(display, screen);
}

void SearchMasterWnd::paint(GC ctx) const {
    XSetPlaneMask(_display, ctx, AllPlanes);
    XSetForeground(_display, ctx, _borderClr);
    XSetBackground(_display, ctx, _bgClr);
}

