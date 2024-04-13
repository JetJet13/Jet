//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-alias-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTPackageAliasNameNode::ASTPackageAliasNameNode(ASTIdentifierNode* identifier) {
    _identifier = identifier;
}

ASTIdentifierNode* ASTPackageAliasNameNode::getIdentifier() {
    return _identifier;
}

ASTNodeType ASTPackageAliasNameNode::getNodeType() {
    return AST_IMPORT_MODULE_ALIAS_NAME_NODE;
}

std::string ASTPackageAliasNameNode::toString() {
    return "IMPORT_MODULE_ALIAS_NAME";
}

bool ASTPackageAliasNameNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTPackageAliasNameNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTPackageAliasNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}