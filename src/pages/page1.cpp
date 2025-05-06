#include "pages/debugger.h"
#include "logger.h"

#include "toolBox.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

constexpr uint8_t LOGGER_OFFSET = 7;

inline ftxui::Element ScreenPageDebugger::transform(ftxui::InputState state)
{
    if (state.is_placeholder)
        state.element |= dim;

    if (state.focused)
    {
        state.element |= color(Color::White);
        input_selected = true;
    }
    else
    {
        input_selected = false;
    }

    return state.element;
}

inline bool ScreenPageDebugger::catch_event(Event event)
{
    if (event.is_character())
    {
        // Checking if it is a command...
    }

    const int size = _render.get_screen()->dimy();
    log_buffer.set_max_size(size - LOGGER_OFFSET);
    if (event == Event::Return)
    {
        send_event(EventType::SEND_COMMAND, cmd_str);
    }
    return (event == Event::Return);
}

ftxui::Element ScreenPageDebugger::render_input()
{
    Element arrow = text("> ");
    if (input_selected)
        arrow |= bgcolor(Color::White) | color(Color::Black);
    else
        arrow |= color(Color::Default) | bgcolor(Color::Default);

    return vbox({separatorEmpty(),
                 text("Send an event"),
                 hbox({arrow,
                       input_event->Render()})});
}

ftxui::Element ScreenPageDebugger::render_log()
{
    Elements log_lines;
    for (const auto &logger : log_buffer.get_buffer())
    {
        if(logger.type == LoggerType::STUB) {
            log_lines.push_back(hbox({
                text(get_time_str(logger.epoch)) | dim,
                text(logger.str)
            }));
        } else {
            log_lines.push_back(hbox({
                text(logger.str) | italic | dim
            }));
        }
    }

    auto log_content = vbox(std::move(log_lines)) | yframe;

    return window(
               text("log") | hcenter | bold,
               log_content | vscroll_indicator | frame) |
           flex;
}

ftxui::Element ScreenPageDebugger::render_status()
{
    return window(text("status") | hcenter | bold, text("content") | center | dim, BorderStyle::EMPTY) | flex | size(WIDTH, GREATER_THAN, 30);
}

ScreenPageDebugger::ScreenPageDebugger(EventHandler &handler, ScreenRender &sr)
    : ScreenPage(handler), _render(sr), input_selected(false)
{
    input_option.transform = [&](const InputState state)
    {
        return this->transform(state);
    };

    input_event = Input(&cmd_str, "Press 'enter' to send the event. Type '/help' for commands.", input_option);

    Component input = Renderer(input_event, [&]()
                               { return render_input(); });

    input |= CatchEvent(
        [&](const Event &event)
        {
            return this->catch_event(event);
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

Logger *ScreenPageDebugger::get_logger()
{
    return &log_buffer;
}
