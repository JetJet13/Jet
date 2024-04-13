//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-name-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleNameNode::ASTModuleNameNode(Lexeme *lexeme) {
    _name = lexeme;
}

Lexeme* ASTModuleNameNode::getName() {
    return _name;
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
    return this->getName()->hasSameSymbolTypeAs(otherNode->getName());
}

void ASTModuleNameNode::print() {
    Logger::log(this->toString(), "-", _name->toString());
}