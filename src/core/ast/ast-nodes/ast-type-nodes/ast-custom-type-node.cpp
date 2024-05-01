//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-custom-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTCustomTypeNode::ASTCustomTypeNode(ASTIdentifierNode* identifierNode) {
    _identifier = identifierNode;
}

ASTIdentifierNode* ASTCustomTypeNode::getIdentifier() {
    return _identifier;
}

ASTNodeType ASTCustomTypeNode::getNodeType() {
    return AST_CUSTOM_TYPE_NODE;
}

std::string ASTCustomTypeNode::toString() {
    return "CUSTOM_TYPE";
}

bool ASTCustomTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTCustomTypeNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTCustomTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}