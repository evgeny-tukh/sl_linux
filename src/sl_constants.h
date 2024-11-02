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
    ID_1,
    ID_2,
    ID_3,
    STATUS_1,
    STATUS_2,
    STATUS_3,
    DIST_1,
    DIST_2,
    DIST_3,
    FOCUS_1,
    FOCUS_2,
    FOCUS_3,
    SYSTEM_1,
    SYSTEM_2,
    SYSTEM_3,

    DSPLY_RNG,
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
extern const char *INFO;

extern const char *DSPLY_RNG;

}

const char *getDataTypeName(Types::DataType);
