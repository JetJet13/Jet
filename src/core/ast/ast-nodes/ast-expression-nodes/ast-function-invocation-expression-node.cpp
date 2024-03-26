//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-invocation-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTFunctionInvocationExpressionNode::ASTFunctionInvocationExpressionNode(ASTFunctionCallNode* function, ASTFunctionArgumentListNode* arguments) {
    _function = function;
    _arguments = arguments;
}

ASTFunctionArgumentListNode* ASTFunctionInvocationExpressionNode::getArguments() {
    return _arguments;
}

ASTFunctionCallNode* ASTFunctionInvocationExpressionNode::getName() {
    return _function;
}

unsigned long ASTFunctionInvocationExpressionNode::numArguments() {
    return _arguments->numArguments();
}

ASTNodeType ASTFunctionInvocationExpressionNode::getNodeType() {
    return AST_FUNCTION_INVOCATION_EXPRESSION_NODE;
}

std::string ASTFunctionInvocationExpressionNode::toString() {
    return "FUNCTION_INVOCATION_EXPRESSION";
}

bool ASTFunctionInvocationExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTFunctionInvocationExpressionNode*)other;

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTFunctionInvocationExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _function->print();
    _arguments->print();
    Logger::log("----------");
}