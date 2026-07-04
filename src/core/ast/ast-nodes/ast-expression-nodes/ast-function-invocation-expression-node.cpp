//
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-invocation-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionInvocationExpressionNode::ASTFunctionInvocationExpressionNode(std::shared_ptr<ASTExpressionNode> function, std::shared_ptr<ASTFunctionArgumentListNode> arguments) {
    _function = function;
    _arguments = arguments;
    _children.push_back(_function);
    _children.push_back(_arguments);
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTFunctionInvocationExpressionNode::getArguments() {
    return _arguments;
}

std::shared_ptr<ASTExpressionNode> ASTFunctionInvocationExpressionNode::getFunction() {
    return _function;
}

unsigned long ASTFunctionInvocationExpressionNode::numArguments() {
    return _arguments->numArguments();
}

void ASTFunctionInvocationExpressionNode::setTypeSignature(FunctionInvocationTypeSignature* functionInvocationTypeSignature) {
    _typeSignature = functionInvocationTypeSignature;
}

FunctionInvocationTypeSignature* ASTFunctionInvocationExpressionNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTFunctionInvocationExpressionNode::getStartPosition() {
    return _function->getStartPosition();
}

Position* ASTFunctionInvocationExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTFunctionInvocationExpressionNode::getNodeType() {
    return AST_FUNCTION_INVOCATION_EXPRESSION_NODE;
}

std::string ASTFunctionInvocationExpressionNode::toString() {
    return "FUNCTION_INVOCATION_EXPRESSION";
}

bool ASTFunctionInvocationExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFunctionInvocationExpressionNode>(other);

    return  this->getFunction()->isSameAs(otherNode->getFunction()) &&
            this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTFunctionInvocationExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _function->print();
    _arguments->print();
    Logger::log("----------");
}

std::string ASTFunctionInvocationExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_function)
    ->add(_arguments);
    return sourceCodeBuilder.build();
}