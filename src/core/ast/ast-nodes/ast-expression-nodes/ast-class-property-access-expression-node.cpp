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
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-property-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassPropertyAccessExpressionNode::ASTClassPropertyAccessExpressionNode(std::shared_ptr<ASTClassPropertyAccessNode> propertyAccess) {
    _propertyAccess = propertyAccess;
    _children.push_back(_propertyAccess);
}

std::shared_ptr<ASTClassPropertyAccessNode> ASTClassPropertyAccessExpressionNode::getPropertyAccess() {
    return _propertyAccess;
}

std::string ASTClassPropertyAccessExpressionNode::getPropertyName() {
    auto className = _propertyAccess->getClassAccess()->getThis()->getId();
    auto propertyName = _propertyAccess->getPropertyName()->getId();
    propertyName.erase(0, className.size() + 1);
    return propertyName;
}

std::shared_ptr<Position> ASTClassPropertyAccessExpressionNode::getStartPosition() {
    return _propertyAccess->getStartPosition();
}

std::shared_ptr<Position> ASTClassPropertyAccessExpressionNode::getEndPosition() {
    return _propertyAccess->getEndPosition();
}

ASTNodeType ASTClassPropertyAccessExpressionNode::getNodeType() {
    return AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE;
}

std::string ASTClassPropertyAccessExpressionNode::toString() {
    return "CLASS_PROPERTY_ACCESS_EXPRESSION";
}

bool ASTClassPropertyAccessExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertyAccessExpressionNode>(other);
    return this->getPropertyAccess()->isSameAs(otherNode->getPropertyAccess());
}

void ASTClassPropertyAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _propertyAccess->print();
    Logger::log("----------");
}

std::string ASTClassPropertyAccessExpressionNode::toSourceCode() {
    return _propertyAccess->toSourceCode();
}