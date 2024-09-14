#pragma once

#include "sl_nmea_sentence.h"

namespace Nmea {

class VDM: public Sentence {
    public:
        VDM(const Parser& parser): Sentence(parser) {}

        bool valid() const override {
            return Sentence::valid() && _parser.size() > 5 && !_parser.omitted(1) && !_parser.omitted(4);
        }

        int getNumericField(int index) const {
            int result;

            if (getInt(1, result))
                return result;

            return 0;
        }

        int numOfChunks() const {
            return getNumericField(1);
        }

        int chunkIndex() const {
            return getNumericField(2);
        }

        int seqId() const {
            return getNumericField(3);
        }

        int numOfFillBits() const {
            return getNumericField(5);
        }

        std::string payload() const {
            std::string result;

            getString(4, result);

            return result;
        }
};


}
