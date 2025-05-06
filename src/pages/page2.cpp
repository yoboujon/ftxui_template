#include "pages/launcher.h"
#include "loader.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

static const std::vector<std::string> _launcher_entries = {
    "Legacy",
    "Debug"};

static const std::vector<std::string> _library_entries = {
    "Reply",
    "UDP_IP",
    "Emit",
    "BOUCHON",
    "Push"};

inline void ScreenPageLauncher::on_launch()
{
    this->send_event(EventType::SWITCH_SCREEN, static_cast<size_t>(1));
    // const std::string name = get_simple_name(_library_entries[_library_selected]);
    this->send_event(EventType::LAUNCH_INSTANCE, _library_entries[_library_selected]);
}

ScreenPageLauncher::ScreenPageLauncher(EventHandler &handler)
    : ScreenPage(handler)
{
    // Will be used later: for now crashes the launcher because it instanciate some values...
    // _library_entries = get_libraries();
    _library_selected = 0;
    _library = Radiobox(&_library_entries, &_library_selected);

    _launcher_selected = 0;
    _launcher = Radiobox(&_launcher_entries, &_launcher_selected);

    Component library_selection = Renderer(_library, [&]
                                           { return vbox({window(text("Select Library"),
                                                                 _library->Render() | vscroll_indicator | frame) |
                                                          center | flex}) |
                                                    xflex_grow; });
    Component launcher_selection = Renderer(_launcher, [&]
                                            { return vbox({window(text("Select launcher"),
                                                                  _launcher->Render() | vscroll_indicator | frame) |
                                                           center | flex}); });

    _launch_button = Container::Vertical({Button("Launch", [&]
                                                 { return on_launch(); })});
    Component launch = Renderer(_launch_button, [&]
                                { return vbox({_launch_button->Render()}) | center | xflex; });

    _page = Container::Vertical({Container::Horizontal({library_selection, launcher_selection, launch}) | flex});
}