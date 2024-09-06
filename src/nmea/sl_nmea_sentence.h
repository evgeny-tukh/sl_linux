#pragma once

#include "sl_nmea_parser.h"
#include "sl_defs.h"

namespace Nmea {

class Sentence {
    public:
        Sentence(const Parser& parser): _parser(parser) {}

        virtual bool valid() const {
            return _parser.valid();
        }

        std::string type() const {
            return _parser.type();
        }

        size_t size() const {
            return _parser.size();
        }

        bool omitted(size_t index) const {
            return _parser.omitted(index);
        }

        bool getDouble(size_t index, double& value) const;
        bool getInt(size_t index, int& value) const;
        bool getChar(size_t index, char& value) const;
        bool getString(size_t index, std::string& value) const;
        bool getUtc(size_t index, SL::Utc& value) const;
        bool getDate(size_t index, SL::Date& value) const;
        bool getLat(size_t index, double& value) const;
        bool getLon(size_t index, double& value) const;

    protected:
        const Parser& _parser;
};

}
