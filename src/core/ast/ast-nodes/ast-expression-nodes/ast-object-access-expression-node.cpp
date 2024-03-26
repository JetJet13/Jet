//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-object-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTObjectAccessExpressionNode::ASTObjectAccessExpressionNode(ASTExpressionNode* source, ASTIdentifierExpressionNode* property) {
    _source = source;
    _property = property;
}

ASTExpressionNode* ASTObjectAccessExpressionNode::getSource() {
    return _source;
}

ASTIdentifierExpressionNode* ASTObjectAccessExpressionNode::getProperty() {
    return _property;
}

ASTNodeType ASTObjectAccessExpressionNode::getNodeType() {
    return AST_OBJECT_ACCESS_EXPRESSION_NODE;
}

std::string ASTObjectAccessExpressionNode::toString() {
    return "OBJECT_ACCESS_EXPRESSION";
}

bool ASTObjectAccessExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTObjectAccessExpressionNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource()) &&
           this->getProperty()->isSameAs(otherNode->getProperty());
}

void ASTObjectAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _property->print();
    Logger::log("----------");
}