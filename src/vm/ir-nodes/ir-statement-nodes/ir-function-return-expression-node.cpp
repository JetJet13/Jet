//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-function-return-expression-node.h"

IRFunctionReturnExpressionNode::IRFunctionReturnExpressionNode(ASTFunctionReturnExpressionNode* node, llvm::ReturnInst* irValue, IRExpressionNode* irExpression) {
    _node = node;
    _irValue = irValue;
    _irExpression = irExpression;
}

llvm::Value * IRFunctionReturnExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    return _irValue;
}

llvm::ReturnInst* IRFunctionReturnExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRFunctionReturnExpressionNode::getNodeType() {
    return IR_FUNCTION_RETURN_EXPRESSION_NODE;
}

std::string IRFunctionReturnExpressionNode::toString() {
    return "IR_FUNCTION_RETURN_EXPRESSION_NODE";
}

void IRFunctionReturnExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irExpression->print(stream);
}