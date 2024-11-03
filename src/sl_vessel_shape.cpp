#include "sl_vessel_shape.h"

namespace {

const int VESSEL_CENTER_X = 8;
const int VESSEL_CENTER_Y = 25;

const int TARGET_CENTER_X = 6;
const int TARGET_CENTER_Y = 8;

Points initVesselShape {
    {8, 0},
    {5, 1},
    {2, 4},
    {1, 6},
    {0, 9},
    {0, 45},
    {1, 47},
    {2, 48},
    {5, 49},
    {11, 49},
    {14, 48},
    {15, 47},
    {16, 45},
    {16, 9},
    {15, 6},
    {14, 4},
    {11, 1},
    {8, 0},
};

Points initTargetShape {
    {6, 0},
    {12, 16},
    {0, 16},
    {6, 0},
};

const double PI = 3.1415926535897932384626433832795;
const double DEG2RAD = PI / 180.0;
}

GenericShape::Pt::Pt(int xArg, int yArg): x(xArg), y(yArg) {
    radius = sqrt(xArg * xArg + yArg * yArg);
    angle = asin(xArg / radius);

    if (yArg < 0)
        angle = PI - angle;
}

GenericShape::GenericShape(Points& points): GenericShape(points, VESSEL_CENTER_X, VESSEL_CENTER_Y) {}

GenericShape::GenericShape(Points& points, int centerX, int centerY): _centerX(centerX), _centerY(centerY) {
    for (auto& pt: points)
        addPoint(pt.first, pt.second);
}

void GenericShape::addPoint(int x, int y) {
    _points.emplace_back((double) (_centerX - x), (double) (_centerY - y));
}

void GenericShape::getShape(double angle, int centerX, int centerY, std::vector<XPoint>& shape, double multiplicator) {
    shape.clear();

    for (auto& pt: _points) {
        double ang = pt.angle + angle * DEG2RAD;
        XPoint point;
        point.x = centerX + pt.radius * multiplicator * sin(ang);
        point.y = centerY - pt.radius * multiplicator * cos(ang);

        shape.push_back(point);
    }
}

VesselShape::VesselShape(): GenericShape(initVesselShape, VESSEL_CENTER_X, VESSEL_CENTER_Y) {
}

TargetShape::TargetShape(): GenericShape(initTargetShape, TARGET_CENTER_X, TARGET_CENTER_Y) {
}

