//
// Created by Johny Georges on 2024-03-23.
//

#include "ast-enum-key-value-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTEnumKeyValueListEndNode::ASTEnumKeyValueListEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTEnumKeyValueListEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTEnumKeyValueListEndNode::getNodeType() {
    return AST_ENUM_KEY_VALUE_LIST_END_NODE;
}

std::string ASTEnumKeyValueListEndNode::toString() {
    return "ENUM_END";
}

bool ASTEnumKeyValueListEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTEnumKeyValueListEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTEnumKeyValueListEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}