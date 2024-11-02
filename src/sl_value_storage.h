#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
#include "sl_constants.h"
#include "sl_target.h"

class ValueStorage {
    public:
        enum class Format {
            Unknown = 0,
            Angle,
            Lat,
            Lon,
            Double,
            Int,
        };

        void setValue(const char *name, double value, Format format);
        void setValue(Types::DataType dataType, double value, Format format);
        bool getValue(const char *name, double& value) const;
        double valueOf(const char *name, double defValue) const;
        double valueOf(Types::DataType type, double defValue) const;
        std::string getStringValue(const char *name) const;
        std::string getStringValue(Types::DataType type) const;

        Target& checkAddTarget(uint32_t id, const std::string& name);
        void removeLostTargets();
        void enumTargets(std::function<void(const Target&)>) const;
        
    protected:
        std::unordered_map<std::string, std::pair<double, Format>> _values;
        std::unordered_map<uint32_t, Target> _targets;
};

