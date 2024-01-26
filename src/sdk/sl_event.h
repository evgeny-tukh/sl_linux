#pragma once

#include <cstdint>
#include <functional>

namespace Ui {

struct Event {
    enum class Type {
        Unknown = 0,
        Command,
    };

    typedef std::function<void(Event&)> EventHandler;
    
    Type type;
    uint16_t id;
    uint64_t serial;
    EventHandler handler;

    static EventHandler defEventHandler;

    static uint64_t count;

    Event(Type, EventHandler = defEventHandler);
    Event();

    void runHandler();
};

void pushEvent(Event& event);
bool popEvent(Event& event);

}
