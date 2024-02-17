#pragma once

#include <functional>
#include <string>

#include <sdk/sl_text.h>

class ValueField: public Ui::Text {
    public:
        typedef std::function<const char *()> Getter;

        ValueField(Display *display, Getter getter, int x, int y, int width, int height, Window parent);

        void updateUi() override;

        void paint(GC ctx) const override;

    protected:
        Getter _getter;
};
