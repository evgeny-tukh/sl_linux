#pragma once

#include <thread>
#include <vector>
#include <atomic>
#include <cstdint>
#include <functional>
#include <string>

#include <sl_value_storage.h>
#include <nmea/sl_sentence_conwayer.h>

namespace Io {

struct GenericConfig {
    uint8_t type;
};

class GenericChannel {
    public:
        using Cb = std::function<void(std::vector<uint8_t>&)>;

        GenericChannel(ValueStorage&);
        virtual ~GenericChannel();

        virtual void configure(const GenericConfig *cfg) {}
        
        void start();
        void stop();

        void setReadCb(Cb cb) { _cb = cb; }

        void setPauseMs(uint32_t pause) { _pauseMs = pause; }

        virtual bool open();
        virtual bool close();

    protected:
        ValueStorage& _storage;
        Nmea::Conwayer _conwayer;
        uint32_t _pauseMs;
        std::atomic_bool _running;
        std::atomic_bool _opened;
        std::thread _runner;
        Cb _cb;

        void runnerProc();

        virtual bool getData(std::vector<uint8_t>& data) { return false; }
};

}