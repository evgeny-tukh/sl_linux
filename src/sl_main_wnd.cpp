#include "sl_main_wnd.h"
#include "sl_util.h"

namespace {
    const int X = 100, Y = 100, WIDTH = 1000, HEIGHT = 400;
}

SearchMasterWnd::SearchMasterWnd(Display *display):
    Ui::Wnd(display, X, Y, WIDTH, HEIGHT, /*parent.handle()*/RootWindow(display, DefaultScreen(display))) {
    auto screen = DefaultScreen(display);
    _borderClr = WhitePixel(display, screen);
    _bgClr = BlackPixel(display, screen);
    _yellowClr = Ui::Util::allocateColor(255, 127, 0, display);
    _img.reset(new Ui::Bitmap(*this));
    _img->loadBmpFile("/home/jeca/work/sl/bin/res/buttonImages/name/normal.bmp");
}

void SearchMasterWnd::create() {
    Ui::Wnd::create();
    selectInput(ButtonPressMask|ButtonReleaseMask|EnterWindowMask|LeaveWindowMask|SubstructureRedirectMask|StructureNotifyMask|SubstructureNotifyMask |ExposureMask |KeyPressMask);

    _butNameEdit.reset(new NameEditButton(*this, 10, 10));
    addChild((uint16_t) Ui::Resources::ToggleName, _butNameEdit);
    _butNameEdit->create();
    _butNameEdit->show(true);
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
    _img->putTo(*this, 100, 100, 0, 0, ctx);
    XUnloadFont(_display, font->fid);
}

