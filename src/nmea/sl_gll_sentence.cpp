#include "sl_gll_sentence.h"

namespace Nmea {

bool GLL::valid() const {
    if (!Sentence::valid() || size() < 8)
        return false;

    for (size_t i = 1; i < 6; ++i) {
        if (omitted(i))
            return false;
    }

    //if (_parser.asChar(6) != 'A')
    //    return false;

    switch (_parser.asChar(7)) {
        case 'A':
        case 'D':
        case 'S':
            return true;
        default:
            return false;
    }
}

bool GLL::getLat(double& lat) const {
    return Sentence::getLat(1, lat);
}

bool GLL::getLon(double& lon) const {
    return Sentence::getLon(3, lon);
}

bool GLL::getUtc(SL::Utc& utc) const {
    return Sentence::getUtc(5, utc);
}

bool GLL::getMode(char& mode) const {
    return Sentence::getChar(7, mode);
}

}
