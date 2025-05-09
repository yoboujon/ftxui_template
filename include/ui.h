#ifndef HEADER_UI_FTXUI
#define HEADER_UI_FTXUI

#include "pages/page.h"

#include <vector>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

/**
 * @brief 'UserInterface' is the main object that can be instanciated anywhere as a singleton
 * you can add any pages to it and cycle through them using the select_screen function.
 */
class UserInterface
{
public:
    static UserInterface &GetInstance()
    {
        static UserInterface instance;
        return instance;
    }

    /**
     * @brief return the actual terminal used for fullscreen.
     *
     * @return ftxui::ScreenInteractive
     */
    ftxui::ScreenInteractive *get_screen();

    /**
     * @brief Adding a page to the list. Only to be called before start().
     * Each page's lifetime has to be take into account as it is not copied into the object.
     *
     * @param Page* pointer to the parent Page
     */
    void add_screen(Page *p);

    /**
     * @brief Can be called anytime. Changes the selected page.
     *
     * @param size_t the index, it has to be inferior or equal to the pages given to the UI.
     */
    void select_screen(size_t index);

    /**
     * @brief Can be called anytime. Changes the selected page.
     *
     * @param Page* pointer to the parent Page, it has to be added to the list before hand.
     */
    void select_screen(const Page *p);

    /**
     * @brief Blocking function to render to the terminal.
     */
    void start();

    /**
     * @brief Updates the terminal. Can be useful when doing custom manipulations to diverse object.
     * Will redraw the entire terminal.
     */
    void update();

private:
    /**
     * @brief UserInterface cannot be created and can be called from anywhere in the executable.
     */
    UserInterface();
    ~UserInterface();

    ftxui::ScreenInteractive _screen;
    std::vector<Page *> _pages;
    /**
     * @brief each ftxui::Component in this object is stored directly because it has to be called by the
     * rendering pipeline.
     */
    ftxui::Component _page_container;
    ftxui::Component _main_container;
    ftxui::Component _main_renderer;
    /**
     * @brief Used in the ftxui::Container::Tab which can switch between
     * each pages renderer. (or get_page())
     */
    int _page_index;
};

#endif // HEADER_RENDER_FTXUI