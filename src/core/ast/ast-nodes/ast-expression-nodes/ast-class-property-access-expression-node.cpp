//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-property-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassPropertyAccessExpressionNode::ASTClassPropertyAccessExpressionNode(ASTClassPropertyAccessNode* propertyAccess) {
    _propertyAccess = propertyAccess;
}

ASTClassPropertyAccessNode* ASTClassPropertyAccessExpressionNode::getPropertyAccess() {
    return _propertyAccess;
}

ASTNodeType ASTClassPropertyAccessExpressionNode::getNodeType() {
    return AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE;
}

std::string ASTClassPropertyAccessExpressionNode::toString() {
    return "CLASS_PROPERTY_ACCESS_EXPRESSION";
}

bool ASTClassPropertyAccessExpressionNode::isSameAs(ASTNode *other) {
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