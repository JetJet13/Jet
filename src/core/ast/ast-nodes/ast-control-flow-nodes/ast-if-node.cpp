//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-if-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTIfNode::ASTIfNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTIfNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTIfNode::getNodeType() {
    return AST_IF_NODE;
}

std::string ASTIfNode::toString() {
    return "IF";
}

bool ASTIfNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTIfNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTIfNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}