#pragma once

#include <X11/Xlib.h> 
#include <sdk/sl_wnd.h>

#include <array>

#include <sl_vessel_shape.h>
#include <sl_value_storage.h>

class TargetDisplay: public Ui::Wnd {
    public:
        TargetDisplay(ValueStorage& storage, Display *display, Window parent);

        void paint(GC ctx) override;

        //void setupLayout(int xParam = 0, int yParam = 0) override;

    private:
        ValueStorage& _storage;
        std::array<XSegment, 360> _ticks;
        std::array<XPoint, 36> _tagPos;
        std::array<double, 360> _sinuses;
        std::array<double, 360> _cosinuses;
        VesselShape _vesselShape;
        TargetShape _targetShape;

        void populateTicksArray();

        //void onSizeChanged(int width, int height, bool& notifyChildren) override;
};