//
// Created by Johny Georges on 2025-07-21.
//

#include "ir-print-statement-node.h"

IRPrintStatementNode::IRPrintStatementNode(ASTPrintStatementNode* node, std::vector<IRExpressionNode*> arguments) {
    _node = node;
    _arguments = arguments;
}

std::vector<IRExpressionNode*>* IRPrintStatementNode::getIRArguments() {
    return &_arguments;
}

IRNodeType IRPrintStatementNode::getNodeType() {
    return IR_PRINT_STATEMENT_NODE;
}

std::string IRPrintStatementNode::toString() {
    return "IR_PRINT_STATEMENT_NODE";
}

void IRPrintStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    for (auto argument : _arguments) {
        argument->print(stream);
    }
}