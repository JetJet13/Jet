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
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
#define JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-function-parameter-node.h"
#include "../../../type-signature/parameter-list-type-signature/parameter-list-type-signature.h"
#include "ast-function-parameter-list-start-node.h"
#include "ast-function-parameter-list-end-node.h"
#include "../ast-comma-node.h"

class ASTFunctionParameterListNode : public ASTNode {
private:
    std::shared_ptr<ASTFunctionParameterListStartNode> _functionParameterListStartNode;
    std::shared_ptr<ASTFunctionParameterListEndNode> _functionParameterListEndNode;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTFunctionParameterNode>> _parameters;
    std::shared_ptr<ParameterListTypeSignature> _typeSignature = std::make_shared<ParameterListTypeSignature>();
public:
    ASTFunctionParameterListNode(std::shared_ptr<ASTFunctionParameterListStartNode> functionParameterListStartNode, std::shared_ptr<ASTFunctionParameterListEndNode> functionParameterListEndNode);
    ASTFunctionParameterListNode(std::shared_ptr<ASTFunctionParameterListStartNode> functionParameterListStartNode, std::vector<std::shared_ptr<ASTFunctionParameterNode>> parameters, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTFunctionParameterListEndNode> functionParameterListEndNode);
    std::vector<std::shared_ptr<ASTFunctionParameterNode>> getParameters();
    uint64_t numParameters();
    std::shared_ptr<ASTFunctionParameterListNode> addParameter(std::shared_ptr<ASTFunctionParameterNode> parameter);
    std::shared_ptr<ASTFunctionParameterListNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    void setTypeSignature(std::shared_ptr<ParameterListTypeSignature> typeSignature);
    std::shared_ptr<ParameterListTypeSignature> getParameterListTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_PARAMETER_LIST_NODE_H
