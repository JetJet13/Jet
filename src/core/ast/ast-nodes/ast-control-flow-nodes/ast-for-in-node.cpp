//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-in-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForInNode::ASTForInNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTForInNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTForInNode::getNodeType() {
    return AST_FOR_IN_NODE;
}

std::string ASTForInNode::toString() {
    return "FOR_IN";
}

bool ASTForInNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTForInNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTForInNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}