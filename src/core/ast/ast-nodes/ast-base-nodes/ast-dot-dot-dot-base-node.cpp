//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-dot-dot-dot-base-node.h"

ASTDotDotDotBaseNode::ASTDotDotDotBaseNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTDotDotDotBaseNode::getLexeme() {
    return _lexeme;
}

ASTNode * ASTDotDotDotBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    return this;
}

ASTNodeType ASTDotDotDotBaseNode::getNodeType() {
    return AST_LESS_THAN_BASE_NODE;
}

std::string ASTDotDotDotBaseNode::toString() {
    return "LESS_THAN";
}

bool ASTDotDotDotBaseNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTDotDotDotBaseNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTDotDotDotBaseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}