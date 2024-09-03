#pragma once

#include <vector>
#include <array>
#include <math.h>

#include <X11/Xlib.h> 

class VesselShape {
    public:
        struct Pt {
            Pt(int xArg, int yArg);
            double x;
            double y;
            double radius;
            double angle;
        };

        VesselShape();
        VesselShape(int centerX, int centerY);

        void getShape(double angle, int centerX, int centerY, std::vector<XPoint>& shape, double multiplicator = 1);

    private:
        int _centerX;
        int _centerY;

        std::vector<Pt> _points;
        std::array<std::pair<double, double>, 360> _sinCosTable;

        void addPoint(int x, int y);
};