#pragma once

#include "sl_nmea_sentence.h"

namespace Nmea {

class HDT: public Sentence {
    public:
        HDT(const Parser& parser): Sentence(parser) {}

        bool valid() const override {
            return Sentence::valid() && _parser.size() > 2 && !_parser.omitted(1) && !_parser.omitted(2) && _parser.asChar(2) == 'T';
        }

        double heading() const {
            return _parser.omitted(1) ? 0.0 : atof(_parser.asString(1).c_str());
        }
};


}
