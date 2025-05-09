#ifndef HEADER_PAGE_FTXUI
#define HEADER_PAGE_FTXUI

#include <ftxui/component/component_base.hpp>
#include "event.h"

/**
 * @brief 'Page' is a child class that can be inherited by any new page.
 * In your constructor you should build the _page given by it. Otherwise this
 * class should not be instanciated whatsover.
 *
 * Each Page is inherited from an EventPage and can send signals. to the main event handler.
 */
class Page : public EventPage
{
public:
    Page(EventHandler &handler)
        : EventPage(handler), _page()
    {
    }

    /**
     * @brief Gather the current page from any parent.
     * This function may be overwritten.
     *
     * @return ftxui::Component the current page
     */
    ftxui::Component *getPage()
    {
        return &_page;
    }

protected:
    ftxui::Component _page;
};

#endif // HEADER_PAGE_FTXUI