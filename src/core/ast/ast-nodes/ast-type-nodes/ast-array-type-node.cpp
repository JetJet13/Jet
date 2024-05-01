//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-array-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTArrayTypeNode::ASTArrayTypeNode(ASTTypeNode* elementType, ASTIntLiteralTypeNode* size) {
    _elementType = elementType;
    _size = size;
}

ASTTypeNode* ASTArrayTypeNode::getElementType() {
    return _elementType;
}

ASTIntLiteralTypeNode* ASTArrayTypeNode::getSize() {
    return _size;
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
    return this->getElementType()->isSameAs(otherNode->getElementType()) &&
           this->getSize()->isSameAs(otherNode->getSize());
}

void ASTArrayTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _elementType->print();
    _size->print();
    Logger::log("----------");
}