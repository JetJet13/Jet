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
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_FLOAT_LITERAL_NODE_H
#define JETLANG_AST_FLOAT_LITERAL_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-literal-node.h"

class ASTFloatLiteralNode : public ASTLiteralNode {
    using ASTLiteralNode::ASTLiteralNode;
private:
    std::string _value;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    void setValue(std::shared_ptr<TokenTable> tokenTable) override;
    std::string getValue();
};

#endif //JETLANG_AST_FLOAT_LITERAL_NODE_H
