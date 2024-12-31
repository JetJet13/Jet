//
// Created by Johny Georges on 2024-04-26.
//

#include "ast-new-class-instance-expression.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTNewClassInstanceExpressionNode::ASTNewClassInstanceExpressionNode(ASTNewNode* newKeywordNode, ASTClassNameNode* className, ASTFunctionArgumentListNode* arguments) {
    _new = newKeywordNode;
    _className = className;
    _arguments = arguments;
    _children.push_back(_new);
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

ClassInstanceTypeSignature* ASTNewClassInstanceExpressionNode::getTypeSignature() {
    return _typeSignature;
}

void ASTNewClassInstanceExpressionNode::setTypeSignature(ClassInstanceTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

Position* ASTNewClassInstanceExpressionNode::getStartPosition() {
    return _new->getStartPosition();
}

Position* ASTNewClassInstanceExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
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

std::string ASTNewClassInstanceExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_new)
    ->addWithWhitespace(_className)
    ->add(_arguments);
    return sourceCodeBuilder.build();
}