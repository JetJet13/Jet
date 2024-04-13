//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-spread-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleSpreadNode::ASTModuleSpreadNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTModuleSpreadNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTModuleSpreadNode::getNodeType() {
    return AST_MODULE_SPREAD_NODE;
}

std::string ASTModuleSpreadNode::toString() {
    return "MODULE_SPREAD";
}

bool ASTModuleSpreadNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleSpreadNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTModuleSpreadNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}