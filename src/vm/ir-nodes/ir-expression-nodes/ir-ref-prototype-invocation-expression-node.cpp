//
// Created by Johny Georges on 2025-10-25.
//

#include "ir-ref-prototype-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRRefPrototypeInvocationExpressionNode::IRRefPrototypeInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, IRType* irFunctionType, std::vector<IRFunctionArgumentNode*> arguments, IRType* type, IRExpressionNode* irRef) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _irRef = irRef;
}

void IRRefPrototypeInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

IRExpressionNode* IRRefPrototypeInvocationExpressionNode::getIRRefValue() {
    return _irRef;
}

std::vector<IRFunctionArgumentNode*>* IRRefPrototypeInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRRefPrototypeInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

llvm::Value* IRRefPrototypeInvocationExpressionNode::getFunctionValue() {
    return _irFunction;
}

IRType* IRRefPrototypeInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRRefPrototypeInvocationExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRRefPrototypeInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRRefPrototypeInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRRefPrototypeInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRRefPrototypeInvocationExpressionNode::getNodeType() {
    return IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE;
}

std::string IRRefPrototypeInvocationExpressionNode::toString() {
    return "IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE";
}

void IRRefPrototypeInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}