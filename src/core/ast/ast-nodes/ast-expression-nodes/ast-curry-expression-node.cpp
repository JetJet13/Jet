//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-curry-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTCurryExpressionNode::ASTCurryExpressionNode(ASTCallableExpressionNode* callableExpression, ASTFunctionArgumentListNode* arguments) {
    _callableExpression = callableExpression;
    _arguments = arguments;
    _children.push_back(_callableExpression);
    _children.push_back(_arguments);
}

ASTFunctionArgumentListNode* ASTCurryExpressionNode::getArguments() {
    return _arguments;
}

ASTCallableExpressionNode* ASTCurryExpressionNode::getCallableExpression() {
    return _callableExpression;
}

unsigned long ASTCurryExpressionNode::numArguments() {
    return _arguments->numArguments();
}

ASTNodeType ASTCurryExpressionNode::getNodeType() {
    return AST_CURRY_EXPRESSION_NODE;
}

std::string ASTCurryExpressionNode::toString() {
    return "CURRY_EXPRESSION";
}

bool ASTCurryExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTCurryExpressionNode*)other;

    return  this->getCallableExpression()->isSameAs(otherNode->getCallableExpression()) &&
            this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTCurryExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _callableExpression->print();
    _arguments->print();
    Logger::log("----------");
}

std::string ASTCurryExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_callableExpression)
    ->add(_arguments);
    return sourceCodeBuilder.build();
}