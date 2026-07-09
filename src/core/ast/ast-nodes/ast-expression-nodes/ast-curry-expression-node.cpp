//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-curry-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTCurryExpressionNode::ASTCurryExpressionNode(std::shared_ptr<ASTCallableExpressionNode> callableExpression, std::shared_ptr<ASTFunctionArgumentListNode> arguments) {
    _callableExpression = callableExpression;
    _arguments = arguments;
    _children.push_back(_callableExpression);
    _children.push_back(_arguments);
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTCurryExpressionNode::getArguments() {
    return _arguments;
}

std::shared_ptr<ASTCallableExpressionNode> ASTCurryExpressionNode::getCallableExpression() {
    return _callableExpression;
}

unsigned long ASTCurryExpressionNode::numArguments() {
    return _arguments->numArguments();
}

std::shared_ptr<Position> ASTCurryExpressionNode::getStartPosition() {
    return _callableExpression->getStartPosition();
}

std::shared_ptr<Position> ASTCurryExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTCurryExpressionNode::getNodeType() {
    return AST_CURRY_EXPRESSION_NODE;
}

std::string ASTCurryExpressionNode::toString() {
    return "CURRY_EXPRESSION";
}

bool ASTCurryExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTCurryExpressionNode>(other);

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