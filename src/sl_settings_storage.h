#pragma once

#include <atomic>

class SettingsStorage {
    public:
        SettingsStorage();

        bool showNames() const { return _showNames.load(); }
        void enableNameShow(bool enable) { _showNames.store(enable); }
        void toggleNameShow() { _showNames.store(!_showNames.load()); }

    private:
        std::atomic_bool _showNames;
};
