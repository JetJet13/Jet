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
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_VARIABLE_DECLARATION_NODE_H
#define JETLANG_AST_VARIABLE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-type-node.h"
#include "../ast-variable-nodes/ast-variable-init-node.h"
#include "ast-declaration-node.h"
#include "../ast-export-node.h"

class ASTVariableDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTVariableInitNode> _varInit;
    std::shared_ptr<ASTExpressionNode> _initializer;
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
    std::optional<std::shared_ptr<ASTExportNode>> _exportKeyword = {};
    uint64_t _captureCount = 0;
public:
    explicit ASTVariableDeclarationNode(std::shared_ptr<ASTVariableInitNode> varInit, std::shared_ptr<ASTExpressionNode> initializer, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword = {});
    std::shared_ptr<ASTVariableInitNode> getVarInitNode();
    std::shared_ptr<ASTExpressionNode> getInitializerNode();
    void markAsCaptured();
    uint64_t getCaptureCount();
    bool isConst();
    bool isExportable() override;
    bool isCaptured();
    void setTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VARIABLE_DECLARATION_NODE_H
