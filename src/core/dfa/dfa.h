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
// Created by Johny Georges on 2024-02-13.
//

#ifndef JETLANG_DFA_H
#define JETLANG_DFA_H

#include <unordered_map>
#include "../ast/ast-nodes/ast-node.h"
#include "dfa.h"
#include "dfa-node.h"

class DFA {
private:
    std::unordered_map<ASTNodeType, std::shared_ptr<DFANode>> _startNodes;
    std::optional<std::shared_ptr<DFANode>> _start;
    std::optional<std::shared_ptr<DFANode>> _current;
public:
    DFA();
    void init(ASTNodeType astNodeType);
    DFA* insertStartNode(std::shared_ptr<DFANode> dfaNode);
    void reset();
    void determine(ASTNodeType nextAstNodeType);
    std::optional<std::shared_ptr<DFANode>> getStartState();
    std::optional<std::shared_ptr<DFANode>> getCurrentState();
    std::optional<std::shared_ptr<DFANode>> findStartNode(ASTNodeType nodeType);
};
#endif //JETLANG_DFA_H
