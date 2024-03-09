#include <sl_value_storage.h>

#include "sl_lamp_dir_indicators.h"

LampDirIndicators::LampDirIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent):
    Ui::DrawableObject::DrawableObject(display, x, y, LampDirIndicator::getLampIndicatorWidth(), LampDirIndicator::getLampIndicatorHeight() * 3, parent),
    _storage(storage) {
    static Types::DataType types[3] {
        Types::DataType::BRG_1,
        Types::DataType::BRG_2,
        Types::DataType::BRG_3,
    };
    for (int i = 0; i < 3; ++i) {
        _indicators[i] = std::make_unique<LampDirIndicator>(
            display,
            [i, this]() {
                return _storage.getStringValue(types[i]);
            },
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
