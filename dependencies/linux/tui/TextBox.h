//
// Created by garik on 07.05.17.
//

#ifndef TERMINALCHAT_TEXTBOX_H
#define TERMINALCHAT_TEXTBOX_H

#include <string>

class TextBox {
public:
    static constexpr int UP = 0;
    static constexpr int DOWN = 1;
    static constexpr int LEFT = 2;
    static constexpr int RIGHT = 3;

    TextBox();

    ~TextBox();

    void addCharacter(int c);
    void addCharacter(std::string c);
    void removeCharacter();

    uint getPos();

    void show(int fx, int fy, int tx, int ty);
    void moveTo(int direction);

    int getX();
    int getY();

    void clear();

    std::string getText();

private:
    void recalcCoords();

    std::string text;
    int x, y;
    int offset;
    int pos;
    int fx, fy, tx, ty;
};


#endif //TERMINALCHAT_TEXTBOX_H
