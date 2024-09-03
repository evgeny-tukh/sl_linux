#pragma once

#include <sl_drawable.h>
#include <sl_red_label.h>
#include <sl_value_field.h>

class SimpleValue: public Ui::DrawableObject {
    public:
        SimpleValue(Display *display, ValueField::Getter valueGetter, int x, int y, int width, int height, Window parent);

        void show(bool showFlag) override;

        void setupLayout(int xOffset, int yOffset) override;

        void paint(GC ctx) override;

        void updateUi() override;

    protected:
        ValueField _field;
};
