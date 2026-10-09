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

#ifndef JETLANG_AST_IF_STATEMENT_NODE_H
#define JETLANG_AST_IF_STATEMENT_NODE_H

#include "./ast-statement-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-assignment-node.h"
#include "../ast-control-flow-nodes/ast-if-block-node.h"
#include "../ast-control-flow-nodes/ast-else-if-block-node.h"
#include "../ast-control-flow-nodes/ast-else-block-node.h"

class ASTIfStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTIfBlockNode> _ifBlock;
    std::vector<std::shared_ptr<ASTElseIfBlockNode>> _elseIfBlocks;
    std::optional<std::shared_ptr<ASTElseBlockNode>> _elseBlock;
public:
    ASTIfStatementNode(std::shared_ptr<ASTIfBlockNode> ifBlock);
    ASTIfStatementNode(std::shared_ptr<ASTIfBlockNode> ifBlock, std::vector<std::shared_ptr<ASTElseIfBlockNode>> elseIfBlocks, std::optional<std::shared_ptr<ASTElseBlockNode>> elseBlock = {});
    std::shared_ptr<ASTIfStatementNode> addElseIfBlock(std::shared_ptr<ASTElseIfBlockNode> elseIfBlock);
    std::shared_ptr<ASTIfBlockNode> getIfBlock();
    std::vector<std::shared_ptr<ASTElseIfBlockNode>>* getElseIfBlocks();
    std::optional<std::shared_ptr<ASTElseBlockNode>> getElseBlock();
    bool onlyHasIfBlock();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IF_STATEMENT_NODE_H
