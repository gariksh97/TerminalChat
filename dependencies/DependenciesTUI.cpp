//
// Created by garik on 16.05.17.
//

#include "DependenciesTUI.h"

#if linux
void DependenciesTUI::tui_initscr() {
    setlocale(LC_ALL, "");
    initscr();
}
#endif
#if __APPLE__
void DependenciesTUI::tui_initscr() {
    initscr();
}
#endif

#if linux || __APPLE__

void DependenciesTUI::tui_mvprintw(int y, int x, std::string value) {
    mvprintw(y, x, value.c_str());
};

void DependenciesTUI::tui_noecho() {
    noecho();
};

void DependenciesTUI::tui_raw() {
    raw();
}



void DependenciesTUI::tui_nonl(){
    nonl();
}

void DependenciesTUI::tui_move(int y, int x){
    move(y, x);
}

void DependenciesTUI::tui_refresh(){
    refresh();
}

void DependenciesTUI::tui_clear(){
    clear();
}

void DependenciesTUI::tui_keypad(){
    keypad(stdscr, TRUE);
}

void DependenciesTUI::tui_endwin(){
    endwin();
}

int DependenciesTUI::tui_getch(){
    timeout(1000);
    return getch();
}

int DependenciesTUI::tui_getmaxx(){
    return getmaxx(stdscr);
}

int DependenciesTUI::tui_getmaxy(){
    return getmaxy(stdscr);
}

#elif _WIN32
#endif