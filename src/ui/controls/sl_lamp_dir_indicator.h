#pragma once

#include <sl_value_field.h>

class LampDirIndicator: public Ui::DrawableObject {
    public:
        LampDirIndicator(Display *display, ValueField::Getter valueGetter, int x, int y, int lampIndex, Window parent);

        void show(bool showFlag) override;

        static int getLampIndicatorWidth();
        static int getLampIndicatorHeight();

        void paint(GC ctx) const override;

        void updateUi() override;

    protected:
        ValueField _label;
        ValueField _value;
        int _lampIndex;
};