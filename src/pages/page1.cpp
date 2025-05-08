#include "pages/page1.h"

#include "logger.h"
#include "ui.h"

#include <ctime>
#include <cstring>
#include <cstdint>
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

constexpr uint8_t LOGGER_OFFSET = 7;
static UserInterface &ui = UserInterface::GetInstance();
static Logger &logger = Logger::GetInstance();
static char time_buffer[11];

inline static const char *get_time_str(uint64_t epoch)
{
    std::tm epoch_time;
    const std::time_t time_epoch = epoch;
    memcpy(&epoch_time, localtime(&time_epoch), sizeof(struct tm));
    snprintf(time_buffer, 12, "[%02d:%02d:%02d]", epoch_time.tm_hour, epoch_time.tm_min, epoch_time.tm_sec);
    return time_buffer;
}

inline ftxui::Element Page1::transform(ftxui::InputState state)
{
    if (state.is_placeholder)
        state.element |= dim;

    if (state.focused)
    {
        state.element |= color(Color::White);
        _input_selected = true;
    }
    else
    {
        _input_selected = false;
    }

    return state.element;
}

inline bool Page1::catch_event(Event event)
{
    if (event.is_character())
    {
        // Checking if it is a command...
    }

    const int size = ui.get_screen()->dimy();
    logger.set_max_size(size - LOGGER_OFFSET);
    if (event == Event::Return)
    {
        logger.push_back(_input_str, LoggerType::PRINT);
    }
    return (event == Event::Return);
}

ftxui::Element Page1::render_input()
{
    Element arrow = text("> ");
    if (_input_selected)
        arrow |= bgcolor(Color::White) | color(Color::Black);
    else
        arrow |= color(Color::Default) | bgcolor(Color::Default);

    return vbox({separatorEmpty(),
                 text("Send a command"),
                 hbox({arrow,
                       _input_component->Render()})});
}

ftxui::Element Page1::render_log()
{
    Elements log_lines;
    for (const auto &logger : logger.get_buffer())
    {
        if (logger.type == LoggerType::PRINT)
        {
            log_lines.push_back(hbox({text(get_time_str(logger.epoch)) | dim,
                                      text(logger.str)}));
        }
        else if (logger.type == LoggerType::COMMAND)
        {
            log_lines.push_back(hbox({text(logger.str) | italic | dim}));
        }
    }

    auto log_content = vbox(std::move(log_lines)) | yframe;

    return window(
               text("log") | hcenter | bold,
               log_content | vscroll_indicator | frame) |
           flex;
}

ftxui::Element Page1::render_status()
{
    return window(text("status") | hcenter | bold, text("content") | center | dim, BorderStyle::EMPTY) | flex | size(WIDTH, GREATER_THAN, 30);
}

Page1::Page1(EventHandler &handler)
    : Page(handler), _input_selected(false)
{
    _input_option.transform = [&](const InputState state)
    {
        return this->transform(state);
    };

    _input_component = Input(&_input_str, "Press 'enter' to send the text.", _input_option);

    Component input = Renderer(_input_component, [&]()
                               { return render_input(); });

    input |= CatchEvent(
        [&](const Event &event)
        {
            return catch_event(event);
        });

    Component log = Renderer([&]()
                             { return render_log(); });

    Component status = Renderer([&]()
                                { return render_status(); });

    _page = Container::Vertical({
        Container::Horizontal({log,
                               status}) |
            yflex,
        input,
    });
}
