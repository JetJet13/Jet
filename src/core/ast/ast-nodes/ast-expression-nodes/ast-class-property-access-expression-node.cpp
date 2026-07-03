//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-property-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassPropertyAccessExpressionNode::ASTClassPropertyAccessExpressionNode(ASTClassPropertyAccessNode* propertyAccess) {
    _propertyAccess = propertyAccess;
    _children.push_back(_propertyAccess);
}

ASTClassPropertyAccessNode* ASTClassPropertyAccessExpressionNode::getPropertyAccess() {
    return _propertyAccess;
}

std::string ASTClassPropertyAccessExpressionNode::getPropertyName() {
    auto className = _propertyAccess->getClassAccess()->getThis()->getId();
    auto propertyName = _propertyAccess->getPropertyName()->getId();
    propertyName.erase(0, className.size() + 1);
    return propertyName;
}

Position* ASTClassPropertyAccessExpressionNode::getStartPosition() {
    return _propertyAccess->getStartPosition();
}

Position* ASTClassPropertyAccessExpressionNode::getEndPosition() {
    return _propertyAccess->getEndPosition();
}

ASTNodeType ASTClassPropertyAccessExpressionNode::getNodeType() {
    return AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE;
}

std::string ASTClassPropertyAccessExpressionNode::toString() {
    return "CLASS_PROPERTY_ACCESS_EXPRESSION";
}

bool ASTClassPropertyAccessExpressionNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassPropertyAccessExpressionNode*)other;
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