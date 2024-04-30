//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTypeNode::ASTTypeNode(ASTTypeBaseNode* type) {
    _type = type;
}

BaseType* ASTTypeNode::getType() {
    return _type->getType();
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
    return this->getType()->isEqualTo(otherNode->getType());
}

void ASTTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _type->print();
    Logger::log("----------");
}
