#include <math.h>

namespace Geo {

const double EARTH_RADIUS = 6366707.0194937074958298109629434;
const double Pi = 3.1415926535897932384626433832795;
const double TwoPi = Pi + Pi;

inline double toRad(double arg) { return arg * Pi / 180.0; }
inline double toDeg(double arg) { return arg * 180.0 / Pi; }

namespace Spherical {

double calcRange(double lat1, double lon1, double lat2, double lon2) {
    double latRad1 = toRad(lat1);
    double latRad2 = toRad(lat2);
    double lonRad1 = toRad(lon1);
    double lonRad2 = toRad(lon2);

    return (acos(sin(latRad1) * sin(latRad2) + cos(latRad1) * cos(latRad2) * cos(lonRad1 - lonRad2)) * EARTH_RADIUS);
}

double calcBearing(double lat1, double lon1, double lat2, double lon2) {
    double latRad1 = toRad(lat1);
    double latRad2 = toRad(lat2);
    double lonRad1 = toRad(lon1);
    double lonRad2 = toRad(lon2);
    double deltaLonW = fmod(lonRad1 - lonRad2, TwoPi);
    double deltaLonE = fmod(lonRad2 - lonRad1, TwoPi);
    double bearing;

    if (fabs(latRad1 - latRad2) < 1.0E-8) {
        // Same latitude, bearing is 90 or 270 deg
        bearing = (deltaLonW > deltaLonE) ? Pi * 1.5 : Pi * 0.5;
    } else {
        double tanRatio = tan(latRad2 * 0.5 + Pi * 0.25) / tan(latRad1 * 0.5 + Pi * 0.25);
        double deltaLat = log(tanRatio);

        bearing = (deltaLonW < deltaLonE) ? fmod(atan2(- deltaLonW, deltaLat), TwoPi) : fmod(atan2(deltaLonE, deltaLat), TwoPi);
    }

    return toDeg(bearing);
}

void calcPosition(double lat, double lon, double bearing, double range, double& destLat, double& destLon) {
    double latRad = toRad(lat);
    double lonRad = toRad(lon);
    double brgRad = toRad(bearing);
    double arcAngle = range / EARTH_RADIUS;
    double arcSin = sin(arcAngle);
    double arcCos = cos(arcAngle);
    double latSin = sin(latRad);
    double latCos = cos(latRad);

    destLat = asin(latSin * arcCos + latCos * arcSin * cos(brgRad));
    destLon = lonRad + atan2(sin(brgRad) * arcSin * latCos, arcCos - latSin * sin(destLat));

    destLat *= 180.0 / Pi;
    destLon *= 180.0 / Pi;
}

}
}