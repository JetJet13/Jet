//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleNode::ASTModuleNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTModuleNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTModuleNode::getNodeType() {
    return AST_MODULE_NODE;
}

std::string ASTModuleNode::toString() {
    return "MODULE";
}

bool ASTModuleNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTModuleNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}