//
// Created by Johny Georges on 2024-06-05.
//

#include "position.h"

Position::Position() {
    _line = -1;
    _column = -1;
}

Position::Position(uint64_t line, uint64_t column) {
    _line = line;
    _column = column;
}

uint64_t Position::getLine() {
    return _line;
}

uint64_t Position::getColumn() {
    return _column;
}

bool Position::isEqual(std::shared_ptr<Position> otherPosition) {
    return _line == otherPosition->getLine() && _column == otherPosition->getColumn();
}