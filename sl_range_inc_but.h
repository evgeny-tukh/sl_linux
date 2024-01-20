#pragma once

#include "sl_button.h"

class RangeIncButton: public Ui::Button {
    public:
        RangeIncButton(Ui::Wnd& parent);

        class ButProperties: public Ui::Wnd::Properties {
            public:
                ButProperties();
        };
};
