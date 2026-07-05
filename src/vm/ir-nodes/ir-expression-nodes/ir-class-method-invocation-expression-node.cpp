//
// Created by Johny Georges on 2024-12-27.
//

#include "ir-class-method-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRClassMethodInvocationExpressionNode::IRClassMethodInvocationExpressionNode(std::shared_ptr<ASTClassMethodInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<IRFunctionArgumentNode*> arguments, std::shared_ptr<IRType> type, IRInstructionNode* classScopeArgument) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _classScopeArgument = classScopeArgument;
}

void IRClassMethodInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

IRInstructionNode* IRClassMethodInvocationExpressionNode::getClassScopeArgument() {
    return _classScopeArgument;
}

std::vector<IRFunctionArgumentNode*>* IRClassMethodInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRClassMethodInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

llvm::Value* IRClassMethodInvocationExpressionNode::getFunctionValue() {
    return _irFunction;
}

std::shared_ptr<IRType> IRClassMethodInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

std::shared_ptr<IRType> IRClassMethodInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRClassMethodInvocationExpressionNode::getTypeSignature() {
    return _node->getName()->getMethodTypeSignature()->getReturnType();
}

Position* IRClassMethodInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRClassMethodInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRClassMethodInvocationExpressionNode::getNodeType() {
    return IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE;
}

std::string IRClassMethodInvocationExpressionNode::toString() {
    return "IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE";
}

void IRClassMethodInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}