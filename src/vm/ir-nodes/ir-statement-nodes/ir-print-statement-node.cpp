//
// Created by Johny Georges on 2025-07-21.
//

#include "ir-print-statement-node.h"

IRPrintStatementNode::IRPrintStatementNode(ASTPrintStatementNode* node, std::vector<IRExpressionNode*> arguments, llvm::Value* newLine, llvm::Value* whitespace) {
    _node = node;
    _arguments = arguments;
    _newLine = newLine;
    _whitespace = whitespace;
}

std::vector<IRExpressionNode*>* IRPrintStatementNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRPrintStatementNode::getNewLine() {
    return _newLine;
}

llvm::Value* IRPrintStatementNode::getWhitespace() {
    return _whitespace;
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