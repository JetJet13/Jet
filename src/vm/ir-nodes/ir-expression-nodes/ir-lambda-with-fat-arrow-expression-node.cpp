//
// Created by Johny Georges on 2024-11-14.
//

#include "ir-lambda-with-fat-arrow-expression-node.h"

IRLambdaWithFatArrowExpressionNode::IRLambdaWithFatArrowExpressionNode(ASTLambdaWithFatArrowExpressionNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLambdaType* type, llvm::Function* irCleanupFunction) {
    _node = node;
    _irValue = irValue;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
    _type = type;
    _irCleanupFunction = irCleanupFunction;
}

llvm::Function* IRLambdaWithFatArrowExpressionNode::getCleanupFunction() {
    return _irCleanupFunction;
}

llvm::Function* IRLambdaWithFatArrowExpressionNode::getValue() {
    return _irValue;
}

IRLambdaType* IRLambdaWithFatArrowExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRLambdaWithFatArrowExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRLambdaWithFatArrowExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRLambdaWithFatArrowExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRLambdaWithFatArrowExpressionNode::getNodeType() {
    return IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE;
}

std::string IRLambdaWithFatArrowExpressionNode::toString() {
    return "IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE";
}

void IRLambdaWithFatArrowExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}