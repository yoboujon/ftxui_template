#include "event.h"

#include <thread>
#include <chrono>
#include <iostream>

constexpr int64_t EVENT_LOOP_WAIT_MS = 100;

// EventPage

EventPage::EventPage(EventHandler &eventhandler)
    : _event_handler(eventhandler)
{
}

void EventPage::send_event(const EventPayload &payload)
{
    _event_handler.add_event(payload);
}

void EventPage::send_event(const EventType &type, std::any data)
{
    _event_handler.add_event({type, data});
}

// EventHandler

EventHandler::EventHandler()
    : _is_running(false), _event_buffer({})
{
}

void EventHandler::set_handler(std::function<void(EventHandler &, const EventPayload &)> function)
{
    _handler = function;
}

void EventHandler::add_event(const EventPayload &payload)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _event_buffer.push_back(payload);
}

void EventHandler::loop()
{
    _is_running = true;
    while (_is_running)
    {
        if (!_event_buffer.empty())
        {
            std::lock_guard<std::mutex> lock(_mutex);
            EventPayload evt = _event_buffer.front();
            _event_buffer.pop_front();
            _handler(*this, evt);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(EVENT_LOOP_WAIT_MS));
    }
}

void EventHandler::stop()
{
    _is_running = false;
}
