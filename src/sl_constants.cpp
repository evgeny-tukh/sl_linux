#include "sl_constants.h"

const char *TextConstants::HDG {"HDG"};
const char *TextConstants::COG {"COG"};
const char *TextConstants::STW {"STW"};
const char *TextConstants::SOG {"SOG"};
const char *TextConstants::LAT {"LATITUDE"};
const char *TextConstants::LON {"LONGITUDE"};
const char *TextConstants::BRG_1 {"BRG_1"};
const char *TextConstants::BRG_2 {"BRG_2"};
const char *TextConstants::BRG_3 {"BRG_3"};
const char *TextConstants::INFO {"INFO"};

const char *getDataTypeName(Types::DataType type) {
    switch (type) {
        case Types::DataType::HDG: return TextConstants::HDG;
        case Types::DataType::COG: return TextConstants::COG;
        case Types::DataType::STW: return TextConstants::STW;
        case Types::DataType::SOG: return TextConstants::SOG;
        case Types::DataType::LAT: return TextConstants::LAT;
        case Types::DataType::LON: return TextConstants::LON;
        case Types::DataType::BRG_1: return TextConstants::BRG_1;
        case Types::DataType::BRG_2: return TextConstants::BRG_2;
        case Types::DataType::BRG_3: return TextConstants::BRG_3;
        default: return "";        
    }
}

