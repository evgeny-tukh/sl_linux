#include "sl_nmea_parser.h"

namespace Nmea {

Parser::Parser(const char *source): _valid(false) {
    if (!source || !*source)
        return;

    if (source[0] != '$' && source[1] != '$')
        return;

    if (!validateCrc(source))
        return;

    _parts.emplace_back();

    for (const char *ch = source; *ch && *ch != '*'; ++ ch) {
        if (*ch == ',') {
            _parts.emplace_back();
        } else {
            _parts.back().push_back(*ch);
        }
    }
}

bool Parser::isPropietary() const {
    return !_parts.empty() && !_parts.front().empty() && _parts.front().length() > 1 && _parts.front().at(1) == 'P';
}

std::string Parser::talkerID() const {
    if (_parts.empty() || _parts.front().empty())
        return std::string();

    if (_parts.front().at(1) == 'P')
        return _parts.front().substr(2, 2);

    return _parts.front().substr(1, 2);
}

std::string Parser::type() const {
    if (_parts.empty() || _parts.front().empty())
        return std::string();

    if (_parts.front().at(1) == 'P')
        return _parts.front().substr(4);

    return _parts.front().substr(3);
}

bool Parser::omitted(size_t index) const {
    return index >= _parts.size() || _parts.at(index).empty();
}

double Parser::asDouble(size_t index) const {
    return (index >= _parts.size() || _parts.at(index).empty()) ? 0.0 : atof(_parts.at(index).c_str());
}

int Parser::asInt(size_t index) const {
    return (index >= _parts.size() || _parts.at(index).empty()) ? 0 : atoi(_parts.at(index).c_str());
}

char Parser::asChar(size_t index) const {
    return (index >= _parts.size() || _parts.at(index).empty()) ? 0.0 : _parts.at(index).front();
}

std::string Parser::asString(size_t index) const {
    return (index >= _parts.size() || _parts.at(index).empty()) ? std::string() : _parts.at(index);
}

bool Parser::validateCrc(const char *source) {
    auto hex2int = [] (char digit) {
        if (digit >= '0' && digit <= '9')
            return digit - '0';
        if (digit >= 'a' && digit <= 'f')
            return digit - 'a' + 10;
        if (digit >= 'A' && digit <= 'F')
            return digit - 'A' + 10;
        return 0;
    };

    uint8_t crc = source[1];

    for (size_t i = 2; source[i]; ++i) {
        if (source[i] == '*') {
            return (hex2int(source[i+1]) * 16 + hex2int(source[i+2])) == crc;
        } else {
            crc ^= (uint8_t) source[i];
        }
    }

    return false;
}

}
