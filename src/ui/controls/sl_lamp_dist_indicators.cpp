#include <array>
#include <sl_value_storage.h>
#include <sl_ui_button.h>

#include "sl_lamp_dist_indicators.h"

namespace {
const char *LABEL { "DIST" };
const int WIDTH = 80;
const int HEIGHT = 35;
}

LampGenericIndicators::Types types {
    Types::DataType::DIST_1,
    Types::DataType::DIST_2,
    Types::DataType::DIST_3,
};

LampDistIndicators::LampDistIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent):
    LampGenericIndicators(LABEL, types, storage, display, x, y, WIDTH, -110, parent) {
}
