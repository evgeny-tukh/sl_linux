#pragma once

#include <sl_value_storage.h>

namespace Nmea {

void processSentence(const char *nmea, size_t size, ValueStorage& storage);

}
