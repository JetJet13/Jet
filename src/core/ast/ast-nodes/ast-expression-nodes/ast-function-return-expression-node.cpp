//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-return-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionReturnExpressionNode::ASTFunctionReturnExpressionNode(ASTExpressionNode* expressionNode) {
    _returnExpression = expressionNode;
}

ASTExpressionNode* ASTFunctionReturnExpressionNode::getExpression() {
    return _returnExpression;
}

ASTNodeType ASTFunctionReturnExpressionNode::getNodeType() {
    return AST_FUNCTION_RETURN_EXPRESSION_NODE;
}

std::string ASTFunctionReturnExpressionNode::toString() {
    return "FUNCTION_RETURN_EXPRESSION";
}

bool ASTFunctionReturnExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionReturnExpressionNode*)other;
    return this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTFunctionReturnExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _returnExpression->print();
    Logger::log("----------");
}