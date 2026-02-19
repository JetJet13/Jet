//
// Created by Johny Georges on 2024-11-14.
//

#include "ir-lambda-with-fat-arrow-expression-node.h"

IRLambdaWithFatArrowExpressionNode::IRLambdaWithFatArrowExpressionNode(ASTLambdaWithFatArrowExpressionNode* node, IRInstructionNode* irValue, llvm::Function* irFunction, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLambdaType* type, llvm::Function* irCleanupFunction, IRExpressionNode* irReturnExpression) {
    _node = node;
    _irValue = irValue;
    _irFunction = irFunction;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
    _irReturnExpression = irReturnExpression;
    _type = type;
    _irCleanupFunction = irCleanupFunction;
}

llvm::Function* IRLambdaWithFatArrowExpressionNode::getCleanupFunction() {
    return _irCleanupFunction;
}

IRBlockNode* IRLambdaWithFatArrowExpressionNode::getBlock() {
    return _irBlock;
}

IRExpressionNode* IRLambdaWithFatArrowExpressionNode::getReturnExpression() {
    return _irReturnExpression;
}

IRInstructionNode* IRLambdaWithFatArrowExpressionNode::getAllocation() {
    return _irValue;
}

llvm::Function* IRLambdaWithFatArrowExpressionNode::getFunctionValue() {
    return _irFunction;
}

IRFunctionParameterListNode* IRLambdaWithFatArrowExpressionNode::getParameters() {
    return _irParameterList;
}

llvm::Value* IRLambdaWithFatArrowExpressionNode::getValue() {
    return _irValue->getValue();
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
    _irFunction->print(**stream);
}