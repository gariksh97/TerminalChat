//
// Created by garik on 07.05.17.
//

#include <ncurses.h>
#include "TUIHelper.h"

void TUIHelper::drawVerticalLine(int x, int fy, int ty) {
    for (int y = fy; y < ty; y++)
        mvprintw(y, x, "|");
}

void TUIHelper::drawHorizontalLine(int fx, int tx, int y) {
    for (int x = fx; x < tx; x++)
        mvprintw(y, x, "-");
}