#ifndef HEADER_PAGE1_FTXUI
#define HEADER_PAGE1_FTXUI

#include "pages/page.h"

#include <string>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/node.hpp>

class Page1 : public Page {
public:
    Page1(EventHandler &handler);
private:
    ftxui::Element transform(ftxui::InputState state);
    ftxui::Element render_input();
    ftxui::Element render_log();
    ftxui::Component render_status();
    bool catch_event(ftxui::Event event);
    void change_screen();

    std::string _input_str;
    ftxui::InputOption _input_option;
    bool _input_selected;
    ftxui::Component _input_component;
    ftxui::Component _button;
};

#endif // HEADER_PAGE1_FTXUI