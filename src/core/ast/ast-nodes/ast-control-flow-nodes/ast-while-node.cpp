//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-while-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTWhileNode::ASTWhileNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTWhileNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTWhileNode::getNodeType() {
    return AST_WHILE_NODE;
}

std::string ASTWhileNode::toString() {
    return "WHILE";
}

bool ASTWhileNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTWhileNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTWhileNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}