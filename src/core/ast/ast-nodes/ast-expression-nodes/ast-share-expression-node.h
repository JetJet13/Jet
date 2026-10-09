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
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_AST_SHARE_EXPRESSION_NODE_H
#define JETLANG_AST_SHARE_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-share-nodes/ast-share-node.h"
#include "../../../type-signature/shared-type-signature/shared-type-signature.h"

class ASTShareExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTExpressionNode> _expression;
    std::shared_ptr<ASTShareNode> _shareNode;
    std::shared_ptr<SharedTypeSignature> _typeSignature = std::make_shared<SharedTypeSignature>();
public:
    ASTShareExpressionNode(std::shared_ptr<ASTShareNode> shareNode, std::shared_ptr<ASTExpressionNode> astExpressionNode);
    std::shared_ptr<ASTExpressionNode> getExpressionNode();
    std::shared_ptr<ASTShareNode> getShareNode();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<SharedTypeSignature> getSharedTypeSignature();
    void setTypeSignature(std::shared_ptr<SharedTypeSignature> typeSignature);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_SHARE_EXPRESSION_NODE_H
