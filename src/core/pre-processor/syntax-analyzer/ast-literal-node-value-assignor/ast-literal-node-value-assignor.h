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
// Created by Johny Georges on 2024-05-20.
//

#ifndef JETLANG_AST_LITERAL_NODE_VALUE_ASSIGNOR_H
#define JETLANG_AST_LITERAL_NODE_VALUE_ASSIGNOR_H

#include "../../../token/token-table.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-literal-node.h"

class ASTLiteralNodeValueAssignor {
public:
    void static assignValue(std::shared_ptr<ASTNode> node, std::shared_ptr<TokenTable> tokenTable);
};

#endif //JETLANG_AST_LITERAL_NODE_VALUE_ASSIGNOR_H
