//
// Created by Johny Georges on 2024-07-06.
//

#include "ir-array-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRArrayAccessExpressionNode::IRArrayAccessExpressionNode(std::shared_ptr<ASTArrayAccessExpressionNode> node, IRExpressionNode* irSource, IRExpressionNode* irIndex, std::shared_ptr<IRType> type, std::optional<IRInstructionNode*> sourceAllocation) {
    _node = node;
    _irSource = irSource;
    _irIndex = irIndex;
    _type = type;
    _sourceAllocation = sourceAllocation;
}

void IRArrayAccessExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irSource->markAsGlobal();
    _irIndex->markAsGlobal();
}


IRExpressionNode* IRArrayAccessExpressionNode::getSourceExpression() {
    return _irSource;
}

IRExpressionNode* IRArrayAccessExpressionNode::getIndexExpression() {
    return _irIndex;
}

std::shared_ptr<ASTArrayAccessExpressionNode> IRArrayAccessExpressionNode::getNode() {
    return _node;
}

std::optional<IRInstructionNode*> IRArrayAccessExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

llvm::Value* IRArrayAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

std::shared_ptr<IRType> IRArrayAccessExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRArrayAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRArrayAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRArrayAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRArrayAccessExpressionNode::getNodeType() {
    return IR_ARRAY_ACCESS_EXPRESSION_NODE;
}

std::string IRArrayAccessExpressionNode::toString() {
    return "IR_ARRAY_ACCESS_EXPRESSION_NODE";
}

void IRArrayAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irSource->print(stream);
    _irIndex->print(stream);
}