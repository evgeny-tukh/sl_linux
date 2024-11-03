#include <string>

#include "sl_nmea_parser.h"
#include "sl_hdt_sentence.h"
#include "sl_gll_sentence.h"
#include "sl_vdm_sentence.h"
#include "sl_ttm_sentence.h"
#include "sl_nmea_parser.h"

#include <sl_value_storage.h>
#include "sl_sentence_conwayer.h"
#include <sl_target.h>
#include <sl_geo.h>

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

Conwayer::Conwayer(ValueStorage& storage): _storage(storage) {
    _lines.emplace(std::pair<std::string, std::function<void()>>("GLL", [this] () { processGLL(); }));
    _lines.emplace(std::pair<std::string, std::function<void()>>("HDT", [this] () { processHDT(); }));
    _lines.emplace(std::pair<std::string, std::function<void()>>("VDM", [this] () { processVDM(); }));
    _lines.emplace(std::pair<std::string, std::function<void()>>("TTM", [this] () { processTTM(); }));
}

void Conwayer::process(const char *nmea, size_t size) {
    std::string source(nmea, nmea + size);

    _parser.parse(source.c_str());

    if (_parser.valid()) {
        auto linePos = _lines.find(_parser.type());

        if (linePos != _lines.end()) {
            linePos->second();
        }
    }
}

void Conwayer::processGLL() {
    Nmea::GLL gll(_parser);

    if (gll.valid()) {
        double lat, lon;

        if (gll.getLat(lat) && gll.getLon(lon)) {
            _storage.setValue(Types::DataType::LAT, lat, ValueStorage::Format::Lat);
            _storage.setValue(Types::DataType::LON, lon, ValueStorage::Format::Lon);
        }
    }
}

void Conwayer::processHDT() {
    Nmea::HDT hdt(_parser);

    if (hdt.valid())
        _storage.setValue(Types::DataType::HDG, hdt.heading(), ValueStorage::Format::Angle);
}

void Conwayer::processVDM() {
    Nmea::VDM vdm(_parser);

    if (vdm.valid()) {
    }
}

void Conwayer::processTTM() {
    Nmea::TTM ttm(_parser);

    if (ttm.valid()) {
        auto lock = _storage.createLock(ValueStorage::LockType::TargetTable);
        auto target = _storage.checkAddTarget(ttm.targetID(), ttm.name());

        double brg = ttm.bearing();
        double rng = ttm.range();
        double hdg = _storage.valueOf(Types::DataType::HDG, 0.0);
        double lat = _storage.valueOf(Types::DataType::LAT, 0.0);
        double lon = _storage.valueOf(Types::DataType::LON, 0.0);

        if (ttm.isRelativeBearing())
            brg += hdg;

        double targetLat, targetLon;

        Geo::Spherical::calcPosition(lat, lon, brg, rng * 1852.0, targetLat, targetLon);

        target->second.lat = targetLat;
        target->second.lon = targetLon;
        target->second.speed = ttm.speed();
        target->second.course = ttm.course();

        if (ttm.isRelativeCourse())
            target->second.course += hdg;

        if (target->second.course >= 360.0)
            target->second.course -= 360.0;

        target->second.lastUpdate = time(nullptr);
    }
}

}
