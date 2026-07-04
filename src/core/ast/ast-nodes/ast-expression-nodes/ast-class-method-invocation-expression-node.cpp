//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-method-invocation-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassMethodInvocationExpressionNode::ASTClassMethodInvocationExpressionNode(std::shared_ptr<ASTClassAccessNode> classAccess, std::shared_ptr<ASTClassMethodCallNode> method, std::shared_ptr<ASTFunctionArgumentListNode> arguments) {
    _classAccess = classAccess;
    _method = method;
    _arguments = arguments;
    _children.push_back(_classAccess);
    _children.push_back(_method);
    _children.push_back(_arguments);
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTClassMethodInvocationExpressionNode::getArguments() {
    return _arguments;
}

std::shared_ptr<ASTClassMethodCallNode> ASTClassMethodInvocationExpressionNode::getName() {
    return _method;
}

std::shared_ptr<ASTClassAccessNode> ASTClassMethodInvocationExpressionNode::getClassAccess() {
    return _classAccess;
}

unsigned long ASTClassMethodInvocationExpressionNode::numArguments() {
    return _arguments->numArguments();
}

Position* ASTClassMethodInvocationExpressionNode::getStartPosition() {
    return _classAccess->getStartPosition();
}

Position* ASTClassMethodInvocationExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTClassMethodInvocationExpressionNode::getNodeType() {
    return AST_CLASS_METHOD_INVOCATION_EXPRESSION_NODE;
}

std::string ASTClassMethodInvocationExpressionNode::toString() {
    return "CLASS_METHOD_INVOCATION_EXPRESSION";
}

bool ASTClassMethodInvocationExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassMethodInvocationExpressionNode>(other);

    return this->getName()->isSameAs(otherNode->getName()) &&
           this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTClassMethodInvocationExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _method->print();
    _arguments->print();
    Logger::log("----------");
}

std::string ASTClassMethodInvocationExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classAccess)
    ->add(_method)
    ->add(_arguments);
    return sourceCodeBuilder.build();
}