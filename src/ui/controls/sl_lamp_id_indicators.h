#pragma once

#include <memory>
#include <sdk/sl_drawable.h>
#include <sl_value_storage.h>
#include "sl_simple_value.h"
#include "sl_red_label.h"
#include "sl_lamp_generic_indicators.h"

#if 1
class LampIdIndicators: public LampGenericIndicators {
    public:
        LampIdIndicators(ValueStorage& storage, Display *display, int x, int y, Window parent);
};

#else

class LampIdIndicators: public Ui::DrawableObject {
    public:
        LampIdIndicators(ValueStorage& storage, Display *display, int x, int y, Window parent);

        void show(bool showFlag) override;

        static int getLampIndicatorWidth();
        static int getLampIndicatorHeight();

    protected:
        ValueStorage& _storage;
        std::unique_ptr<ValueField> _indicators[3];
        std::unique_ptr<RedLabel> _label;

        void paint(GC ctx) override;

        void updateUi() override;
};

#endif