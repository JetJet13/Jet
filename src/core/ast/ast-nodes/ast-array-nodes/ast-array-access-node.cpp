//
// Created by Johny Georges on 2024-03-12.
//

#include "ast-array-access-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTArrayAccessNode::ASTArrayAccessNode(ASTExpressionNode* index) {
    _index = index;
}

ASTExpressionNode* ASTArrayAccessNode::getIndex() {
    return _index;
}

ASTNodeType ASTArrayAccessNode::getNodeType() {
    return AST_ARRAY_ACCESS_NODE;
}

std::string ASTArrayAccessNode::toString() {
    return "ARRAY_ACCESS";
}

bool ASTArrayAccessNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTArrayAccessNode*)other;
    return _index->isSameAs(otherNode->getIndex());

}

void ASTArrayAccessNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _index->print();
    Logger::log("----------");
}