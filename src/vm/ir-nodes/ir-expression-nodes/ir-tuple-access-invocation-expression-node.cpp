//
// Created by Johny Georges on 2025-06-19.
//

#include "ir-tuple-access-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRTupleAccessInvocationExpressionNode::IRTupleAccessInvocationExpressionNode(std::shared_ptr<ASTTupleAccessInvocationExpressionNode> node, IRExpressionNode* source, llvm::CallInst* irCallInstruction, IRType* irFunctionType, int64_t targetIndex, std::vector<IRFunctionArgumentNode*> arguments, IRType* type) {
    _node = node;
    _source = source;
    _irCallInstruction = irCallInstruction;
    _irFunctionType = irFunctionType;
    _targetIndex = targetIndex;
    _arguments = arguments;
    _type = type;
}

void IRTupleAccessInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

IRExpressionNode* IRTupleAccessInvocationExpressionNode::getSource() {
    return _source;
}

std::vector<IRFunctionArgumentNode*>* IRTupleAccessInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRTupleAccessInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

IRType* IRTupleAccessInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

int64_t IRTupleAccessInvocationExpressionNode::getTargetIndex() {
    return _targetIndex;
}

IRType* IRTupleAccessInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRTupleAccessInvocationExpressionNode::getTypeSignature() {
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
    _irCallInstruction->print(**stream);
}