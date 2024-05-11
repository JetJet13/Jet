//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-array-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTArrayTypeNode::ASTArrayTypeNode(ASTTypeNode* elementType) {
    _elementType = elementType;
    _children.push_back(_elementType);
}

ASTTypeNode* ASTArrayTypeNode::getElementType() {
    return _elementType;
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
    return this->getElementType()->isSameAs(otherNode->getElementType());
}

void ASTArrayTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _elementType->print();
    Logger::log("----------");
}