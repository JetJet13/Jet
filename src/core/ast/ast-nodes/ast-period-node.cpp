//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-period-node.h"
#include "../../../shared/utils/logger/logger.h"

ASTPeriodNode::ASTPeriodNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTPeriodNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTPeriodNode::getNodeType() {
    return AST_PERIOD_NODE;
}

std::string ASTPeriodNode::toString() {
    return "PERIOD";
}

bool ASTPeriodNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTPeriodNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTPeriodNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}
