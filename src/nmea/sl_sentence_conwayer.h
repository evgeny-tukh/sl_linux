#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include <sl_value_storage.h>
#include <nmea/sl_gll_sentence.h>
#include <nmea/sl_hdt_sentence.h>
#include <nmea/sl_vdm_sentence.h>

namespace Nmea {

void processSentence(const char *nmea, size_t size, ValueStorage& storage);

class Conwayer {
    public:
        Conwayer(ValueStorage& storage);

        void process(const char *nmea, size_t size);

    private:
        std::unordered_map<std::string, std::function<void()>> _lines;
        ValueStorage& _storage;
        Parser _parser;

        void processGLL();
        void processHDT();
        void processVDM();
};

}
