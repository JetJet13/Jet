// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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