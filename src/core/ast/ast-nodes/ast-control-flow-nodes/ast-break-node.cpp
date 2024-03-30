//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-break-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTBreakNode::ASTBreakNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTBreakNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTBreakNode::getNodeType() {
    return AST_BREAK_NODE;
}

std::string ASTBreakNode::toString() {
    return "BREAK";
}

bool ASTBreakNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTBreakNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTBreakNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}