#pragma once

#include "sl_nmea_sentence.h"

namespace Nmea {

class TTM: public Sentence {
    public:
        TTM(const Parser& parser): Sentence(parser) {}

        bool valid() const override;

        int targetID() const {
            return _parser.asInt(1);
        }

        double range() const {
            return _parser.asDouble(2);
        }

        double bearing() const {
            return _parser.asDouble(3);
        }

        bool isTrueBearing() const {
            return _parser.asChar(4) == 'T';
        }

        bool isRelativeBearing() const {
            return _parser.asChar(4) == 'R';
        }

        double speed() const {
            return _parser.asDouble(5);
        }

        double course() const {
            return _parser.asDouble(6);
        }

        bool isTrueCourse() const {
            return _parser.asChar(7) == 'T';
        }

        bool isRelativeCourse() const {
            return _parser.asChar(7) == 'R';
        }

        std::string name() const {
            return _parser.asString(11);
        }

        bool lost() const {
            return _parser.asChar(12) == 'L';
        }

        bool tracking() const {
            return _parser.asChar(12) == 'T';
        }

        bool queried() const {
            return _parser.asChar(12) == 'Q';
        }

        bool reference() const {
            return _parser.asChar(13) == 'R';
        }
};


}
