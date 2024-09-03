#pragma once

#include <memory>
#include <sdk/sl_drawable.h>
#include <sl_value_storage.h>
#include "sl_simple_value.h"
#include "sl_red_label.h"
#include "sl_lamp_generic_indicators.h"

class LampFocusIndicators: public LampGenericIndicators {
    public:
        LampFocusIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent);
};