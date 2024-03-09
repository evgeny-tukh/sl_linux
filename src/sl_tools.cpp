#include <math.h>

#include "sl_tools.h"

std::string Tools::formatAngle(double angle) {
    int angleInt = (int) (angle * 10.0);

    while (angleInt < 0)
        angleInt += 3600;
    while (angleInt >= 3600)
        angleInt -= 3600;

    std::string result;

    for (int weight = 1000; weight > 0; weight = weight / 10) {
        if (angleInt >= weight) {
            result += angleInt / weight + '0';
            angleInt = angleInt % weight;
        } else {
            result += '0';
        }

        if (weight == 10)
            result += '.';
    }

    return result + '\xb0';
}

std::string Tools::formatMinutes(double value) {
    if (value < 0.0 || value >= 60.0)
        return "";

    int valueInt = (int) (value * 1000.0);

    std::string result;

    for (int weight = 10000; weight > 0; weight = weight / 10) {
        if (valueInt >= weight) {
            result += valueInt / weight + '0';
            valueInt = valueInt % weight;
        } else {
            result += '0';
        }

        if (weight == 1000)
            result += '.';
    }

    return result;
}

std::string Tools::formatInt(int value, int numOfDigits) {
    std::string result = std::to_string(value);

    while (result.length() < numOfDigits)
        result.insert(result.begin(), '0');

    return result;
}

std::string Tools::formatLat(double value) {
    double absValue = fabs(value);
    int deg = (int) absValue;
    double min = (absValue - (double) deg) * 60.0;
    std::string result = formatInt(deg, 2) + " " + formatMinutes(min);

    if (value < 0.0)
        result += 'S';
    else
        result += 'N';

    return result;
}

std::string Tools::formatLon(double value) {
    double absValue = fabs(value);
    int deg = (int) absValue;
    double min = (absValue - (double) deg) * 60.0;
    std::string result = formatInt(deg, 3) + " " + formatMinutes(min);

    if (value < 0.0)
        result += 'W';
    else
        result += 'E';

    return result;
}