//
// Created by Johny Georges on 2024-11-12.
//

#include "ir-lambda-with-block-expression-node.h"

IRLambdaWithBlockExpressionNode::IRLambdaWithBlockExpressionNode(std::shared_ptr<ASTLambdaExpressionNode> node, IRInstructionNode* irValue, llvm::Function* irFunction, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRLambdaType* type, llvm::Function* irCleanupFunction) {
    _node = node;
    _irValue = irValue;
    _irFunction = irFunction;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
    _type = type;
    _irCleanupFunction = irCleanupFunction;
}

llvm::Function* IRLambdaWithBlockExpressionNode::getCleanupFunction() {
    return _irCleanupFunction;
}

IRFunctionParameterListNode* IRLambdaWithBlockExpressionNode::getParameters() {
    return _irParameterList;
}

IRBlockNode* IRLambdaWithBlockExpressionNode::getBlock() {
    return _irBlock;
}

llvm::Value* IRLambdaWithBlockExpressionNode::getValue() {
    return _irValue->getValue();
}

IRInstructionNode* IRLambdaWithBlockExpressionNode::getAllocation() {
    return _irValue;
}

llvm::Function* IRLambdaWithBlockExpressionNode::getFunctionValue() {
    return _irFunction;
}

IRLambdaType* IRLambdaWithBlockExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRLambdaWithBlockExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRLambdaWithBlockExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRLambdaWithBlockExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRLambdaWithBlockExpressionNode::getNodeType() {
    return IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE;
}

std::string IRLambdaWithBlockExpressionNode::toString() {
    return "IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE";
}

void IRLambdaWithBlockExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}