//
// Created by Johny Georges on 2024-11-12.
//

#include "ir-lambda-expression-node.h"

IRLambdaExpressionNode::IRLambdaExpressionNode(ASTLambdaExpressionNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLambdaType* type) {
    _node = node;
    _irValue = irValue;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
    _type = type;
}

llvm::Function* IRLambdaExpressionNode::getValue() {
    return _irValue;
}

IRType* IRLambdaExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRLambdaExpressionNode::getTypeSignature() {
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