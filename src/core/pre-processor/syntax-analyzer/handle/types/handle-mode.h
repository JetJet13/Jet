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
// Created by Johny Georges on 2024-03-21.
//

#ifndef JETLANG_HANDLE_MODE_H
#define JETLANG_HANDLE_MODE_H
typedef enum {
    HANDLE_NORMAL_MODE,
    HANDLE_TERMINATOR_MODE,
    HANDLE_GROUP_MODE,
    HANDLE_ARRAY_MODE,
    HANDLE_STRUCT_MODE,
    HANDLE_FUNCTION_PARAMETER_LIST_MODE,
    HANDLE_ENUM_KEY_VALUE_LIST_MODE,
    HANDLE_FUNCTION_BLOCK_MODE,
} HandleMode;
#endif //JETLANG_HANDLE_MODE_H
