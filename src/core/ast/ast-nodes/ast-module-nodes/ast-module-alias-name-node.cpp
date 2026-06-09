//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-alias-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleAliasNameNode::ASTModuleAliasNameNode(ASTIdentifierNode* identifier) {
    _identifier = identifier;
    _children.push_back(_identifier);
}

ASTIdentifierNode* ASTModuleAliasNameNode::getIdentifier() {
    return _identifier;
}

Position* ASTModuleAliasNameNode::getStartPosition() {
    return _identifier->getStartPosition();
}

Position* ASTModuleAliasNameNode::getEndPosition() {
    return _identifier->getEndPosition();
}

ASTNodeType ASTModuleAliasNameNode::getNodeType() {
    return AST_MODULE_ALIAS_NAME_NODE;
}

std::string ASTModuleAliasNameNode::toString() {
    return "MODULE_ALIAS_NAME";
}

bool ASTModuleAliasNameNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleAliasNameNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTModuleAliasNameNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}

std::string ASTModuleAliasNameNode::toSourceCode() {
    return _identifier->toSourceCode();
}