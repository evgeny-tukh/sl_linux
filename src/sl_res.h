#pragma once

#include <cstdint>

namespace Ui {

enum class Resources: uint16_t {
    IncreaseRange = 100,
    DecreaseRange,
    SeacrhMaster,
    ToggleName,
    ToggleHarbourMode,
    Settings,
    RangeExt,
    RangeRed,
    ScanExt,
    ScanRed,
    LightOn,
    LightOff,
    IncreaseDimmer,
    DecreaseDimmer,

    Hello,
    HDG,
    COG,
    STW,
    SOG,
    LAT,
    LON,

    LAMP_BRGS,
    LAMP_IDS,
    LAMP_STATUSES,
};

}
