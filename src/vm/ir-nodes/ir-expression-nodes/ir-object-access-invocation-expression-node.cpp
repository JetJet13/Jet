//
// Created by Johny Georges on 2025-06-20.
//

#include "ir-object-access-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRObjectAccessInvocationExpressionNode::IRObjectAccessInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, std::shared_ptr<IRExpressionNode> source, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, int64_t targetIndex, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type, std::optional<std::shared_ptr<IRExpressionNode>> scopeArgument) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _source = source;
    _targetIndex = targetIndex;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _scopeArgument = scopeArgument;
}

void IRObjectAccessInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

std::shared_ptr<IRExpressionNode> IRObjectAccessInvocationExpressionNode::getSource() {
    return _source;
}


std::optional<std::shared_ptr<IRExpressionNode>> IRObjectAccessInvocationExpressionNode::getScopeArgument() {
    return _scopeArgument;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRObjectAccessInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRObjectAccessInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

int64_t IRObjectAccessInvocationExpressionNode::getTargetIndex() {
    return _targetIndex;
}

std::shared_ptr<IRType> IRObjectAccessInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

std::shared_ptr<IRType> IRObjectAccessInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRObjectAccessInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRObjectAccessInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRObjectAccessInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRObjectAccessInvocationExpressionNode::getNodeType() {
    return IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE;
}

std::string IRObjectAccessInvocationExpressionNode::toString() {
    return "IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE";
}

void IRObjectAccessInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _source->getValue()->print(**stream);
}