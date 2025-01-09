//
// Created by Johny Georges on 2025-01-08.
//

#include "ir-if-else-node.h"

IRIfElseNode::IRIfElseNode(IRExpressionNode* condition, IRBlockNode* thenBlock, IRBlockNode* elseBlock) {
    _condition = condition;
    _thenBlock = thenBlock;
    _elseBlock = elseBlock;
}

IRExpressionNode* IRIfElseNode::getExpression() {
    return _condition;
}

IRBlockNode* IRIfElseNode::getThenBlock() {
    return _thenBlock;
}

IRBlockNode* IRIfElseNode::getElseBlock() {
    return _elseBlock;
}

IRNodeType IRIfElseNode::getNodeType() {
    return IR_IF_ELSE_NODE;
}

std::string IRIfElseNode::toString() {
    return "IR_IF_ELSE_NODE";
}

void IRIfElseNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _condition->print(stream);
}