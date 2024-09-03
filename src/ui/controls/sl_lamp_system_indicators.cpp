#include <array>
#include <sl_value_storage.h>
#include <sl_ui_button.h>

#include "sl_lamp_system_indicators.h"

namespace {
const char *LABEL { "SYSTEM" };
const int WIDTH = 120;
const int HEIGHT = 35;
}

LampGenericIndicators::Types types {
    Types::DataType::SYSTEM_1,
    Types::DataType::SYSTEM_2,
    Types::DataType::SYSTEM_3,
};

LampSystemIndicators::LampSystemIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent):
    LampGenericIndicators(LABEL, types, storage, display, x, y, WIDTH, -345, parent) {
}
