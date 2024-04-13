//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTPackageNameNode::ASTPackageNameNode(ASTIdentifierNode* identifier) {
    _identifier = identifier;
}

ASTIdentifierNode* ASTPackageNameNode::getIdentifier() {
    return _identifier;
}

ASTNodeType ASTPackageNameNode::getNodeType() {
    return AST_MODULE_NAME_NODE;
}

std::string ASTPackageNameNode::toString() {
    return "MODULE_NAME";
}

bool ASTPackageNameNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTPackageNameNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTPackageNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}