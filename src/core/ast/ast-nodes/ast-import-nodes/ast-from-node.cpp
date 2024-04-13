//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-from-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFromNode::ASTFromNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFromNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTFromNode::getNodeType() {
    return AST_FROM_NODE;
}

std::string ASTFromNode::toString() {
    return "FROM";
}

bool ASTFromNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFromNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFromNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}