//
// Created by Johny Georges on 2025-06-16.
//

#include "ast-object-access-invocation-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "../../../type-signature/ref-type-signature/ref-type-signature.h"

ASTObjectAccessInvocationExpressionNode::ASTObjectAccessInvocationExpressionNode(ASTObjectAccessExpressionNode* objectAccess, ASTFunctionArgumentListNode* arguments) {
    _objectAccess = objectAccess;
    _arguments = arguments;
    _children.push_back(_objectAccess);
    _children.push_back(_arguments);
}

ASTFunctionArgumentListNode* ASTObjectAccessInvocationExpressionNode::getArguments() {
    return _arguments;
}

ASTObjectAccessExpressionNode* ASTObjectAccessInvocationExpressionNode::getObjectAccess() {
    return _objectAccess;
}

ASTObjectAccessSourceNode* ASTObjectAccessInvocationExpressionNode::getSource() {
    return _objectAccess->getSource();
}

ASTObjectAccessTargetNode* ASTObjectAccessInvocationExpressionNode::getTarget() {
    return _objectAccess->getTarget();
}

InvocableTypeSignature* ASTObjectAccessInvocationExpressionNode::getInvocableTypeSignature() {
    return (InvocableTypeSignature*)_objectAccess->getTypeSignature();
}

std::string ASTObjectAccessInvocationExpressionNode::getName() {
    return _objectAccess->getTarget()->getTarget()->getIdentifierNode()->getId();
}

unsigned long ASTObjectAccessInvocationExpressionNode::numArguments() {
    return _arguments->numArguments();
}

bool ASTObjectAccessInvocationExpressionNode::isArrayPrototypeInvocation() {
    auto sourceTypeSignature = this->getSource()->getSource()->getTypeSignature();
    if (sourceTypeSignature->typeTargetIs(REF_TYPE_SOURCE)) {
        auto refTypeSignature = (RefTypeSignature*)sourceTypeSignature;
        sourceTypeSignature = refTypeSignature->getUnderlyingType();
    }
    return (sourceTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)
    || sourceTypeSignature->typeTargetIs(STRING_LITERAL_TYPE_SOURCE))
           && this->getObjectAccess()->getTypeSignature()->isPrototype();
}

bool ASTObjectAccessInvocationExpressionNode::isRefPrototypeInvocation() {
    return this->getSource()->getSource()->getTypeSignature()->typeTargetIs(REF_TYPE_SOURCE)
            && this->getObjectAccess()->getTypeSignature()->isPrototype();
}

Position* ASTObjectAccessInvocationExpressionNode::getStartPosition() {
    return _objectAccess->getStartPosition();
}

Position* ASTObjectAccessInvocationExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTObjectAccessInvocationExpressionNode::getNodeType() {
    return AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE;
}

std::string ASTObjectAccessInvocationExpressionNode::toString() {
    return "AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE";
}

bool ASTObjectAccessInvocationExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTObjectAccessInvocationExpressionNode*)other;

    return this->getObjectAccess()->isSameAs(otherNode->getObjectAccess()) &&
           this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTObjectAccessInvocationExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _objectAccess->print();
    _arguments->print();
    Logger::log("----------");
}

std::string ASTObjectAccessInvocationExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_objectAccess)
    ->add(_arguments);
    return sourceCodeBuilder.build();
}