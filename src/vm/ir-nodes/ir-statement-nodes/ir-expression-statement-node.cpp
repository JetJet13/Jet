//
// Created by Johny Georges on 2024-11-25.
//

#include "ir-expression-statement-node.h"

IRExpressionStatementNode::IRExpressionStatementNode(ASTExpressionStatementNode* node, IRExpressionNode* irExpression) {
    _node = node;
    _irExpression = irExpression;
}

IRExpressionNode* IRExpressionStatementNode::getExpression() {
    return _irExpression;
}

IRNodeType IRExpressionStatementNode::getNodeType() {
    return IR_EXPRESSION_STATEMENT_NODE;
}

std::string IRExpressionStatementNode::toString() {
    return "IR_EXPRESSION_STATEMENT_NODE";
}

void IRExpressionStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}