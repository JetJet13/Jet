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
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_IR_CAPTURED_VARIABLE_NODE_H
#define JETLANG_IR_CAPTURED_VARIABLE_NODE_H

#include "ir-instruction-node.h"

class IRCapturedVariableNode {
private:
    std::shared_ptr<IRInstructionNode> _mallocVariable;
    std::shared_ptr<IRInstructionNode> _arc;
public:
    IRCapturedVariableNode(std::shared_ptr<IRInstructionNode> mallocVariable, std::shared_ptr<IRInstructionNode> arc);
    std::shared_ptr<IRInstructionNode> getVariable();
    std::shared_ptr<IRInstructionNode> getArc();
};

#endif //JETLANG_IR_CAPTURED_VARIABLE_NODE_H
