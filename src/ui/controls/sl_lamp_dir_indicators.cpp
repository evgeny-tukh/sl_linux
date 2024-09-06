#include <sl_value_storage.h>
#include <sl_ui_button.h>

#include "sl_lamp_dir_indicators.h"

namespace {
const char *LABEL { "BRG" };
const int LBL_WIDTH = 40;
const int LBL_HEIGHT = 35;
}

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
        int yOffset = LampDirIndicator::getLampIndicatorHeight() * i + 34;
        _indicators[i] = std::make_unique<LampDirIndicator>(
            display,
            [i, this]() {
                return _storage.getStringValue(types[i]);
            },
            _x,
            _y + yOffset,
            i,
            parent
        );
        
        addChildDrawableObject(_indicators[i].get());
        _indicators[i]->setParentDrawableObject(this);
        _indicators[i]->setupLayout(0, yOffset);
        _indicators[i]->setBgColor(0);
    }

    _label = std::make_unique<RedLabel>(display, LABEL, 0, 0, LBL_WIDTH, LBL_HEIGHT, this);
    _label->setAnchorage(AnchorageFlags::ParentBase, 0, 0);
    _label->applyAnchorage();
}

void LampDirIndicators::show(bool showFlag) {
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->show(showFlag);
    }
    _label->show(showFlag);
}

void LampDirIndicators::paint(GC ctx) {
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
