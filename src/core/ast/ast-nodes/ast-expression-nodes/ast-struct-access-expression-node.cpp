//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-struct-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTStructAccessExpressionNode::ASTStructAccessExpressionNode(ASTExpressionNode* source, ASTIdentifierExpressionNode* property) {
    _source = source;
    _property = property;
}

ASTExpressionNode* ASTStructAccessExpressionNode::getSource() {
    return _source;
}

ASTIdentifierExpressionNode* ASTStructAccessExpressionNode::getProperty() {
    return _property;
}

ASTNodeType ASTStructAccessExpressionNode::getNodeType() {
    return AST_STRUCT_ACCESS_EXPRESSION_NODE;
}

std::string ASTStructAccessExpressionNode::toString() {
    return "STRUCT_ACCESS_EXPRESSION";
}

bool ASTStructAccessExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTStructAccessExpressionNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource()) &&
           this->getProperty()->isSameAs(otherNode->getProperty());
}

void ASTStructAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _property->print();
    Logger::log("----------");
}