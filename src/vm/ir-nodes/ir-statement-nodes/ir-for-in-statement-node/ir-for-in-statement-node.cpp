//
// Created by Johny Georges on 2025-05-24.
//

#include "ir-for-in-statement-node.h"

IRForInStatementNode::IRForInStatementNode(std::shared_ptr<ASTForInStatementNode> node, IRInstructionNode* index, IRInstructionNode* variable, IRExpressionNode* source, IRBlockNode* setupBlock, IRBlockNode* forInBlock, IRBlockNode* bodyBlock, IRBlockNode* endBlock, std::optional<IRCapturedVariableNode*> capturedVariable) {
    _node = node;
    _index = index;
    _variable = variable;
    _source = source;
    _setupBlock = setupBlock;
    _forInBlock = forInBlock;
    _bodyBlock = bodyBlock;
    _endBlock = endBlock;
    _capturedVariable = capturedVariable;
}

IRInstructionNode* IRForInStatementNode::getIndex() {
    return _index;
}

IRInstructionNode* IRForInStatementNode::getVariable() {
    return _variable;
}

std::optional<IRCapturedVariableNode*> IRForInStatementNode::getCapturedVariable() {
    return _capturedVariable;
}

IRExpressionNode* IRForInStatementNode::getSource() {
    return _source;
}

IRBlockNode* IRForInStatementNode::getSetupBlock() {
    return _setupBlock;
}

IRBlockNode* IRForInStatementNode::getForInBlock() {
    return _forInBlock;
}

IRBlockNode* IRForInStatementNode::getBodyBlock() {
    return _bodyBlock;
}

IRBlockNode* IRForInStatementNode::getEndBlock() {
    return _endBlock;
}

void IRForInStatementNode::nestIn(IRBlockNode* irBlock) {
    irBlock->nest(_setupBlock);
    irBlock->nest(_forInBlock);
    irBlock->nest(_bodyBlock);
    irBlock->nest(_endBlock);
}

IRNodeType IRForInStatementNode::getNodeType() {
    return IR_FOR_IN_STATEMENT_NODE;
}

std::string IRForInStatementNode::toString() {
    return "IR_FOR_IN_STATEMENT_NODE";
}

void IRForInStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _source->print(stream);
}