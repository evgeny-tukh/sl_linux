#pragma once

#include <cstdint>
#include <string>
#include <time.h>

struct Target {
    Target(uint32_t targetID, const std::string& targetName): id(targetID), name(targetName) {}

    uint32_t id;            // for arpa target - id (0..99); for ais - mmsi
    std::string name;
    double lat, lon;        // absolute position
    double course, speed;   // absolute data
    time_t lastUpdate;
};

