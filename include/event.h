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
    // Add you own event here
    STOP,
};

struct EventPayload
{
    EventType type;
    std::any data;
};

/**
 * @brief Main thread-safe event handler. You can set a custom function in it that will be called once the
 * loop is starting. It is recommended to run the eventhandler in a separated thread.
 *
 * Each event that is added or handled is thread safe.
 */
class EventHandler
{
public:
    EventHandler();

    /**
     * @brief setting the function to be called in the loop.
     *
     * @param function
     */
    void set_handler(std::function<void(EventHandler &, const EventPayload &)> function);

    /**
     * @brief Blocking loop function that will run the handled events.
     */
    void loop();

    /**
     * @brief Stopping the currently running loop.
     */
    void stop();

private:
    friend class EventPage;
    void add_event(const EventPayload &payload);
    bool _is_running;
    std::function<void(EventHandler &, const EventPayload &)> _handler;
    std::deque<EventPayload> _event_buffer;
    std::mutex _mutex;
};

/**
 * @brief inherited by any class that wants to send an event with a proper payload.
 * Each event handler linked is independent.
 */
class EventPage
{
public:
    /**
     * @brief Creating the event object with its proper handler
     *
     * @param EventHandler& the handler reference.
     */
    EventPage(EventHandler &eventhandler);

    /**
     * @brief sending an event with a proper payload.
     *
     * @param EventPayload payload
     */
    void send_event(const EventPayload &payload);

    /**
     * @brief sending an event with a proper payload.
     *
     * @param EventType type of the payload
     * @param std::any the data in the payload
     */
    void send_event(const EventType &type, std::any data = {});

private:
    EventHandler &_event_handler;
};

#endif // HEADER_EVENT_FTXUI