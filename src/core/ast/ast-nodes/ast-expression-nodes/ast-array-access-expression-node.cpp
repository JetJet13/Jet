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
// Created by Johny Georges on 2024-03-11.
//

#include "ast-array-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessExpressionNode::ASTArrayAccessExpressionNode(std::shared_ptr<ASTExpressionNode> source, std::shared_ptr<ASTArrayAccessNode> arrayAccess) {
    _source = source;
    _arrayAccess = arrayAccess;
    _children.push_back(_source);
    _children.push_back(_arrayAccess);
}

std::shared_ptr<ASTExpressionNode> ASTArrayAccessExpressionNode::getSource() {
    return _source;
}

std::shared_ptr<ASTArrayAccessNode> ASTArrayAccessExpressionNode::getIndex() {
    return _arrayAccess;
}

std::shared_ptr<Position> ASTArrayAccessExpressionNode::getStartPosition() {
    return _source->getStartPosition();
}

std::shared_ptr<Position> ASTArrayAccessExpressionNode::getEndPosition() {
    return _arrayAccess->getEndPosition();
}

ASTNodeType ASTArrayAccessExpressionNode::getNodeType() {
    return AST_ARRAY_ACCESS_EXPRESSION_NODE;
}

std::string ASTArrayAccessExpressionNode::toString() {
    return "ARRAY_ACCESS_EXPRESSION";
}

bool ASTArrayAccessExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTArrayAccessExpressionNode>(other);
    return this->getSource()->isSameAs(otherNode->getSource()) &&
           this->getIndex()->isSameAs(otherNode->getIndex());
}

void ASTArrayAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _arrayAccess->print();
    Logger::log("----------");
}

std::string ASTArrayAccessExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_source)
    ->add(_arrayAccess);
    return sourceCodeBuilder.build();
}