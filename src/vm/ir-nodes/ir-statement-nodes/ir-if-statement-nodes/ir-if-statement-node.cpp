//
// Created by Johny Georges on 2025-01-08.
//

#include "ir-if-statement-node.h"

IRIfStatementNode::IRIfStatementNode(std::shared_ptr<ASTIfStatementNode> node, IRIfElseNode* ifElseNode, std::optional<IRBlockNode*> elseNode) {
    _node = node;
    _ifElseNode = ifElseNode;
    _elseNode = elseNode;
}

IRIfElseNode* IRIfStatementNode::getIfElseNode() {
    return _ifElseNode;
}

std::optional<IRBlockNode*> IRIfStatementNode::getElseNode() {
    return _elseNode;
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