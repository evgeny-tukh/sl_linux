#include "sl_lamp_dir_indicators.h"

LampDirIndicators::LampDirIndicators(Display *display, int x, int y, Window parent):
    Ui::DrawableObject::DrawableObject(display, x, y, LampDirIndicator::getLampIndicatorWidth(), LampDirIndicator::getLampIndicatorHeight() * 3, parent) {
    for (int i = 0; i < 3; ++i) {
        _indicators[i] = std::make_unique<LampDirIndicator>(
            display,
            [i]() { return "val of" + std::to_string(i + 1); },
            x,
            y + LampDirIndicator::getLampIndicatorHeight() * i,
            i,
            parent
        );
    }
}

void LampDirIndicators::show(bool showFlag) {
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->show(showFlag);
    }
}

void LampDirIndicators::paint(GC ctx) const {
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->paint(ctx);
    }
}

void LampDirIndicators::updateUi() {
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->updateUi();
    }
}
