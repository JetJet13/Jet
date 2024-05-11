//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleNameNode::ASTModuleNameNode(ASTIdentifierNode* identifier) {
    _identifier = identifier;
    _children.push_back(_identifier);
}

ASTIdentifierNode* ASTModuleNameNode::getIdentifier() {
    return _identifier;
}

ASTNodeType ASTModuleNameNode::getNodeType() {
    return AST_MODULE_NAME_NODE;
}

std::string ASTModuleNameNode::toString() {
    return "MODULE_NAME";
}

bool ASTModuleNameNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleNameNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTModuleNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}