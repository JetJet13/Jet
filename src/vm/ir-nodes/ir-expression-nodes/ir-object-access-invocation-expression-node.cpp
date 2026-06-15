//
// Created by Johny Georges on 2025-06-20.
//

#include "ir-object-access-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRObjectAccessInvocationExpressionNode::IRObjectAccessInvocationExpressionNode(ASTObjectAccessInvocationExpressionNode* node, IRExpressionNode* source, llvm::CallInst* irCallInstruction, IRType* irFunctionType, int64_t targetIndex, std::vector<IRFunctionArgumentNode*> arguments, IRType* type, std::optional<IRExpressionNode*> scopeArgument) {
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

IRExpressionNode* IRObjectAccessInvocationExpressionNode::getSource() {
    return _source;
}


std::optional<IRExpressionNode*> IRObjectAccessInvocationExpressionNode::getScopeArgument() {
    return _scopeArgument;
}

std::vector<IRFunctionArgumentNode*>* IRObjectAccessInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRObjectAccessInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

int64_t IRObjectAccessInvocationExpressionNode::getTargetIndex() {
    return _targetIndex;
}

IRType* IRObjectAccessInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRObjectAccessInvocationExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRObjectAccessInvocationExpressionNode::getTypeSignature() {
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