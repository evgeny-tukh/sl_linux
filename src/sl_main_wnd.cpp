#include "sl_main_wnd.h"
#include "sl_util.h"
#include "sl_tools.h"
#include "sl_text_constants.h"

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

    initLabeledValue(_hdg, TextConstants::HDG, 400, 200, Ui::Resources::HDG);
    initLabeledValue(_lat, TextConstants::LAT, 400, 300, Ui::Resources::LAT, 150);
    initLabeledValue(_lon, TextConstants::LON, 400, 400, Ui::Resources::LON, 150);

    _storage.setValue(TextConstants::HDG, 56.4, ValueStorage::Format::Angle);
    _storage.setValue(TextConstants::LAT, 59.5, ValueStorage::Format::Lat);
    _storage.setValue(TextConstants::LON, 29.5, ValueStorage::Format::Lon);
}

std::string SearchMasterWnd::getValueOfParameter(const char *label) const {
    auto text = _storage.getStringValue(label).c_str();
    return text;
}

void SearchMasterWnd::initLabeledValue(std::shared_ptr<LabeledValue>& ctrl, const char *label, int x, int y, Ui::Resources id, int width) {
    ValueField::Getter getter = [this, label] () {
        return getValueOfParameter(label);
    };

    ctrl.reset(new LabeledValue(_display, label, getter, x, y, _wnd, width));
    addChild((uint16_t) id, ctrl);
    ctrl->show(true);

    _valueDisplays.emplace(std::pair<std::string, std::shared_ptr<LabeledValue>&>(label, ctrl));
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