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

#include "ast-lambda-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTLambdaTypeNode::ASTLambdaTypeNode(std::shared_ptr<ASTLambdaTypeParameterListNode> parameterList, std::shared_ptr<ASTLambdaArrowNode> arrowNode, std::shared_ptr<ASTTypeNode> returnType) {
    _parameterList = parameterList;
    _arrowNode = arrowNode;
    _returnType = returnType;
    _children.push_back(_parameterList);
    _children.push_back(_arrowNode);
    _children.push_back(_returnType);
}

std::shared_ptr<ASTLambdaTypeParameterListNode> ASTLambdaTypeNode::getParameterList() {
    return _parameterList;
}

std::shared_ptr<ASTTypeNode> ASTLambdaTypeNode::getReturnType() {
    return _returnType;
}

std::shared_ptr<Position> ASTLambdaTypeNode::getStartPosition() {
    return _parameterList->getStartPosition();
}

std::shared_ptr<Position> ASTLambdaTypeNode::getEndPosition() {
    return _returnType->getEndPosition();
}

ASTNodeType ASTLambdaTypeNode::getNodeType() {
    return AST_LAMBDA_TYPE_NODE;
}

std::string ASTLambdaTypeNode::toString() {
    return "LAMBDA_TYPE";
}

bool ASTLambdaTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLambdaTypeNode>(other);

    return this->getParameterList()->isSameAs(otherNode->getParameterList()) &&
           this->getReturnType()->isSameAs(otherNode->getReturnType());
}

void ASTLambdaTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}

std::string ASTLambdaTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder
            .add(_parameterList)
            ->add(_arrowNode)
            ->add(_returnType);
    return sourceCodeBuilder.build();
}