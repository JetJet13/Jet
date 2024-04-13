//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-module-access-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleAccessNode::ASTModuleAccessNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTModuleAccessNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTModuleAccessNode::getNodeType() {
    return AST_MODULE_ACCESS_NODE;
}

std::string ASTModuleAccessNode::toString() {
    return "MODULE_ACCESS";
}

bool ASTModuleAccessNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleAccessNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTModuleAccessNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}