#include <sl_value_storage.h>
#include <sl_ui_button.h>

#include "sl_lamp_generic_indicators.h"

LampGenericIndicators::LampGenericIndicators(const char *label, Types& types, const ValueStorage& storage, Display *display, int x, int y, int width, int offsetFromCol2, Window parent):
    Ui::DrawableObject::DrawableObject(display, x, y, width, getIndicatorHeight() * types.size(), parent),
    _width(width),
    _storage(storage),
    _types(types) {
    setAnchorage(AnchorageFlags::Right|AnchorageFlags::Top, UiButtonsLayout::SECOND_COL_RIGHT + offsetFromCol2, UiButtonsLayout::SECOND_ROW_Y);
    applyAnchorage();
    for (int i = 0; i < types.size(); ++i) {
        int yOffset = LampGenericIndicators::getIndicatorHeight() * i + 34;
        _indicators[i] = std::make_unique<ValueField>(
            display,
            [i, this]() {
                return _storage.getStringValue(_types[i]);
            },
            _x,
            _y + yOffset,
            width,
            getIndicatorHeight(),
            parent
        );
        
        addChildDrawableObject(_indicators[i].get());
        _indicators[i]->setParentDrawableObject(this);
        _indicators[i]->setAnchorage(AnchorageFlags::ParentBase, 0, yOffset);
        _indicators[i]->setupLayout(0, yOffset);
        _indicators[i]->setBgColor(0);
    }

    _label = std::make_unique<RedLabel>(display, label, 0, 0, width, getIndicatorHeight(), this);
    _label->setAnchorage(AnchorageFlags::ParentBase, 0, 0);
    _label->applyAnchorage();
}

void LampGenericIndicators::show(bool showFlag) {
    for (int i = 0; i < _types.size(); ++i) {
        if (_indicators[i])
            _indicators[i]->show(showFlag);
    }
    _label->show(showFlag);
}

void LampGenericIndicators::paint(GC ctx) {
    for (int i = 0; i < _types.size(); ++i) {
        if (_indicators[i])
            _indicators[i]->paint(ctx);
    }
    _label->paint(ctx);
}

void LampGenericIndicators::updateUi() {
    applyAnchorage();
    for (int i = 0; i < _types.size(); ++i) {
        if (_indicators[i])
            _indicators[i]->updateUi();
    }
    _label->updateUi();
}

