#pragma once

#include "sl_value.h"

class AngleValue: public Value {
    public:
        AngleValue(Display *display, Getter getter, int x, int y, Window parent);
};