//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-catch-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTCatchNode::ASTCatchNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTCatchNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTCatchNode::getNodeType() {
    return AST_CATCH_NODE;
}

std::string ASTCatchNode::toString() {
    return "CATCH";
}

bool ASTCatchNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTCatchNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTCatchNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}