#pragma once

#include <memory>
#include <sdk/sl_drawable.h>
#include <sl_value_storage.h>
#include "sl_simple_value.h"
#include "sl_red_label.h"

class LampIdIndicators: public Ui::DrawableObject {
    public:
        LampIdIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent);

        void show(bool showFlag) override;

        static int getLampIndicatorWidth();
        static int getLampIndicatorHeight();

    protected:
        const ValueStorage& _storage;
        std::unique_ptr<ValueField> _indicators[3];
        std::unique_ptr<RedLabel> _label;

        void paint(GC ctx) override;

        void updateUi() override;
};