#pragma once

#include <sl_defs.h>
#include <time.h>

#include "sl_nmea_sentence.h"

namespace Nmea {

class GLL: public Sentence {
    public:
        GLL(const Parser& parser): Sentence(parser) {}

        bool valid() const override;

        bool getLat(double&) const;
        bool getLon(double&) const;
        bool getUtc(SL::Utc&) const;
        bool getMode(char&) const;
};


}
