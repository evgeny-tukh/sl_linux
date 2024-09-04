#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Nmea {

class Parser {
    public:
        Parser(const char *source);

        bool isPropietary() const;
        std::string talkerID() const;
        std::string type() const;

        bool omitted(size_t index) const;
        double asDouble(size_t index) const;
        int asInt(size_t index) const;
        char asChar(size_t index) const;
        std::string asString(size_t index) const;

        bool valid() const { return _valid; }

        size_t size() const { return _parts.size(); }
        
    protected:
        std::vector<std::string> _parts;
        bool _valid;

        static bool validateCrc(const char *source);
};

}
