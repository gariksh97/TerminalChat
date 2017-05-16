//
// Created by garik on 16.05.17.
//

#ifndef TERMINALCHAT_DEPENDENCIESTUI_H
#define TERMINALCHAT_DEPENDENCIESTUI_H

#include <string>

#if __APPLE__ || linux
#include <ncurses.h>
#endif

class DependenciesTUI {
public:
    static void tui_mvprintw(int y, int x, std::string value);
    static void tui_noecho();
    static void tui_raw();
    static void tui_initscr();
    static void tui_nonl();
    static void tui_move(int y, int x);
    static void tui_refresh();
    static void tui_clear();
    static void tui_keypad();
    static void tui_endwin();
    static int tui_getmaxx();
    static int tui_getmaxy();
    static int tui_getch();

    static constexpr int TUI_F4           = KEY_F(4);
    static constexpr int TUI_F3           = KEY_F(3);
    static constexpr int TUI_F2           = KEY_F(2);
    static constexpr int TUI_F1           = KEY_F(1);
    static constexpr int TUI_UP           = KEY_UP;
    static constexpr int TUI_DOWN         = KEY_DOWN;
    static constexpr int TUI_LEFT         = KEY_LEFT;
    static constexpr int TUI_RIGHT        = KEY_RIGHT;
    static constexpr int TUI_ENTER        = KEY_ENTER;
    static constexpr int TUI_BACKSPACE    = KEY_BACKSPACE;

};


#endif //TERMINALCHAT_DEPENDENCIESTUI_H
