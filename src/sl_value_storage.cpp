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

void ValueStorage::setValue(Types::DataType dataType, double value, Format format) {
    auto name = getDataTypeName(dataType);
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

std::string ValueStorage::getStringValue(Types::DataType type) const {
    return getStringValue(getDataTypeName(type));
}

bool ValueStorage::getValue(const char *name, double& value) const {
    auto pos = _values.find(name);

    if (pos == _values.end())
        return false;

    value = pos->second.first;

    return true;
}

double ValueStorage::valueOf(Types::DataType type, double defValue) const {
    return valueOf(getDataTypeName(type), 0.0);
}

double ValueStorage::valueOf(const char *name, double defValue) const {
    auto pos = _values.find(name);

    if (pos == _values.end())
        return defValue;

    return pos->second.first;
}

ValueStorage::TargetTable::iterator ValueStorage::checkAddTarget(uint32_t id, const std::string& name) {
    auto pos = _targets.find(id);

    if (pos == _targets.end())
        pos = _targets.emplace(std::pair<uint32_t, Target>(id, Target(id, name))).first;

    return pos;
}

void ValueStorage::removeLostTargets() {
    Locker lock(_trgTableLocker);
}

void ValueStorage::enumTargets(std::function<void(Target&)> cb) {
    Locker lock(_trgTableLocker);
    for (auto targetItem: _targets) {
        cb(targetItem.second);
    }
}

std::shared_ptr<ValueStorage::Locker> ValueStorage::createLock(ValueStorage::LockType type) {
    switch (type) {
        case ValueStorage::LockType::Values: return std::make_shared<Locker>(_valuesLocker);
        case ValueStorage::LockType::TargetTable: return std::make_shared<Locker>(_trgTableLocker);
        default: return std::shared_ptr<Locker>();
    }
}