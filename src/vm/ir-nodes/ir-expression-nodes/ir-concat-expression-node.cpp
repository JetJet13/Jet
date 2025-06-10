//
// Created by Johny Georges on 2025-06-09.
//

#include "ir-concat-expression-node.h"

IRConcatExpressionNode::IRConcatExpressionNode(ASTConcatExpressionNode* astNode, IRInstructionNode* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRArrayPointerType* type) {
    _node = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _type = type;
}

void IRConcatExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irLeftNode->markAsGlobal();
    _irRightNode->markAsGlobal();
}

llvm::Value* IRConcatExpressionNode::getValue() {
    return _irValue->getValue();
}

IRExpressionNode* IRConcatExpressionNode::getLeftNode() {
    return _irLeftNode;
}

IRExpressionNode* IRConcatExpressionNode::getRightNode() {
    return _irRightNode;
}

std::optional<IRInstructionNode*> IRConcatExpressionNode::getSourceAllocation() {
    return _irValue;
}

IRArrayPointerType* IRConcatExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRConcatExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRConcatExpressionNode::getNodeType() {
    return IR_CONCAT_EXPRESSION_NODE;
}

std::string IRConcatExpressionNode::toString() {
    return "IR_CONCAT_EXPRESSION_NODE";
}

void IRConcatExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->getValue()->print(**stream);
    stream->get()->write('\n');
    _irLeftNode->print(stream);
    stream->get()->write('\n');
    _irRightNode->print(stream);
}