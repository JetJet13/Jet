//
// Created by Johny Georges on 2024-02-07.
//

#include "ast-binary-operator-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTBinaryOperatorNode::ASTBinaryOperatorNode(Lexeme* lexemeOperator) {
    _lexemeOperator = lexemeOperator;
}

Lexeme* ASTBinaryOperatorNode::getOperator() {
    return _lexemeOperator;
}

ASTNodeType ASTBinaryOperatorNode::getNodeType() {
    return AST_BINARY_OPERATOR_NODE;
}

std::string ASTBinaryOperatorNode::toString() {
    return "BINARY_OPERATOR - " + _lexemeOperator->toString();
}

bool ASTBinaryOperatorNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTBinaryOperatorNode*)other;
    return this->getOperator()->hasSameSymbolTypeAs(otherNode->getOperator());
}