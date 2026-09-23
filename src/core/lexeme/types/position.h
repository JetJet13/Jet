//
// Created by Johny Georges on 2024-06-05.
//

#ifndef JETLANG_POSITION_H
#define JETLANG_POSITION_H

#include <memory>

class Position {
private:
    uint64_t _line = 0;
    uint64_t _column = 0;
public:
    Position();
    Position(uint64_t line, uint64_t column);
    uint64_t getLine();
    uint64_t getColumn();
    bool isEqual(std::shared_ptr<Position> otherPosition);

};

#endif //JETLANG_POSITION_H
