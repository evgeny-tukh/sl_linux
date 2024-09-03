#pragma once

#include <memory>
#include <array>
#include <X11/Xlib.h> 
#include <sdk/sl_drawable.h>
#include <sdk/sl_wnd.h>
#include <sl_constants.h>
#include <sl_value_storage.h>
#include "sl_simple_value.h"
#include "sl_red_label.h"

class LampGenericIndicators: public Ui::DrawableObject {
    public:
        using Types = const std::array<Types::DataType, 3>;

        LampGenericIndicators(const char *label, Types& types, const ValueStorage& storage, Display *display, int x, int y, int width, int offsetFromCol2, Window parent);

        void show(bool showFlag) override;

        virtual int getIndicatorHeight() const { return 35; };

    protected:
        int _width;
        const ValueStorage& _storage;
        std::unique_ptr<ValueField> _indicators[3];
        std::unique_ptr<RedLabel> _label;
        const Types& _types;

        void paint(GC ctx) override;

        void updateUi() override;
};