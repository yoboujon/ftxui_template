#ifndef HEADER_PAGE2_FTXUI
#define HEADER_PAGE2_FTXUI

#include "pages/page.h"

#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/node.hpp>

class Page2 : public Page {
public:
    Page2(EventHandler &handler);
private:
    void change_screen();
    ftxui::Element render_radiobox();
    ftxui::Element render_button();

    int _selected;
    ftxui::Component _radiobox;
    ftxui::Component _button;
};

#endif // HEADER_PAGE2_FTXUI