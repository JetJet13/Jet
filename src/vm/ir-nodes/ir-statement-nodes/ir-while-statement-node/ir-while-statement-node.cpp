//
// Created by Johny Georges on 2025-05-24.
//

#include "ir-while-statement-node.h"

IRWhileStatementNode::IRWhileStatementNode(ASTWhileStatementNode* node, IRExpressionNode* condition, IRBlockNode* whileBlock, IRBlockNode* bodyBlock, IRBlockNode* endBlock) {
    _condition = condition;
    _whileBlock = whileBlock;
    _bodyBlock = bodyBlock;
    _endBlock = endBlock;
}

IRExpressionNode* IRWhileStatementNode::getExpression() {
    return _condition;
}

IRBlockNode* IRWhileStatementNode::getWhileBlock() {
    return _whileBlock;
}

IRBlockNode* IRWhileStatementNode::getBodyBlock() {
    return _bodyBlock;
}

IRBlockNode* IRWhileStatementNode::getEndBlock() {
    return _endBlock;
}

void IRWhileStatementNode::setBlocksToBeSuccessorsOf(IRBlockNode* irBlock) {
    irBlock->addSuccessor(_whileBlock);
    irBlock->addSuccessor(_bodyBlock);
    irBlock->addSuccessor(_endBlock);
}

IRNodeType IRWhileStatementNode::getNodeType() {
    return IR_WHILE_STATEMENT_NODE;
}

std::string IRWhileStatementNode::toString() {
    return "IR_WHILE_STATEMENT_NODE";
}

void IRWhileStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _condition->print(stream);
}