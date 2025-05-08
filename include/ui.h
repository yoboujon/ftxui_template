#ifndef HEADER_UI_FTXUI
#define HEADER_UI_FTXUI

#include "pages/page.h"

#include <vector>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

class UserInterface
{
public:
    static UserInterface &GetInstance()
    {
        static UserInterface instance;
        return instance;
    }

    ftxui::ScreenInteractive *get_screen();
    void add_screen(Page *p);
    void select_screen(size_t index);
    void select_screen(const Page *p);
    void start();
    void update();

private:
    UserInterface();
    ~UserInterface();

    ftxui::ScreenInteractive _screen;
    std::vector<Page *> _pages;
    ftxui::Component _page_container;
    ftxui::Component _main_container;
    ftxui::Component _main_renderer;
    int _page_index;
};

#endif // HEADER_RENDER_FTXUI