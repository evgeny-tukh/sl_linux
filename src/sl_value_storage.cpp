#include "sl_value_storage.h"
#include "sl_tools.h"

void ValueStorage::setValue(const char *name, double value, Format format) {
    auto pos = _values.find(name);

    if (pos == _values.end()) {
        _values.emplace(std::pair<std::string, std::pair<double, Format>>(name, std::pair<double, Format>(value, format)));
    } else {
        pos->second.first = value;
    }
}

std::string ValueStorage::getStringValue(const char *name) const {
    auto pos = _values.find(name);

    if (pos == _values.end())
        return "N/A";

    switch (pos->second.second) {
        case Format::Angle:
            return Tools::formatAngle(pos->second.first);
        case Format::Lat:
            return Tools::formatLat(pos->second.first);
        case Format::Lon:
            return Tools::formatLon(pos->second.first);
        case Format::Double:
            return std::to_string(pos->second.first);
        case Format::Int:
            return std::to_string((int) pos->second.first);
        default:
            return "N/A";
    }
}

bool ValueStorage::getValue(const char *name, double& value) const {
    auto pos = _values.find(name);

    if (pos == _values.end())
        return false;

    value = pos->second.first;

    return true;
}

double ValueStorage::valueOf(const char *name, double defValue) const {
    auto pos = _values.find(name);

    if (pos == _values.end())
        return defValue;

    return pos->second.first;
}
