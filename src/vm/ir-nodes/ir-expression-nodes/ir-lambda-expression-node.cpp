//
// Created by Johny Georges on 2024-11-12.
//

#include "ir-lambda-expression-node.h"

IRLambdaExpressionNode::IRLambdaExpressionNode(ASTLambdaExpressionNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLambdaType* type, llvm::Function* irCleanupFunction) {
    _node = node;
    _irValue = irValue;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
    _type = type;
    _irCleanupFunction = irCleanupFunction;
}

llvm::Function* IRLambdaExpressionNode::getCleanupFunction() {
    return _irCleanupFunction;
}

llvm::Function* IRLambdaExpressionNode::getValue() {
    return _irValue;
}

IRLambdaType* IRLambdaExpressionNode::getIRType() {
    return _type;
}

LambdaExpressionTypeSignature* IRLambdaExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRLambdaExpressionNode::getNodeType() {
    return IR_LAMBDA_EXPRESSION_NODE;
}

std::string IRLambdaExpressionNode::toString() {
    return "IR_LAMBDA_EXPRESSION_NODE";
}

void IRLambdaExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}