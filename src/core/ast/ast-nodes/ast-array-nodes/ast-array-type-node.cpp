//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-array-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTArrayTypeNode::ASTArrayTypeNode(ASTTypeParameterListNode* typeParameterList) {
    _typeParameterList = typeParameterList;
}

ASTTypeParameterListNode* ASTArrayTypeNode::getParameterList() {
    return _typeParameterList;
}

ASTNodeType ASTArrayTypeNode::getNodeType() {
    return AST_ARRAY_TYPE_NODE;
}

std::string ASTArrayTypeNode::toString() {
    return "ARRAY_TYPE";
}

bool ASTArrayTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTArrayTypeNode*)other;
    return this->getParameterList()->isSameAs(otherNode->getParameterList());
}

void ASTArrayTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _typeParameterList->print();
    Logger::log("----------");
}