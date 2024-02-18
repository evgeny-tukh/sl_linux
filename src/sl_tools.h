#pragma once

#include <string>

namespace Tools {

std::string formatAngle(double value);
std::string formatMinutes(double value);
std::string formatInt(int value, int numOfDigits);
std::string formatLat(double value);
std::string formatLon(double value);

}
