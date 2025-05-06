#include <iostream>
#include <string>
#include <thread>

#include "ui.h"
#include "event.h"

using namespace ftxui;

std::thread t_instance;

static inline void handle(EventHandler &handler, const EventPayload &payload)
{
    UserInterface &ui = UserInterface::GetInstance();

    if (payload.type == EventType::STOP)
        handler.stop();
    else if (payload.type == EventType::SWITCH_SCREEN)
        ui.select_screen(std::any_cast<size_t>(payload.data));
}

int main(int argc, char **argv)
{
    // Event/Screen
    EventHandler handler;
    UserInterface &ui = UserInterface::GetInstance();

    // Page declaration
    // ScreenPageDebugger debugger(handler, screen);
    // screen.add_screen(&launcher);

    // Event handler function
    handler.set_handler(handle);

    // Main logic
    std::thread t_event(&EventHandler::loop, &handler);
    ui.start();

    // Finish
    handler.stop();
    t_event.join();
    return 0;
}