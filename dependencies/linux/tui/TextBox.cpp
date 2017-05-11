//
// Created by garik on 07.05.17.
//

#include <ncurses.h>
#include "TextBox.h"

TextBox::TextBox() {
    this->text = "";
    offset = 0;
    pos = 0;
}

TextBox::~TextBox() {}

void TextBox::show(int fx, int fy, int tx, int ty) {

    if (this->fx != fx || this->tx != tx || this->ty != ty || this->fy != fy) {
        this->fy = fy;
        this->ty = ty;
        this->fx = fx;
        this->tx = tx;
        recalcCoords();
    }
    {
        std::string m = "Your message:";
        mvprintw(fy++, fx, m.length() <= tx - fx ? m.c_str() : m.substr(0, tx - fx).c_str());
    }
    for (int i = (tx - fx) * offset; i < text.length() && fy <= ty; fy++) {
        if (tx - fx <= text.length())
            mvprintw(fy, fx, text.substr(i, tx - fx).c_str());
        else
            mvprintw(fy, fx, text.substr(i).c_str());
        i += tx - fx;
    }
}

void TextBox::addCharacter(int c) {
    std::string s;
    s = toascii(c);
    addCharacter(s);
}

void TextBox::addCharacter(std::string c) {
    text = text.insert(pos, c);
    for (int i = 0; i < c.length(); i++)
        moveTo(RIGHT);
}

std::string TextBox::getText() {
    return text;
}

void TextBox::removeCharacter() {
    if (text.length() == 0) return;
    if (pos == 0)
        return;
    text = text.substr(0, pos - 1) + text.substr(pos, text.length());
    moveTo(LEFT);
}

void TextBox::moveTo(int direction) {
    switch (direction) {
        case UP:
            if (pos - (tx - fx) >= 0) {
                y--;
                pos -= tx - fx;
            }
            break;
        case DOWN:
            if (pos + (tx - fx) < text.length()) {
                y++;
                pos += tx - fx;
            }
            break;
        case LEFT:
            if (pos > 0) {
                --pos;
                if (x != fx) {
                    --x;
                } else {
                    x = tx;
                    --y;
                }
            }
            break;
        case RIGHT:
            if (pos + 1 <= text.length()) {
                pos++;
                if (x != tx) {
                    ++x;
                } else {
                    x = fx;
                    ++y;
                }
            }
            break;
    }
}

uint TextBox::getPos() {
    return pos;
}

void TextBox::recalcCoords() {
    int pos = this->pos;
    if (tx - fx != 0) {
        y = pos / (tx - fx) + fy + 1;
        x = pos % (tx - fx) + fx;
    } else {
        x = -1;
        y = -1;
    }
}

int TextBox::getX() {
    return x;
}

int TextBox::getY() {
    return y;
}

void TextBox::clear() {
    text = "";
    x = fx;
    y = fy + 1;
    pos = 0;
}