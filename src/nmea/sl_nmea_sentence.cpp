#include "sl_defs.h"
#include "sl_nmea_sentence.h"

namespace Nmea {

bool Sentence::getDouble(size_t index, double& value) const {
    if (omitted(index))
        return false;

    value = _parser.asDouble(index);

    return true;
}

bool Sentence::getInt(size_t index, int& value) const {
    if (omitted(index))
        return false;

    value = _parser.asInt(index);

    return true;
}

bool Sentence::getChar(size_t index, char& value) const {
    if (omitted(index))
        return false;

    value = _parser.asChar(index);

    return true;
}

bool Sentence::getString(size_t index, std::string& value) const {
    if (omitted(index))
        return false;

    value = _parser.asString(index);

    return true;
}

bool Sentence::getUtc(size_t index, SL::Utc& value) const {
    if (omitted(index))
        return false;

    std::string utc = _parser.asString(index);

    if (utc.length() == 6 || utc.length() == 9 && utc[6] == '.') {
        for (size_t i = 0; i < utc.length(); ++ i) {
            if (i != 6 && !isdigit(utc[i]))
                return false;
        }
    } else {
        return false;
    }

    value.hour = SL::chars2dec(utc[0], utc[1]);
    value.min = SL::chars2dec(utc[2], utc[3]);
    value.sec = SL::chars2dec(utc[4], utc[5]);

    if (utc[6] == '.')
        value.msec = SL::chars2dec(utc[7], utc[8]) * 10;

    return true;
}

bool Sentence::getDate(size_t index, SL::Date& value) const {
    if (omitted(index))
        return false;

    std::string date = _parser.asString(index);

    if (date.length() == 6) {
        for (size_t i = 0; 6; ++ i) {
            if (isdigit(date[i]))
                return false;
        }
    } else {
        return false;
    }

    value.day = SL::chars2dec(date[0], date[1]);
    value.month = SL::chars2dec(date[2], date[3]);
    value.year = SL::chars2dec(date[4], date[5]) + 2000;

    return true;
}

bool Sentence::getLat(size_t index, double& value) const {
    if (omitted(index) || omitted(index + 1) || _parser.asChar(index + 1) != 'N' && _parser.asChar(index + 1) != 'S')
        return false;

    std::string coord = _parser.asString(index);

    if (coord.length() < 6 || coord[4] != '.')
        return false;

    for (size_t i = 0; i < coord.length(); ++i) {
        if (i != 4 && !isdigit(coord[i]))
            return false;
    }

    double deg = SL::chars2dec(coord[0], coord [1]);
    double min = atof(coord.c_str() + 2);

    value = deg + min / 60.0;

    if (_parser.asChar(index + 1) == 'S')
        value = - value;

    return true;
}

bool Sentence::getLon(size_t index, double& value) const {
    if (omitted(index) || omitted(index + 1) || _parser.asChar(index + 1) != 'E' && _parser.asChar(index + 1) != 'W')
        return false;

    std::string coord = _parser.asString(index);

    if (coord.length() < 7 || coord[5] != '.')
        return false;

    for (size_t i = 0; i < coord.length(); ++i) {
        if (i != 5 && !isdigit(coord[i]))
            return false;
    }

    double deg = SL::chars2dec(coord[0], coord [1], coord[2]);
    double min = atof(coord.c_str() + 3);

    value = deg + min / 60.0;

    if (_parser.asChar(index + 1) == 'W')
        value = - value;

    return true;
}

}