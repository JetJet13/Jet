//
// Created by Johny Georges on 2024-03-23.
//

#include "ast-enum-key-value-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTEnumKeyValueListStartNode::ASTEnumKeyValueListStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTEnumKeyValueListStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTEnumKeyValueListStartNode::getNodeType() {
    return AST_ENUM_KEY_VALUE_LIST_START_NODE;
}

std::string ASTEnumKeyValueListStartNode::toString() {
    return "ENUM_START";
}

bool ASTEnumKeyValueListStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTEnumKeyValueListStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTEnumKeyValueListStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}