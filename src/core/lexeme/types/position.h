//
// Created by Johny Georges on 2024-06-05.
//

#ifndef JETLANG_POSITION_H
#define JETLANG_POSITION_H

class Position {
private:
    unsigned long _line;
    unsigned long _column;
public:
    Position();
    Position(unsigned long line, unsigned long column);
    unsigned long getLine();
    unsigned long getColumn();

};

#endif //JETLANG_POSITION_H
