//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForNode::ASTForNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTForNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTForNode::getNodeType() {
    return AST_FOR_NODE;
}

std::string ASTForNode::toString() {
    return "FOR";
}

bool ASTForNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTForNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTForNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}