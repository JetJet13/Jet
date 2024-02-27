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
    return "BINARY_OPERATOR";
}

bool ASTBinaryOperatorNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    Logger::log("ASTBinaryOperatorNode", "other node is same type");
    auto otherNode = (ASTBinaryOperatorNode*)other;
    return this->getOperator()->isEqual(otherNode->getOperator());
}