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
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_IR_ARRAY_PROTOTYPE_FUNCTION_H
#define JETLANG_IR_ARRAY_PROTOTYPE_FUNCTION_H
typedef enum {
    AP_DROP_FUNCTION,
    AP_DROP_LAST_FUNCTION,
    AP_TAKE_FUNCTION,
    AP_TAKE_LAST_FUNCTION,
    AP_HEAD_FUNCTION,
    AP_TAIL_FUNCTION,
    AP_LAST_FUNCTION,
    AP_APPEND_FUNCTION,
    AP_PREPEND_FUNCTION,
    AP_SIZE_FUNCTION,
    AP_EMPTY_FUNCTION
} IRArrayPrototypeFunctionId;
#endif //JETLANG_IR_ARRAY_PROTOTYPE_FUNCTION_H
