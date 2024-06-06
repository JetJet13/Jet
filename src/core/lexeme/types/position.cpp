//
// Created by Johny Georges on 2024-06-05.
//

#include "position.h"

Position::Position() {
    _line = -1;
    _column = -1;
}

Position::Position(unsigned long line, unsigned long column) {
    _line = line;
    _column = column;
}

unsigned long Position::getLine() {
    return _line;
}

unsigned long Position::getColumn() {
    return _column;
}