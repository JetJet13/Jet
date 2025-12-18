//
// Created by Johny Georges on 2025-06-19.
//

#include "ir-tuple-access-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRTupleAccessInvocationExpressionNode::IRTupleAccessInvocationExpressionNode(ASTTupleAccessInvocationExpressionNode* node, IRTupleAccessExpressionNode* irTupleAccessExpression, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type) {
    _node = node;
    _irTupleAccessExpression = irTupleAccessExpression;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
}

void IRTupleAccessInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

bool IRTupleAccessInvocationExpressionNode::isReferenced() {
    return _node->isReferenced();
}

IRTupleAccessExpressionNode* IRTupleAccessInvocationExpressionNode::getIRTupleAccessExpression() {
    return _irTupleAccessExpression;
}

std::vector<IRExpressionNode*>* IRTupleAccessInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRTupleAccessInvocationExpressionNode::getValue() {
    return _irTupleAccessExpression->getValue();
}

IRType* IRTupleAccessInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRTupleAccessInvocationExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRTupleAccessInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRTupleAccessInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRTupleAccessInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRTupleAccessInvocationExpressionNode::getNodeType() {
    return IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE;
}

std::string IRTupleAccessInvocationExpressionNode::toString() {
    return "IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE";
}

void IRTupleAccessInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irTupleAccessExpression->getValue()->print(**stream);
}