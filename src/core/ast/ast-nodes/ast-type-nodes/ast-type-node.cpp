//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTypeNode::ASTTypeNode(ASTTypeBaseNode* type) {
    _type = type;
    _children.push_back(_type);
}

ASTTypeBaseNode* ASTTypeNode::getType() {
    return _type;
}

void ASTTypeNode::setTypeSignature(TypeSignature* typeSignature) {
    _type->setTypeSignature(typeSignature);
}

TypeSignature* ASTTypeNode::getTypeSignature() {
    return _type->getTypeSignature();
}

ASTNodeType ASTTypeNode::getNodeType() {
    return AST_TYPE_NODE;
}

std::string ASTTypeNode::toString() {
    return "TYPE";
}

bool ASTTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTypeNode*)other;
    return _type->isSameAs(otherNode->getType());
}

void ASTTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _type->print();
    Logger::log("----------");
}
