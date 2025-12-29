//
// Created by Johny Georges on 2024-11-08.
//

#include "ir-function-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRFunctionInvocationExpressionNode::IRFunctionInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, IRInstructionNode* irFunction, llvm::CallInst* irCallInstruction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, std::optional<IRInstructionNode*> varArgsTypeValueArgument) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _varArgsTypeValueArgument = varArgsTypeValueArgument;
}

void IRFunctionInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

bool IRFunctionInvocationExpressionNode::isReferenced() {
    return _node->isReferenced();
}

std::optional<IRInstructionNode*> IRFunctionInvocationExpressionNode::getVarArgsTypeValueArgument() {
    return _varArgsTypeValueArgument;
}

std::vector<IRExpressionNode*>* IRFunctionInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

ASTFunctionInvocationExpressionNode* IRFunctionInvocationExpressionNode::getNode() {
    return _node;
}

llvm::CallInst* IRFunctionInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

IRInstructionNode* IRFunctionInvocationExpressionNode::getFunction() {
    return _irFunction;
}

llvm::Value* IRFunctionInvocationExpressionNode::getFunctionValue() {
    return _irFunction->getValue();
}

IRType* IRFunctionInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRFunctionInvocationExpressionNode::getIRType() {
    return _type;
}

FunctionInvocationTypeSignature* IRFunctionInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRFunctionInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRFunctionInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRFunctionInvocationExpressionNode::getNodeType() {
    return IR_FUNCTION_INVOCATION_EXPRESSION_NODE;
}

std::string IRFunctionInvocationExpressionNode::toString() {
    return "IR_FUNCTION_INVOCATION_EXPRESSION_NODE";
}

void IRFunctionInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->getValue()->print(**stream);
}