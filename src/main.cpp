#include <iostream>
#include <string>
#include <thread>

#include "event.h"
#include "logger.h"
#include "ui.h"

#include "pages/page1.h"
#include "pages/page2.h"

using namespace ftxui;

UserInterface& ui = UserInterface::GetInstance();
Logger& logger = Logger::GetInstance();

static inline void loop_event(EventHandler &handler, const EventPayload &payload)
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
    Page1 page1(handler);
    Page2 page2(handler);
    ui.add_screen(&page1);
    ui.add_screen(&page2);

    // Event handler function
    handler.set_handler(loop_event);

    // Main logic
    std::thread t_event(&EventHandler::loop, &handler);
    ui.start();

    // Finish
    handler.stop();
    t_event.join();
    return 0;
}