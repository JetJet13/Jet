//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-colon-colon-base-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTColonColonBaseNode::ASTColonColonBaseNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTColonColonBaseNode::getLexeme() {
    return _lexeme;
}

ASTNode* ASTColonColonBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    return this;
}

ASTNodeType ASTColonColonBaseNode::getNodeType() {
    return AST_COLON_COLON_BASE_NODE;
}

std::string ASTColonColonBaseNode::toString() {
    return "COLON_COLON_BASE";
}

bool ASTColonColonBaseNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTColonColonBaseNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTColonColonBaseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}