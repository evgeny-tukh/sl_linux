#include "sl_constants.h"

const char *TextConstants::HDG {"HDG"};
const char *TextConstants::COG {"COG"};
const char *TextConstants::STW {"STW"};
const char *TextConstants::SOG {"SOG"};
const char *TextConstants::LAT {"LATITUDE"};
const char *TextConstants::LON {"LONGITUDE"};

const char *getDataTypeName(Types::DataType type) {
    switch (type) {
        case Types::DataType::HDG: return TextConstants::HDG;
        case Types::DataType::COG: return TextConstants::HDG;
        case Types::DataType::STW: return TextConstants::HDG;
        case Types::DataType::SOG: return TextConstants::HDG;
        case Types::DataType::LAT: return TextConstants::HDG;
        case Types::DataType::LON: return TextConstants::HDG;
        default: return "";        
    }
}

