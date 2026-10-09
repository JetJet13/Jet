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
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_BLOCK_NODE_H
#define JETLANG_AST_BLOCK_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "../../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"
#include "../ast-scoped-block-node.h"
#include "ast-block-start-node.h"
#include "ast-block-end-node.h"

class ASTBlockNode : public ASTScopedBlockNode {
private:
    std::shared_ptr<ASTBlockStartNode> _blockStartNode;
    std::shared_ptr<ASTBlockEndNode> _blockEndNode;
    std::vector<std::shared_ptr<ASTNode>> _contents;
public:
    explicit ASTBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::shared_ptr<ASTBlockEndNode> blockEndNode);
    explicit ASTBlockNode(std::shared_ptr<ASTBlockStartNode> blockStartNode, std::vector<std::shared_ptr<ASTNode>> contents, std::shared_ptr<ASTBlockEndNode> blockEndNode);
    std::shared_ptr<ASTBlockNode> addContent(std::shared_ptr<ASTNode> content);
    void hoistTypes(std::vector<ASTNodeType> astNodeTypes);
    uint64_t size();
    std::vector<std::shared_ptr<ASTNode>>* getContents();
    std::vector<std::shared_ptr<ASTFunctionReturnExpressionNode>>* getReturnStatements() override;
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BLOCK_NODE_H
