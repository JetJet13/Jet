//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-boolean-literal-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTBooleanLiteralNode::getNodeType() {
    return AST_BOOLEAN_LITERAL_NODE;
}

std::string ASTBooleanLiteralNode::toString() {
    return "BOOLEAN_LITERAL - " + _lexeme->toString();
}

void ASTBooleanLiteralNode::setValue(std::shared_ptr<TokenTable> tokenTable) {
    if (_lexeme->getToken()->getSymbol()->isTrue()) {
        _value = true;
        return;
    } else if (_lexeme->getToken()->getSymbol()->isFalse()) {
        _value = false;
        return;
    }

    throw std::logic_error("unable to set value for boolean literal node because lexeme is not true or false");
}

bool ASTBooleanLiteralNode::getValue() {
    return _value;
}
