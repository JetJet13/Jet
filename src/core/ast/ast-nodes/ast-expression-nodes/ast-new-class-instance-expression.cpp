//
// Created by Johny Georges on 2024-04-26.
//

#include "ast-new-class-instance-expression.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNewClassInstanceExpressionNode::ASTNewClassInstanceExpressionNode(ASTClassNameNode* className, ASTFunctionArgumentListNode* arguments) {
    _className = className;
    _arguments = arguments;
    _children.push_back(_className);
    _children.push_back(_arguments);
}

ASTFunctionArgumentListNode* ASTNewClassInstanceExpressionNode::getArguments() {
    return _arguments;
}

ASTClassNameNode* ASTNewClassInstanceExpressionNode::getClassName() {
    return _className;
}

unsigned long ASTNewClassInstanceExpressionNode::numArguments() {
    return _arguments->numArguments();
}

ASTNodeType ASTNewClassInstanceExpressionNode::getNodeType() {
    return AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE;
}

std::string ASTNewClassInstanceExpressionNode::toString() {
    return "NEW_CLASS_INSTANCE_EXPRESSION";
}

bool ASTNewClassInstanceExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTNewClassInstanceExpressionNode*)other;

    return  this->getClassName()->isSameAs(otherNode->getClassName()) &&
            this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTNewClassInstanceExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _className->print();
    _arguments->print();
    Logger::log("----------");
}