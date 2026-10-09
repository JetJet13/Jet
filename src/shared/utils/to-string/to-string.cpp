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
// Created by Johny Georges on 2023-12-24.
//

#include "to-string.h"

namespace ToStringUtil {
    std::string toString(uint8_t value) {
        return std::to_string(value);
    }
    std::string toString(int value) {
        return std::to_string(value);
    }
    std::string toString(uint64_t value) {
        return std::to_string(value);
    }
    std::string toString(bool value) {
        return value ? "true" : "false";
    }
}