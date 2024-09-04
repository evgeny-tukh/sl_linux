#pragma once

#include <thread>
#include <vector>
#include <atomic>
#include <cstdint>
#include <functional>
#include <string>

namespace Io {

struct GenericConfig {
    uint8_t type;
};

class GenericChannel {
    public:
        using Cb = std::function<void(std::vector<uint8_t>&)>;

        GenericChannel();
        virtual ~GenericChannel();

        virtual void configure(const GenericConfig *cfg) {}
        
        void start();
        void stop();

        void setReadCb(Cb cb) { _cb = cb; }

        void setPauseMs(uint32_t pause) { _pauseMs = pause; }

    protected:
        uint32_t _pauseMs;
        std::atomic_bool _running;
        std::atomic_bool _opened;
        std::thread _runner;
        Cb _cb;

        virtual bool open();
        virtual bool close();

        void runnerProc();

        virtual bool getData(std::vector<uint8_t>& data) { return false; }
};

}