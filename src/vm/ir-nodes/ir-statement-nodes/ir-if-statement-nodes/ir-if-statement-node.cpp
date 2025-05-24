//
// Created by Johny Georges on 2025-01-08.
//

#include "ir-if-statement-node.h"

IRIfStatementNode::IRIfStatementNode(ASTIfStatementNode* node, IRIfElseNode* ifElseNode) {
    _node = node;
    _ifElseNode = ifElseNode;
}

IRIfElseNode* IRIfStatementNode::getIfElseNode() {
    return _ifElseNode;
}

IRNodeType IRIfStatementNode::getNodeType() {
    return IR_IF_STATEMENT_NODE;
}

std::string IRIfStatementNode::toString() {
    return "IR_IF_STATEMENT_NODE";
}

void IRIfStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _ifElseNode->print(stream);
}