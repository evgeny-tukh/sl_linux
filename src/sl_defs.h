#pragma once

#include <stdlib.h>
#include <ctype.h>

#include <cstdint>
#include <optional>

namespace SL {

#pragma pack(1)

inline int char2dec(char ch) {
    if  (ch >= '0' && ch <= '9')
        return ch -  '0';

    return 0;
}

inline int chars2dec(char ch1, char ch2) {
    if (isdigit (ch1) && isdigit(ch2))
        return char2dec(ch1) * 10 + char2dec(ch2);

    return 0;
}

inline int chars2dec(char ch1, char ch2, char ch3) {
    if (isdigit (ch1) && isdigit(ch2) && isdigit(ch3))
        return char2dec(ch1) * 100 + char2dec(ch2) * 10  + char2dec(ch3);

    return 0;
}

inline int chars2dec(char ch1, char ch2, char ch3, char ch4) {
    if (isdigit (ch1) && isdigit(ch2) && isdigit (ch3) && isdigit(ch4))
        return char2dec(ch1) * 100 + char2dec(ch2) * 100 + char2dec(ch3) * 10 + char2dec(ch4);

    return 0;
}

inline int str2dec (const char *str, size_t numOfChars) {
    if (!str || !*str)
        return 0;

    switch (numOfChars) {
        case 1: return char2dec(*str);
        case 2: return chars2dec(str[0], str[1]);
        case 3: return chars2dec(str[0], str[1], str[2]);
        case 4: return chars2dec(str[0], str[1], str[2], str[3]);
        default: return 0;
    }
}

union Utc {
    struct {
        uint8_t hour;
        uint8_t min;
        uint8_t sec;
        uint8_t msec;
    };

    uint32_t value;
};

union Date {
    struct {
        uint8_t day;
        uint8_t month;
        uint16_t year;
    };

    uint32_t value;
};

}
