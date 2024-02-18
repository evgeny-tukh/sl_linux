#pragma once

#include <cstdint>
#include <unordered_map>

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
        bool getValue(const char *name, double& value) const;
        double valueOf(const char *name, double defValue) const;
        std::string getStringValue(const char *name) const;
        
    protected:
        std::unordered_map<std::string, std::pair<double, Format>> _values;
};

