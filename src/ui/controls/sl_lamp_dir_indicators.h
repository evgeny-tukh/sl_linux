#pragma once

#include <memory>
#include <sdk/sl_drawable.h>
#include "sl_lamp_dir_indicator.h"

class LampDirIndicators: public Ui::DrawableObject {
    public:
        LampDirIndicators(Display *display, int x, int y, Window parent);

        void show(bool showFlag) override;

    protected:
        std::unique_ptr<LampDirIndicator> _indicators[3];

        void paint(GC ctx) const override;

        void updateUi() override;
};