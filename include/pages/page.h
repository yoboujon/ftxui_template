#ifndef HEADER_PAGE_FTXUI
#define HEADER_PAGE_FTXUI

#include <ftxui/component/component_base.hpp>
#include "event.h"

class ScreenPage : public Event
{
public:
    ScreenPage(EventHandler &handler)
        : Event(handler), _page()
    {
    }

    ftxui::Component *getPage()
    {
        return &_page;
    }

protected:
    ftxui::Component _page;
};

#endif // HEADER_PAGE_FTXUI