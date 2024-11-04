#pragma once

#include <X11/Xlib.h> 
#include <sdk/sl_wnd.h>

#include <array>

#include <sl_vessel_shape.h>
#include <sl_value_storage.h>
#include <sl_target.h>
#include <sl_settings_storage.h>

class TargetDisplay: public Ui::Wnd {
    public:
        TargetDisplay(ValueStorage& storage, SettingsStorage& settings, Display *display, Window parent);

        void paint(GC ctx) override;

        //void setupLayout(int xParam = 0, int yParam = 0) override;

    private:
        struct TargetDrawContext {
            double lat, lon, hdg, displayRng;
            bool showNames;

            TargetDrawContext(ValueStorage& storage, SettingsStorage& settings) {
                auto lock = storage.createLock(ValueStorage::LockType::Values);
                
                lat = storage.valueOf(Types::DataType::LAT, 0.0);
                lon = storage.valueOf(Types::DataType::LON, 0.0);
                hdg = storage.valueOf(Types::DataType::HDG, 0.0);
                displayRng = storage.valueOf(Types::DataType::DSPLY_RNG, 0.0);
                showNames = settings.showNames();
            }
        };

        ValueStorage& _storage;
        SettingsStorage& _settings;
        std::array<XSegment, 360> _ticks;
        std::array<XPoint, 36> _tagPos;
        std::array<double, 360> _sinuses;
        std::array<double, 360> _cosinuses;
        VesselShape _vesselShape;
        TargetShape _targetShape;

        void populateTicksArray();

        void drawTarget(const Target& target, GC ctx, const TargetDrawContext& trgDrawCtx);

        //void onSizeChanged(int width, int height, bool& notifyChildren) override;
};