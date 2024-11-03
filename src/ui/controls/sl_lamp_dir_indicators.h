#pragma once

#include <memory>
#include <sdk/sl_drawable.h>
#include <sl_value_storage.h>
#include "sl_red_label.h"
#include "sl_lamp_dir_indicator.h"

class LampDirIndicators: public Ui::DrawableObject {
    public:
        LampDirIndicators(ValueStorage& storage, Display *display, int x, int y, Window parent);

        void show(bool showFlag) override;

    protected:
        ValueStorage& _storage;
        std::unique_ptr<LampDirIndicator> _indicators[3];
        std::unique_ptr<RedLabel> _label;

        void paint(GC ctx) override;

        void updateUi() override;
};