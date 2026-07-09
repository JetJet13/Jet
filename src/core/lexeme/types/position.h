//
// Created by Johny Georges on 2024-06-05.
//

#ifndef JETLANG_POSITION_H
#define JETLANG_POSITION_H

#include <memory>

class Position {
private:
    unsigned long _line = 0;
    unsigned long _column = 0;
public:
    Position();
    Position(unsigned long line, unsigned long column);
    unsigned long getLine();
    unsigned long getColumn();
    bool isEqual(std::shared_ptr<Position> otherPosition);

};

#endif //JETLANG_POSITION_H
