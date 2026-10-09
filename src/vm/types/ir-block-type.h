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
// Created by Johny Georges on 2025-11-22.
//

#ifndef JETLANG_IR_BLOCK_TYPE_H
#define JETLANG_IR_BLOCK_TYPE_H
typedef enum {
    IR_BASIC_BT,
    IR_IF_BT,
    IR_IF_THEN_BT,
    IR_IF_ELSE_BT,
    IR_IF_END_BT,
    IR_WHILE_BT,
    IR_WHILE_BODY_BT,
    IR_WHILE_END_BT,
    IR_FOR_LOOP_BT,
    IR_FOR_LOOP_BODY_BT,
    IR_FOR_LOOP_END_BT,
    IR_FOR_IN_BT,
    IR_FOR_IN_SETUP_BT,
    IR_FOR_IN_BODY_BT,
    IR_FOR_IN_END_BT,
} IRBlockType;
#endif //JETLANG_IR_BLOCK_TYPE_H
