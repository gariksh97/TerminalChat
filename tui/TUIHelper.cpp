//
// Created by garik on 07.05.17.
//

#include "TUIHelper.h"
#include <string>
#include "../dependencies/DependenciesTUI.h"

void TUIHelper::drawVerticalLine(int x, int fy, int ty) {
    for (int y = fy; y < ty; y++)
        DependenciesTUI::tui_mvprintw(y, x, "|");
}

void TUIHelper::drawHorizontalLine(int fx, int tx, int y) {
    for (int x = fx; x < tx; x++)
        DependenciesTUI::tui_mvprintw(y, x, "-");
}