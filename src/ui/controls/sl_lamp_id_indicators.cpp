#include <array>
#include <sl_value_storage.h>
#include <sl_ui_button.h>

#include "sl_lamp_id_indicators.h"

namespace {
const char *LABEL { "ID" };
const int WIDTH = 50;
const int HEIGHT = 35;
}

#if 1
LampGenericIndicators::Types types {
    Types::DataType::ID_1,
    Types::DataType::ID_2,
    Types::DataType::ID_3,
};

LampIdIndicators::LampIdIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent):
    LampGenericIndicators(LABEL, types, storage, display, x, y, WIDTH, 95, parent) {

}
#else
Types::DataType types[3] {
    Types::DataType::ID_1,
    Types::DataType::ID_2,
    Types::DataType::ID_3,
};
}

LampIdIndicators::LampIdIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent):
    Ui::DrawableObject::DrawableObject(display, x, y, LampIdIndicators::getLampIndicatorWidth(), LampIdIndicators::getLampIndicatorHeight() * 3, parent),
    _storage(storage) {
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::SECOND_COL_RIGHT + 95, UiButtonsLayout::SECOND_ROW_Y);
    applyAnchorage();
    for (int i = 0; i < 3; ++i) {
        int yOffset = LampIdIndicators::getLampIndicatorHeight() * i + 34;
        _indicators[i] = std::make_unique<ValueField>(
            display,
            [i, this]() {
                return _storage.getStringValue(types[i]);
            },
            _x,
            _y + yOffset,
            WIDTH,
            HEIGHT,
            parent
        );
        
        addChildDrawableObject(_indicators[i].get());
        _indicators[i]->setParentDrawableObject(this);
        _indicators[i]->setAnchorage(AnchorageFlags::ParentBase, 0, yOffset);
        _indicators[i]->setupLayout(0, yOffset);
    }

    _label = std::make_unique<RedLabel>(display, LABEL, 0, 0, WIDTH, HEIGHT, this);
    _label->setAnchorage(AnchorageFlags::ParentBase, 0, 0);
    _label->applyAnchorage();
}

void LampIdIndicators::show(bool showFlag) {
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->show(showFlag);
    }
    _label->show(showFlag);
}

void LampIdIndicators::paint(GC ctx) {
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->paint(ctx);
    }
    _label->paint(ctx);
}

void LampIdIndicators::updateUi() {
    applyAnchorage();
    for (int i = 0; i < 3; ++i) {
        if (_indicators[i])
            _indicators[i]->updateUi();
    }
    _label->updateUi();
}

int LampIdIndicators::getLampIndicatorWidth() {
    return WIDTH;
}

int LampIdIndicators::getLampIndicatorHeight() {
    return HEIGHT;
}

#endif