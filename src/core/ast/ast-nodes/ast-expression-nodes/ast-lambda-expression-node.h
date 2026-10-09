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
// Created by Johny Georges on 2024-04-03.
//

#ifndef JETLANG_AST_LAMBDA_EXPRESSION_NODE_H
#define JETLANG_AST_LAMBDA_EXPRESSION_NODE_H

#include <set>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../../../type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../ast-declaration-nodes/ast-variable-declaration-node.h"

class ASTLambdaExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<Lexeme> _lexeme;
    std::shared_ptr<ASTFunctionParameterListNode> _parameters;
    std::shared_ptr<ASTFunctionBlockNode> _block;
    std::optional<std::shared_ptr<ASTTypeColonNode>> _typeColon;
    std::optional<std::shared_ptr<ASTTypeNode>> _returnType;
    std::shared_ptr<LambdaExpressionTypeSignature> _typeSignature = std::make_shared<LambdaExpressionTypeSignature>();
    std::set<std::string> _capturedValueIds;
public:
    explicit ASTLambdaExpressionNode(std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> block);
    explicit ASTLambdaExpressionNode(std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> block, std::shared_ptr<ASTTypeColonNode> typeColon, std::shared_ptr<ASTTypeNode> returnType);
    std::shared_ptr<Lexeme> getLexeme();
    std::shared_ptr<ASTFunctionParameterListNode> getParameters();
    std::shared_ptr<ASTFunctionBlockNode> getBlock();
    std::optional<std::shared_ptr<ASTTypeNode>> getReturnType();
    std::set<std::string>* getCapturedValueIds();
    void addCapturedValueId(std::string id);
    void setTypeSignature(std::shared_ptr<LambdaExpressionTypeSignature> lambdaExpressionTypeSignature);
    std::shared_ptr<LambdaExpressionTypeSignature> getLambdaTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_LAMBDA_EXPRESSION_NODE_H
