#ifndef HEADER_EVENT_FTXUI
#define HEADER_EVENT_FTXUI

#include <any>
#include <deque>
#include <functional>
#include <mutex>

enum class EventType : uint8_t
{
    SWITCH_SCREEN,
    SEND_TEXT,
    STOP,
};

struct EventPayload
{
    EventType type;
    std::any data;
};

class EventHandler
{
public:
    EventHandler();
    void set_handler(std::function<void(EventHandler &, const EventPayload &)> function);
    void loop();
    void stop();

protected:
    void add_event(const EventPayload &payload);
    friend class EventPage;

private:
    bool _is_running;
    std::function<void(EventHandler &, const EventPayload &)> _handler;
    std::deque<EventPayload> _event_buffer;
    std::mutex _mutex;
};

class EventPage
{
public:
    EventPage(EventHandler &eventhandler);
    void send_event(const EventPayload &payload);
    void send_event(const EventType &type, std::any data = {});

private:
    EventHandler &_event_handler;
};

#endif // HEADER_EVENT_FTXUI