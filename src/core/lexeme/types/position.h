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
