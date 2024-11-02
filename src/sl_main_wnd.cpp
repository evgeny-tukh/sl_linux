#include <stdlib.h>
#include <memory.h>
#include "sl_main_wnd.h"
#include "sl_util.h"
#include "sl_tools.h"
#include "sl_constants.h"
#include "sl_display.h"

#if 0
#include <nmea/sl_nmea_parser.h>
#include <nmea/sl_hdt_sentence.h>
#include <nmea/sl_gll_sentence.h>
#include <nmea/sl_vdm_sentence.h>
#endif

namespace {
    const int X = 100, Y = 100, WIDTH = 1500, HEIGHT = 800;
}


SearchMasterWnd::SearchMasterWnd(Display *display, ValueStorage & storage):
    Ui::Wnd(display, X, Y, WIDTH, HEIGHT, /*parent.handle()*/RootWindow(display, DefaultScreen(display))),
    _storage(storage) {
    auto screen = DefaultScreen(display);
    _borderClr = WhitePixel(display, screen);
    _bgClr = BlackPixel(display, screen);
    _yellowClr = Ui::Util::allocateColor(255, 127, 0, display);
    _img.reset(new Ui::Bitmap(*this));
    _img->loadBmpFile("/home/jeca/work/sl/bin/res/buttonImages/name/hovered.bmp");
}

SearchMasterWnd::~SearchMasterWnd() {
    _running.store(false);

    if (_watchdog.joinable())
        _watchdog.join();
}

void SearchMasterWnd::create() {
    Ui::Wnd::create();
    selectInput(ButtonPressMask|ButtonReleaseMask|EnterWindowMask|LeaveWindowMask|SubstructureRedirectMask|StructureNotifyMask|SubstructureNotifyMask |ExposureMask |KeyPressMask);

    initButton<NameEditButton>(_butNameEdit, Ui::Resources::ToggleName);
    initButton<HarbourModeButton>(_butHarbourModeSwitch, Ui::Resources::ToggleHarbourMode);
    initButton<SettingsButton>(_butSettings, Ui::Resources::Settings);
    initButton<RangeExtendButton>(_butRangeExt, Ui::Resources::RangeExt);
    initButton<RangeReduceButton>(_butRangeRed, Ui::Resources::RangeRed);
    initButton<ScanExtendButton>(_butScanExt, Ui::Resources::ScanExt);
    initButton<ScanReduceButton>(_butScanRed, Ui::Resources::ScanRed);
    initButton<LightOnButton>(_butLightOn, Ui::Resources::LightOn);
    initButton<LightOffButton>(_butLightOff, Ui::Resources::LightOff);
    initButton<DimmerExtendButton>(_butDimmerExt, Ui::Resources::IncreaseDimmer);
    initButton<DimmerReduceButton>(_butDimmerRed, Ui::Resources::DecreaseDimmer);

    initLabeledValue(_hdg, TextConstants::HDG, 400, 200, Ui::Resources::HDG);
    initLabeledValue(_lat, TextConstants::LAT, 400, 300, Ui::Resources::LAT, 150);
    initLabeledValue(_lon, TextConstants::LON, 400, 400, Ui::Resources::LON, 150);
    initLabeledValue(_info, TextConstants::INFO, 400, 400, Ui::Resources::INFO, 580, 180);

    _hdg->setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::FIRST_COL_RIGHT, UiButtonsLayout::TOP_ROW_Y);
    _hdg->setupLayout(0, 0);
    _hdg->applyAnchorage();

    _lat->setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::SECOND_COL_RIGHT - 15, UiButtonsLayout::THIRD_ROW_Y);
    _lat->setupLayout(0, 0);
    _lat->applyAnchorage();

    _lon->setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::SECOND_COL_RIGHT - 175, UiButtonsLayout::THIRD_ROW_Y);
    _lon->setupLayout(0, 0);
    _lon->applyAnchorage();

    _info->setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::SECOND_COL_RIGHT - 445, UiButtonsLayout::THIRD_ROW_Y + 75);
    _info->setupLayout(0, 0);
    _info->applyAnchorage();

    _targetDisplay.reset(new TargetDisplay(_storage, _display, _wnd));
    addChild((uint16_t) Ui::Resources::TargetDisplay, _targetDisplay);
    _targetDisplay->create();
    _targetDisplay->show(true);
    _targetDisplay->setAnchorage(AnchorageFlags::FitLeft, 20, 20, 700, 0);
    _targetDisplay->applyAnchorage();
    _targetDisplay->moveToCurrentPos();
    _targetDisplay->setupLayout();

    _storage.setValue(TextConstants::HDG, 56.4, ValueStorage::Format::Angle);
    _storage.setValue(TextConstants::LAT, 59.5, ValueStorage::Format::Lat);
    _storage.setValue(TextConstants::LON, 29.5, ValueStorage::Format::Lon);
    _storage.setValue(TextConstants::BRG_1, 123.5, ValueStorage::Format::Angle);
    _storage.setValue(TextConstants::BRG_3, 281.4, ValueStorage::Format::Angle);

    _lampDirIndicators.reset(new LampDirIndicators(_storage, _display, 700, 600, _wnd));
    addChild((uint16_t) Ui::Resources::LAMP_BRGS, _lampDirIndicators);
    _lampDirIndicators->show(true);

    _lampIdIndicators.reset(new LampIdIndicators(_storage, _display, 700, 600, _wnd));
    addChild((uint16_t) Ui::Resources::LAMP_IDS, _lampIdIndicators);
    _lampIdIndicators->show(true);

    _lampStatusIndicators.reset(new LampStatusIndicators(_storage, _display, 700, 600, _wnd));
    addChild((uint16_t) Ui::Resources::LAMP_STATUSES, _lampStatusIndicators);
    _lampStatusIndicators->show(true);

    _lampDistIndicators.reset(new LampDistIndicators(_storage, _display, 700, 600, _wnd));
    addChild((uint16_t) Ui::Resources::LAMP_RANGES, _lampDistIndicators);
    _lampDistIndicators->show(true);

    _lampFocusIndicators.reset(new LampFocusIndicators(_storage, _display, 700, 600, _wnd));
    addChild((uint16_t) Ui::Resources::LAMP_FOCUSES, _lampFocusIndicators);
    _lampFocusIndicators->show(true);

    _lampSystemIndicators.reset(new LampSystemIndicators(_storage, _display, 700, 600, _wnd));
    addChild((uint16_t) Ui::Resources::LAMP_SYSTEMS, _lampSystemIndicators);
    _lampSystemIndicators->show(true);

    _running.store(true);
    _watchdog = std::thread([this] () { watchdogProc(); });
}

std::string SearchMasterWnd::getValueOfParameter(const char *label) const {
    auto text = _storage.getStringValue(label).c_str();
    return text;
}

/*void SearchMasterWnd::onSizeChanged(int width, int height, bool& notifyChildren) {
    _targetDisplay->setupLayout();
}*/

void SearchMasterWnd::initLabeledValue(std::shared_ptr<LabeledValue>& ctrl, const char *label, int x, int y, Ui::Resources id, int width, int height) {
    ValueField::Getter getter = [this, label] () {
        return getValueOfParameter(label);
    };

    if (height > 0)
        ctrl.reset(new LabeledValue(_display, label, getter, x, y, _wnd, width, height));
    else
        ctrl.reset(new LabeledValue(_display, label, getter, x, y, _wnd, width));

    addChild((uint16_t) id, ctrl);
    ctrl->show(true);

    _valueDisplays.emplace(std::pair<std::string, std::shared_ptr<LabeledValue>&>(label, ctrl));
}

void SearchMasterWnd::paint(GC ctx) {
    //XClearArea(_display, _wnd, 0, 0, _width, _height, true);
}

void SearchMasterWnd::watchdogProc() {
    Display *display = XOpenDisplay(nullptr);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    while (_running.load()) {
        XEvent evt;

        memset(&evt, 0, sizeof(evt));

        updateUi();

        evt.xexpose.type = Expose;
        evt.xexpose.display = display;
        evt.xexpose.window = _wnd;

        auto result = XSendEvent(display, _wnd, 0, ExposureMask, &evt);
        XFlush(display);

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    XCloseDisplay(display);
}

void SearchMasterWnd::onPaint(XExposeEvent& evt) {
    Ui::Wnd::onPaint(evt);
}