#pragma once

#include <cstdint>
#include <string>
#include <time.h>

#pragma pack(1)

struct Target {
    Target(uint32_t targetID, const std::string& targetName): id(targetID), name(targetName) {}

    uint32_t id;            // for arpa target - id (0..99); for ais - mmsi
    double lat, lon;        // absolute position
    double course, speed;   // absolute data
    time_t lastUpdate;
    std::string name;
};

#pragma pack()
