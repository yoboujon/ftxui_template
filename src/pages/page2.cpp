#include "pages/page2.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

inline const std::vector<std::string> create_entries(const size_t num)
{
    std::vector<std::string> ret;
    for (size_t i = 0; i < num; i++)
        ret.push_back("Sample " + std::to_string(i));
    return ret;
}

static const std::vector<std::string> _entries = create_entries(50);

inline void Page2::change_screen()
{
    this->send_event(EventType::SWITCH_SCREEN, static_cast<size_t>(0));
}

inline Element Page2::render_radiobox()
{
    return vbox({window(text("Select Sample"),
                        _radiobox->Render() | vscroll_indicator | frame) |
                 center | flex}) |
           xflex_grow;
}

inline Element Page2::render_button()
{
    return vbox({_button->Render()}) | center | xflex;
}

Page2::Page2(EventHandler &handler)
    : Page(handler), _selected(0), _radiobox(Radiobox(&_entries, &_selected))
{
    Component radiobox_component = Renderer(_radiobox, [&]
                                            { return render_radiobox(); });

    _button = Container::Vertical({Button("Go to Page1", [&]
                                          { return change_screen(); })});
    Component button_component = Renderer(_button, [&]
                                          { return render_button(); });

    _page = Container::Vertical({Container::Horizontal({button_component, radiobox_component}) | flex});
}
