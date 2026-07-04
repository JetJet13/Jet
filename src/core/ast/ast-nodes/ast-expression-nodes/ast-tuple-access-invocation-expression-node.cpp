//
// Created by Johny Georges on 2025-06-18.
//

#include "ast-tuple-access-invocation-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTupleAccessInvocationExpressionNode::ASTTupleAccessInvocationExpressionNode(std::shared_ptr<ASTTupleAccessExpressionNode> tupleAccess, std::shared_ptr<ASTFunctionArgumentListNode> arguments) {
    _tupleAccess = tupleAccess;
    _arguments = arguments;
    _children.push_back(_tupleAccess);
    _children.push_back(_arguments);
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTTupleAccessInvocationExpressionNode::getArguments() {
    return _arguments;
}

std::shared_ptr<ASTTupleAccessExpressionNode> ASTTupleAccessInvocationExpressionNode::getObjectAccess() {
    return _tupleAccess;
}

std::shared_ptr<ASTObjectAccessSourceNode> ASTTupleAccessInvocationExpressionNode::getSource() {
    return _tupleAccess->getSource();
}

std::shared_ptr<ASTTupleAccessNode> ASTTupleAccessInvocationExpressionNode::getIndex() {
    return _tupleAccess->getIndex();
}

InvocableTypeSignature* ASTTupleAccessInvocationExpressionNode::getInvocableTypeSignature() {
    return (InvocableTypeSignature*)_tupleAccess->getTypeSignature();
}

unsigned long ASTTupleAccessInvocationExpressionNode::numArguments() {
    return _arguments->numArguments();
}

Position* ASTTupleAccessInvocationExpressionNode::getStartPosition() {
    return _tupleAccess->getStartPosition();
}

Position* ASTTupleAccessInvocationExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTTupleAccessInvocationExpressionNode::getNodeType() {
    return AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE;
}

std::string ASTTupleAccessInvocationExpressionNode::toString() {
    return "AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE";
}

bool ASTTupleAccessInvocationExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleAccessInvocationExpressionNode>(other);

    return this->getObjectAccess()->isSameAs(otherNode->getObjectAccess()) &&
           this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTTupleAccessInvocationExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _tupleAccess->print();
    _arguments->print();
    Logger::log("----------");
}

std::string ASTTupleAccessInvocationExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleAccess)
            ->add(_arguments);
    return sourceCodeBuilder.build();
}