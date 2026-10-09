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
// Created by Johny Georges on 2023-12-23.
//

#ifndef JETLANG_LOGGER_H
#define JETLANG_LOGGER_H
#include <string>
#include "iostream"
#include "../../types/basic-character-type.h"


namespace Logger {
    template <typename... Types>
    void log(Types... args) {
        ((std::cout << args << WHITE_SPACE), ...);
        std::cout << std::endl;
    }
    template <typename... Types>
    void debugLog(bool debug, Types... args) {
        if (!debug) return;
        ((std::cout << args << WHITE_SPACE), ...);
        std::cout << std::endl;
    }
}
#endif //JETLANG_LOGGER_H
