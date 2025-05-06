#include "ui.h"
#include <algorithm>
#include "ftxui/component/component.hpp"

using namespace ftxui;

UserInterface::UserInterface()
    : _screen(ScreenInteractive::Fullscreen()), _pages({}), _page_container(), _main_container(), _main_renderer(), _page_index(0)
{
}

UserInterface::~UserInterface()
{
    _screen.Exit();
}

ftxui::ScreenInteractive *UserInterface::get_screen()
{
    return &_screen;
}

void UserInterface::add_screen(ScreenPage *p)
{
    _pages.push_back(p);
}

void UserInterface::select_screen(size_t index)
{
    _page_index = index;
}

void UserInterface::select_screen(const ScreenPage *p)
{
    const typename std::vector<ScreenPage *>::iterator it = std::find(_pages.begin(), _pages.end(), p);
    const size_t index = it - _pages.begin();
    select_screen(index);
}

void UserInterface::start()
{
    Components pages_component;
    for (const auto &p : _pages)
        pages_component.push_back(*(p->getPage()));
    _page_container = Container::Tab(pages_component, &_page_index);

    _main_container = Container::Vertical({
        _page_container | flex,
    });

    _main_renderer = Renderer(_main_container, [&]
                              { return vbox({
                                    text("FTXUI Template") | inverted | hcenter,
                                    separatorEmpty(),
                                    _main_container->Render() | yflex_grow,
                                }); });

    _screen.Loop(_main_renderer);
}

void UserInterface::update()
{
    _screen.PostEvent(ftxui::Event::Custom);
}
