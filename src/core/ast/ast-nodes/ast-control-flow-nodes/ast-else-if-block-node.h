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
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_ELSE_IF_BLOCK_NODE_H
#define JETLANG_AST_ELSE_IF_BLOCK_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-control-flow-condition-node.h"
#include "ast-control-flow-block-node.h"
#include "ast-else-if-node.h"

class ASTElseIfBlockNode : public ASTScopedBlockNode {
private:
    std::shared_ptr<ASTElseIfNode> _elseIfKeyword;
    std::shared_ptr<ASTControlFlowConditionNode> _condition;
    std::shared_ptr<ASTControlFlowBlockNode> _block;
public:
    explicit ASTElseIfBlockNode(std::shared_ptr<ASTElseIfNode> elseIfKeyword, std::shared_ptr<ASTControlFlowConditionNode> condition, std::shared_ptr<ASTControlFlowBlockNode> block);
    std::shared_ptr<ASTControlFlowBlockNode> getBlock();
    std::shared_ptr<ASTControlFlowConditionNode> getCondition();
    std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* getReturnStatements() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ELSE_IF_BLOCK_NODE_H
