//
// Created by Johny Georges on 2026-02-06.
//

#include "ast-array-access-invocation-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTArrayAccessInvocationExpressionNode::ASTArrayAccessInvocationExpressionNode(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccess, std::shared_ptr<ASTFunctionArgumentListNode> arguments) {
    _arrayAccess = arrayAccess;
    _arguments = arguments;
    _children.push_back(_arrayAccess);
    _children.push_back(_arguments);
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTArrayAccessInvocationExpressionNode::getArguments() {
    return _arguments;
}

std::shared_ptr<ASTArrayAccessExpressionNode> ASTArrayAccessInvocationExpressionNode::getArrayAccess() {
    return _arrayAccess;
}

std::shared_ptr<ASTExpressionNode> ASTArrayAccessInvocationExpressionNode::getSource() {
    return _arrayAccess->getSource();
}

std::shared_ptr<ASTArrayAccessNode> ASTArrayAccessInvocationExpressionNode::getIndex() {
    return _arrayAccess->getIndex();
}

InvocableTypeSignature* ASTArrayAccessInvocationExpressionNode::getInvocableTypeSignature() {
    return (InvocableTypeSignature*)_arrayAccess->getTypeSignature();
}

unsigned long ASTArrayAccessInvocationExpressionNode::numArguments() {
    return _arguments->numArguments();
}

Position* ASTArrayAccessInvocationExpressionNode::getStartPosition() {
    return _arrayAccess->getStartPosition();
}

Position* ASTArrayAccessInvocationExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTArrayAccessInvocationExpressionNode::getNodeType() {
    return AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE;
}

std::string ASTArrayAccessInvocationExpressionNode::toString() {
    return "AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE";
}

bool ASTArrayAccessInvocationExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTArrayAccessInvocationExpressionNode>(other);

    return this->getArrayAccess()->isSameAs(otherNode->getArrayAccess()) &&
           this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTArrayAccessInvocationExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _arrayAccess->print();
    _arguments->print();
    Logger::log("----------");
}

std::string ASTArrayAccessInvocationExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayAccess)
    ->add(_arguments);
    return sourceCodeBuilder.build();
}