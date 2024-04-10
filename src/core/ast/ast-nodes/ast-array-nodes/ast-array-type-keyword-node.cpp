//
// Created by Johny Georges on 2024-04-09.
//

#include "ast-array-type-keyword-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTArrayTypeKeywordNode::ASTArrayTypeKeywordNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTArrayTypeKeywordNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTArrayTypeKeywordNode::getNodeType() {
    return AST_ARRAY_TYPE_KEYWORD_NODE;
}

std::string ASTArrayTypeKeywordNode::toString() {
    return "ARRAY_TYPE_KEYWORD";
}

bool ASTArrayTypeKeywordNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTArrayTypeKeywordNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTArrayTypeKeywordNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}