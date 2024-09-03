#include <array>
#include <sl_value_storage.h>
#include <sl_ui_button.h>

#include "sl_lamp_focus_indicators.h"

namespace {
const char *LABEL { "FOCUS" };
const int WIDTH = 100;
const int HEIGHT = 35;
}

LampGenericIndicators::Types types {
    Types::DataType::FOCUS_1,
    Types::DataType::FOCUS_2,
    Types::DataType::FOCUS_3,
};

LampFocusIndicators::LampFocusIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent):
    LampGenericIndicators(LABEL, types, storage, display, x, y, WIDTH, -215, parent) {
}
