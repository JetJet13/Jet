//
// Created by Johny Georges on 2024-02-20.
//

#include "./ast-unary-operator-node.h"

ASTUnaryOperatorNode::ASTUnaryOperatorNode(Lexeme* lexemeOperator) {
    _lexemeOperator = lexemeOperator;
}

Lexeme* ASTUnaryOperatorNode::getOperator() {
    return _lexemeOperator;
}

ASTNodeType ASTUnaryOperatorNode::getNodeType() {
    return AST_UNARY_OPERATOR_NODE;
}

std::string ASTUnaryOperatorNode::toString() {
    return "UNARY_OPERATOR";
}

bool ASTUnaryOperatorNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTUnaryOperatorNode*)other;
    return this->getOperator()->isEqual(otherNode->getOperator());
}