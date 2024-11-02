#include "sl_ttm_sentence.h"

namespace Nmea {

bool TTM::valid() const {
    if (!Sentence::valid() || _parser.size() <= 14)
        return false;

    for (int i = 1; i < 13; ++i) {
        if (i != 8 && i != 9 && _parser.omitted(i))
            return false;
    }

    switch (_parser.asChar(4)) {
        case 'T': case 'R': break;
        default: return false;
    }

    switch (_parser.asChar(7)) {
        case 'T': case 'R': break;
        default: return false;
    }

    switch (_parser.asChar(12)) {
        case 'Q': case 'L': case 'T': break;
        default: return false;
    }

    return true;
}

}
