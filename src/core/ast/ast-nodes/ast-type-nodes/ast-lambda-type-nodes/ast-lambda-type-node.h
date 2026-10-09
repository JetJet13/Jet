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
// Created by Johny Georges on 2025-07-09.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_NODE_H

#include "../ast-type-base-node.h"
#include "../../ast-lambda-nodes/ast-lambda-arrow-node.h"
#include "ast-lambda-type-parameter-list-node.h"

class ASTLambdaTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<ASTLambdaTypeParameterListNode> _parameterList;
    std::shared_ptr<ASTLambdaArrowNode> _arrowNode;
    std::shared_ptr<ASTTypeNode> _returnType;
public:
    ASTLambdaTypeNode(std::shared_ptr<ASTLambdaTypeParameterListNode> parameterList, std::shared_ptr<ASTLambdaArrowNode> arrowNode, std::shared_ptr<ASTTypeNode> returnType);
    std::shared_ptr<ASTLambdaTypeParameterListNode> getParameterList();
    std::shared_ptr<ASTTypeNode> getReturnType();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_NODE_H
