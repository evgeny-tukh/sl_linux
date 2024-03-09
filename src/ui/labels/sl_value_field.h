#pragma once

#include <functional>
#include <string>

#include <sdk/sl_text.h>

class ValueField: public Ui::Text {
    public:
        enum Style {
            Border = 1,
        };

        typedef std::function<std::string()> Getter;
        typedef std::function<void(GC ctx)> Painter;

        ValueField(Display *display, Getter getter, int x, int y, int width, int height, Window parent, Painter painter = nullptr);

        void updateUi() override;

        void paint(GC ctx) const override;

    protected:
        Getter _getter;
        Painter _painter;
};
