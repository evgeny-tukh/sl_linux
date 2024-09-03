#include <array>
#include <sl_value_storage.h>
#include <sl_ui_button.h>

#include "sl_lamp_status_indicators.h"

namespace {
const char *LABEL { "STATUS" };
const int WIDTH = 100;
const int HEIGHT = 35;
}

LampGenericIndicators::Types types {
    Types::DataType::STATUS_1,
    Types::DataType::STATUS_2,
    Types::DataType::STATUS_3,
};

LampStatusIndicators::LampStatusIndicators(const ValueStorage& storage, Display *display, int x, int y, Window parent):
    LampGenericIndicators(LABEL, types, storage, display, x, y, WIDTH, -20, parent) {
}
