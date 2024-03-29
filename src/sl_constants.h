#pragma once

namespace Types {

enum class DataType {
    HDG,
    COG,
    STW,
    SOG,
    LAT,
    LON,
    BRG_1,
    BRG_2,
    BRG_3,
};

}

namespace TextConstants {

extern const char *HDG;
extern const char *COG;
extern const char *STW;
extern const char *SOG;
extern const char *LAT;
extern const char *LON;
extern const char *BRG_1;
extern const char *BRG_2;
extern const char *BRG_3;

}

const char *getDataTypeName(Types::DataType);
