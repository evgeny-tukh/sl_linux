#include <sl_value_storage.h>
#include <sl_ui_button.h>

#include "sl_lamp_dir_indicators.h"

LampDirIndicators::LampDirIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent):
    Ui::DrawableObject::DrawableObject(display, x, y, LampDirIndicator::getLampIndicatorWidth(), LampDirIndicator::getLampIndicatorHeight() * 3, parent),
    _storage(storage) {
    static Types::DataType types[3] {
        Types::DataType::BRG_1,
        Types::DataType::BRG_2,
        Types::DataType::BRG_3,
    };
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::SECOND_COL_RIGHT, UiButtonsLayout::TOP_ROW_Y);
    applyAnchorage();
    for (int i = 0; i < 3; ++i) {
        _indicators[i] = std::make_unique<LampDirIndicator>(
            display,
            [i, this]() {
                return _storage.getStringValue(types[i]);
            },
            _x,
            _y + LampDirIndicator::getLampIndicatorHeight() * i + 30,
            i,
            parent
        );
    }
    _label = std::make_unique<RedLabel>(display, "BRG.", 0, 0, 100, 30, parent);
}

void LampDirIndicators::show(bool showFlag) {
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->show(showFlag);
    }
    _label->show(showFlag);
}

void LampDirIndicators::paint(GC ctx) const {
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->paint(ctx);
    }
    _label->paint(ctx);
}

void LampDirIndicators::updateUi() {
    applyAnchorage();
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->updateUi();
    }
    _label->updateUi();
}
