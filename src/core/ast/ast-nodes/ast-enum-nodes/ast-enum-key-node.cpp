//
// Created by Johny Georges on 2024-03-23.
//

#include "ast-enum-key-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTEnumKeyNode::ASTEnumKeyNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTEnumKeyNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTEnumKeyNode::getNodeType() {
    return AST_ENUM_KEY_NODE;
}

std::string ASTEnumKeyNode::toString() {
    return "ENUM_KEY";
}

bool ASTEnumKeyNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTEnumKeyNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTEnumKeyNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}