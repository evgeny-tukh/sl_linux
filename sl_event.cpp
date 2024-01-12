#include <queue>
#include <memory>

#include "sl_event.h"

namespace Ui {

uint64_t Event::count = 0;
Event::EventHandler Event::defEventHandler = [] (Event&) {};

Event::Event(Type evtType, EventHandler evtHandler): type(evtType), serial(++count), handler(evtHandler) {
}

Event::Event(): type(Event::Type::Unknown), serial(0), handler(Event::defEventHandler) {
}

void Event::runHandler() {
    handler(*this);
}

class EventProcessor {
    public:
        void pushEvent(Event& event) {
            _queue.push(std::move(event));
        }
        bool popEvent(Event& event) {
            if (_queue.empty())
                return false;
            
            event = _queue.front();
            _queue.pop();
            return true;
        }

    private:
        std::queue<Event> _queue;
};

EventProcessor *getEventProcessor() {
    static std::shared_ptr<EventProcessor> eventProcessor;

    if (!eventProcessor)
        eventProcessor = std::make_shared<EventProcessor>();

    return eventProcessor.get();
}

void pushEvent(Event& event) {
    auto eventProcessor = getEventProcessor();

    if (eventProcessor)
        eventProcessor->pushEvent(event);
}

bool popEvent(Event& event) {
    auto eventProcessor = getEventProcessor();

    if (!eventProcessor)
        return false;

    return eventProcessor->popEvent(event);
}

}
