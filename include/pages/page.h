#ifndef HEADER_PAGE_FTXUI
#define HEADER_PAGE_FTXUI

#include <ftxui/component/component_base.hpp>
#include "event.h"

class Page : public EventPage
{
public:
    Page(EventHandler &handler)
        : EventPage(handler), _page()
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