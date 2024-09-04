#pragma once

#include "sl_nmea_parser.h"

namespace Nmea {

class Sentence {
    public:
        Sentence(const Parser& parser): _parser(parser) {}

        bool valid() const {
            return _parser.valid();
        }

        std::string type() const {
            return _parser.type();
        }

        size_t size() {
            return _parser.size();
        }

    protected:
        const Parser& _parser;
};

}
