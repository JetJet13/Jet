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
// Created by Johny Georges on 2024-06-03.
//

#ifndef JETLANG_SCOPE_H
#define JETLANG_SCOPE_H

#include <stack>
#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-start-node.h"
#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-node.h"

class Scope {
private:
    std::shared_ptr<ASTBlockStartNode> _blockStartNode;
    std::vector<std::shared_ptr<ASTNode>> _block;
public:
    Scope(std::shared_ptr<ASTBlockStartNode> blockStartNode);
    void add(std::shared_ptr<ASTNode> node);
    std::vector<std::shared_ptr<ASTNode>> getBlock();
    std::shared_ptr<ASTBlockNode> convertToBlockNode(std::shared_ptr<ASTBlockEndNode> blockEndNode);
    std::stack<std::shared_ptr<ASTNode>> convertToStack();
};

#endif //JETLANG_SCOPE_H
