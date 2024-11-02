#pragma once

namespace Geo {
namespace Spherical {

double calcRange(double lat1, double lon1, double lat2, double lon2);

inline double calcRangeNm(double lat1, double lon1, double lat2, double lon2) {
    return calcRange(lat1, lon1, lat2, lon2) / 1852.0;
}

double calcBearing(double lat1, double lon1, double lat2, double lon2);

void calcPosition(double lat, double lon, double bearing, double range, double& destLat, double& destLon);

inline void calcPositionNm(double lat, double lon, double bearing, double range, double& destLat, double& destLon) {
    calcPosition(lat, lon, bearing, range * 1852.0, destLat, destLon);
}

}
}
