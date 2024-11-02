#include "sl_generic_channel.h"

namespace Io {

GenericChannel::GenericChannel(ValueStorage& storage): _pauseMs(50), _storage(storage), _conwayer(storage) {
    _running.store(false);
    _opened.store(false);
}

GenericChannel::~GenericChannel() {
    stop();
    close();
}

void GenericChannel::runnerProc() {
    std::vector<uint8_t> data;
    while(_running.load()) {
        //if (getData(data) && _cb)
        //    _cb(data);
        if (getData(data))
            _conwayer.process((const char *) data.data(), data.size());

        std::this_thread::sleep_for(std::chrono::microseconds(_pauseMs));
    }
}

void GenericChannel::start() {
    if (!_running.load()) {
        _running.store(true);
        _runner = std::thread([this]() { runnerProc(); });
    }
}

void GenericChannel::stop() {
    if (_running.load())
        _running.store(false);

    if (_runner.joinable())
        _runner.join();
}

bool GenericChannel::open() {
    if (!_opened.load())
        _opened.store(true);

    return _opened.load();
}

bool GenericChannel::close() {
    if (_opened.load())
        _opened.store(false);

    return !_opened.load();
}

}