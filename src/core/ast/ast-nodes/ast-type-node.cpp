//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-type-node.h"
#include "../../../shared/utils/logger/logger.h"

ASTTypeNode::ASTTypeNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTTypeNode::getTerminator() {
    return _lexeme;
}

ASTNodeType ASTTypeNode::getNodeType() {
    return AST_TYPE_NODE;
}

std::string ASTTypeNode::toString() {
    return "TYPE";
}

bool ASTTypeNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTypeNode*)other;
    return this->getTerminator()->hasSameSymbolTypeAs(otherNode->getTerminator());
}

void ASTTypeNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}
