#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <memory>
#include "sl_constants.h"
#include "sl_target.h"

class ValueStorage {
    public:
        enum class Format {
            Unknown = 0,
            Angle,
            Lat,
            Lon,
            Double,
            Int,
        };

        enum class LockType {
            Values,
            TargetTable,
        };

        using TargetTable = std::unordered_map<uint32_t, Target>;

        class Locker {
            public:
                Locker(std::mutex& mutex): _lock(mutex) {
                }

            private:
                std::lock_guard<std::mutex> _lock;
        };

        void setValue(const char *name, double value, Format format);
        void setValue(Types::DataType dataType, double value, Format format);
        bool getValue(const char *name, double& value) const;
        double valueOf(const char *name, double defValue) const;
        double valueOf(Types::DataType type, double defValue) const;
        std::string getStringValue(const char *name) const;
        std::string getStringValue(Types::DataType type) const;

        TargetTable::iterator checkAddTarget(uint32_t id, const std::string& name);
        void removeLostTargets();
        void enumTargets(std::function<void(Target&)>);

        std::shared_ptr<Locker> createLock(LockType type);

    protected:
        TargetTable _targets;
        std::mutex _valuesLocker, _trgTableLocker;
        std::unordered_map<std::string, std::pair<double, Format>> _values;
};

