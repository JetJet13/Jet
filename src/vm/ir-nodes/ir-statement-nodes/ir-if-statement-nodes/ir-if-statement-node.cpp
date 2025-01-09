//
// Created by Johny Georges on 2025-01-08.
//

#include "ir-if-statement-node.h"

IRIfStatementNode::IRIfStatementNode(ASTIfStatementNode* node, std::vector<IRIfElseNode*> ifElseNodes) {
    _node = node;
    _ifElseNodes = std::vector<IRIfElseNode*>();
}

std::vector<IRIfElseNode*>* IRIfStatementNode::getIfElseNodes() {
    return &_ifElseNodes;
}

IRNodeType IRIfStatementNode::getNodeType() {
    return IR_IF_STATEMENT_NODE;
}

std::string IRIfStatementNode::toString() {
    return "IR_IF_STATEMENT_NODE";
}

void IRIfStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    for (auto ifElseNode : _ifElseNodes) {
        ifElseNode->print(stream);
    }
}