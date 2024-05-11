//
// Created by Johny Georges on 2024-03-11.
//

#include "ast-array-access-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTArrayAccessExpressionNode::ASTArrayAccessExpressionNode(ASTExpressionNode* source, ASTArrayAccessNode* index) {
    _source = source;
    _index = index;
    _children.push_back(_source);
    _children.push_back(_index);
}

ASTExpressionNode* ASTArrayAccessExpressionNode::getSource() {
    return _source;
}

ASTArrayAccessNode* ASTArrayAccessExpressionNode::getIndex() {
    return _index;
}

ASTNodeType ASTArrayAccessExpressionNode::getNodeType() {
    return AST_ARRAY_ACCESS_EXPRESSION_NODE;
}

std::string ASTArrayAccessExpressionNode::toString() {
    return "ARRAY_ACCESS_EXPRESSION";
}

bool ASTArrayAccessExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTArrayAccessExpressionNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource()) &&
           this->getIndex()->isSameAs(otherNode->getIndex());
}

void ASTArrayAccessExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _index->print();
    Logger::log("----------");
}