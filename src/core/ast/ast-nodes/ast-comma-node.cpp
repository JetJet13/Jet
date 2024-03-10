//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-comma-node.h"
#include "../../../shared/utils/logger/logger.h"

ASTCommaNode::ASTCommaNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTCommaNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTCommaNode::getNodeType() {
    return AST_COMMA_NODE;
}

std::string ASTCommaNode::toString() {
    return "COMMA";
}

bool ASTCommaNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTCommaNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTCommaNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}
