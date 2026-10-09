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
// Created by Johny Georges on 2024-05-02.
//

#ifndef JETLANG_AST_NODE_ID_ASSIGNOR_H
#define JETLANG_AST_NODE_ID_ASSIGNOR_H

#include <unordered_map>
#include "../../../token/token-table.h"
#include "../../../ast/types/ast-node-type.h"
#include "../../../ast/ast-nodes/ast-node.h"
#include "ast-node-id-strategies/ast-node-id-strategy.h"

class ASTNodeIdAssignor {
private:
    std::shared_ptr<TokenTable> _tokenTable;
    std::unordered_map<ASTNodeType, std::shared_ptr<ASTNodeIdStrategy>, std::hash<int>> _strategies;
    void initStrategies();
    void addStrategy(ASTNodeType astNodeType, std::shared_ptr<ASTNodeIdStrategy> reducerStrategy);
public:
    ASTNodeIdAssignor(std::shared_ptr<TokenTable> tokenTable);
    void assignIdIfNecessary(std::shared_ptr<ASTNode> node);
};

#endif //JETLANG_AST_NODE_ID_ASSIGNOR_H
