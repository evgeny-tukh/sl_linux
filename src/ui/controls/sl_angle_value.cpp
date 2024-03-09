#include "sl_angle_value.h"

AngleValue::AngleValue(Display *display, Getter getter, int x, int y, Window parent): Value(display, getter, x, y, parent, "", "\xb0") {}
