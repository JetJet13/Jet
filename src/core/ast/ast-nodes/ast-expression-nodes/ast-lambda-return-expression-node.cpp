//
// Created by Johny Georges on 2024-04-04.
//

#include "ast-lambda-return-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLambdaReturnExpressionNode::ASTLambdaReturnExpressionNode(ASTExpressionNode* expressionNode) {
    _returnExpression = expressionNode;
}

ASTExpressionNode* ASTLambdaReturnExpressionNode::getExpression() {
    return _returnExpression;
}

ASTNodeType ASTLambdaReturnExpressionNode::getNodeType() {
    return AST_LAMBDA_RETURN_EXPRESSION_NODE;
}

std::string ASTLambdaReturnExpressionNode::toString() {
    return "LAMBDA_RETURN_EXPRESSION";
}

bool ASTLambdaReturnExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLambdaReturnExpressionNode*)other;
    return this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTLambdaReturnExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _returnExpression->print();
    Logger::log("----------");
}