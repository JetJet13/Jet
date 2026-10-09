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
// Created by Johny Georges on 2024-04-26.
//

#ifndef JETLANG_AST_NEW_CLASS_INSTANCE_EXPRESSION_H
#define JETLANG_AST_NEW_CLASS_INSTANCE_EXPRESSION_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-function-nodes/ast-function-call-node.h"
#include "ast-callable-expression-node.h"
#include "../ast-class-nodes/ast-class-name-node.h"
#include "../ast-class-nodes/ast-new-node.h"
#include "../../../type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "ast-module-access-expression-node.h"

class ASTNewClassInstanceExpressionNode : public ASTCallableExpressionNode {
private:
    std::shared_ptr<ASTNewNode> _new;
    std::optional<std::shared_ptr<ASTClassNameNode>> _className;
    std::optional<std::shared_ptr<ASTModuleAccessExpressionNode>> _moduleAccessExpression;
    std::shared_ptr<ASTFunctionArgumentListNode> _arguments;
    std::shared_ptr<NewClassInstanceTypeSignature> _typeSignature = std::make_shared<NewClassInstanceTypeSignature>();
public:
    explicit ASTNewClassInstanceExpressionNode(std::shared_ptr<ASTNewNode> newKeywordNode, std::shared_ptr<ASTClassNameNode> className, std::shared_ptr<ASTFunctionArgumentListNode> arguments);
    explicit ASTNewClassInstanceExpressionNode(std::shared_ptr<ASTNewNode> newKeywordNode, std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpressionNode, std::shared_ptr<ASTFunctionArgumentListNode> arguments);
    std::shared_ptr<ASTFunctionArgumentListNode> getArguments();
    std::string getClassName();
    std::optional<std::string> getModuleName();
    uint64_t numArguments();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    void setTypeSignature(std::shared_ptr<NewClassInstanceTypeSignature> typeSignature);
    std::shared_ptr<NewClassInstanceTypeSignature> getClassInstanceTypeSignature();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_NEW_CLASS_INSTANCE_EXPRESSION_H
