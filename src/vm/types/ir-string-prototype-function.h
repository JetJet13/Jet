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
// Created by Johny Georges on 2026-03-21.
//

#ifndef JETLANG_IR_STRING_PROTOTYPE_FUNCTION_H
#define JETLANG_IR_STRING_PROTOTYPE_FUNCTION_H
typedef enum {
    SP_DROP_FUNCTION,
    SP_DROP_LAST_FUNCTION,
    SP_TAKE_FUNCTION,
    SP_TAKE_LAST_FUNCTION,
    SP_AT_FUNCTION,
// will support head and last once we add null support
//    SP_HEAD_FUNCTION,
//    SP_LAST_FUNCTION,
    SP_TAIL_FUNCTION,
    SP_APPEND_FUNCTION,
    SP_PREPEND_FUNCTION,
    SP_SIZE_FUNCTION,
    SP_EMPTY_FUNCTION
} IRStringPrototypeFunctionId;
#endif //JETLANG_IR_STRING_PROTOTYPE_FUNCTION_H
