# FTXUI Template

![Static Badge](https://img.shields.io/badge/builds_on-Linux-brightgreen)
![Static Badge](https://img.shields.io/badge/builds_on-Windows-brightgreen)

Template example using the [FTXUI](https://github.com/ArthurSonzogni/FTXUI) library with a proper logger, thread-safe event handler and multiple pages paradigm. This template can be used in any project and is a good way to start a project using a simple and not-so-verbose approach.

## Build the project

You can simply use CMake with the following commands:

```bash
mkdir build && cd build
cmake ..
cmake --build . --parallel
```

## Using the Interface

### Event

Main thread-safe event handler. You can set a custom function in it that will be called once the
loop is starting. It is recommended to run the eventhandler in a separated thread.

Each event that is added or handled is thread safe.

_main.cpp_
```cpp

static inline void loop_event(EventHandler &handler, const EventPayload &payload)
{
    // Called each time there is a new event in the event buffer...
}

int main(void)
{
    // Basic usage
    EventHandler handler;
    handler.set_handler(loop_event);
    Page1 page1(handler);
    // Starting the event loop in a separated thread.
    std::thread t_event(&EventHandler::loop, &handler);
    t_event.join();
    return 0;
}
```

_page1.cpp_
```cpp
void Page1::change_screen()
{
    this->send_event(EventType::SWITCH_SCREEN, static_cast<size_t>(1));
}
```

### Logger

_'Logger'_ is a general Logger that can be instanciated anywhere as a singleton. It can have a maximum size for its buffer that can be changed on the go.Each LoggerType can be gathered from each data which can lead to multiple ways to print out a log.

```cpp
Logger& logger = Logger::GetInstance();
logger.push_back("Hello, world!", LoggerType::PRINT);
// std::vector<std::string>& buffer = logger.get_buffer();
```

### UserInterface

_'UserInterface'_ is the main object that can be instanciated anywhere as a singleton you can add any pages to it and cycle through them using the select_screen function.

```cpp
UserInterface &ui = UserInterface::GetInstance();

int main(void)
{
    // Event declaration
    EventHandler handler;

    // Page declaration
    PageX pagex(handler);
    // other pages...

    ui.add_screen(&pagex);
    // other pages...

    ui.start();
    return 0;
}
```

## Creating a new page

To create a new page, just create a parent class from `Page` and create a `ftxui::Component` named `_page` in the constructor. You can follow the examples given in the [pages folder](src/pages).