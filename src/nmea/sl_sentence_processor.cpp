#include <string>

#include "sl_nmea_parser.h"
#include "sl_hdt_sentence.h"
#include "sl_gll_sentence.h"
#include "sl_vdm_sentence.h"
#include "sl_nmea_parser.h"

#include <sl_value_storage.h>

namespace Nmea {

void processSentence(const char *nmea, size_t size, ValueStorage& storage) {
    if (nmea && size > 0) {
        std::string source(nmea, nmea + size);
        Nmea::Parser parser(source.c_str());

        if (parser.size() > 0) {
            auto type = parser.type();

            if (type.compare("HDT") == 0) {
                Nmea::HDT hdt(parser);

                if (hdt.valid())
                    storage.setValue(Types::DataType::HDG, hdt.heading(), ValueStorage::Format::Angle);
            } else if (type.compare("GLL") == 0) {
                Nmea::GLL gll(parser);

                if (gll.valid()) {
                    double lat, lon;

                    if (gll.getLat(lat) && gll.getLon(lon)) {
                        storage.setValue(Types::DataType::LAT, lat, ValueStorage::Format::Lat);
                        storage.setValue(Types::DataType::LON, lon, ValueStorage::Format::Lon);
                    }
                }
            } else if (type.compare("VDM") == 0) {
                Nmea::VDM vdm(parser);

                if (vdm.valid()) {
                }
            }
        }
    }
}

}
