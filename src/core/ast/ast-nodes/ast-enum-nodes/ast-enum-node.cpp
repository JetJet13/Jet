//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTEnumNode::ASTEnumNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTEnumNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTEnumNode::getNodeType() {
    return AST_ENUM_NODE;
}

std::string ASTEnumNode::toString() {
    return "ENUM";
}

bool ASTEnumNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTEnumNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTEnumNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}