//
// Created by Johny Georges on 2024-07-06.
//

#include "ir-array-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRArrayAccessExpressionNode::IRArrayAccessExpressionNode(ASTArrayAccessExpressionNode* node, IRExpressionNode* irSource, IRExpressionNode* irIndex, IRType* type, llvm::Function* arrayAccessFunction) {
    _node = node;
    _irSource = irSource;
    _irIndex = irIndex;
    _type = type;
    _arrayAccessFunction = arrayAccessFunction;
}

IRExpressionNode* IRArrayAccessExpressionNode::getSourceExpression() {
    return _irSource;
}

IRExpressionNode* IRArrayAccessExpressionNode::getIndexExpression() {
    return _irIndex;
}

llvm::Value* IRArrayAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

IRType* IRArrayAccessExpressionNode::getIRType() {
    return _type;
}

llvm::Function* IRArrayAccessExpressionNode::getArrayAccessFunction() {
    return _arrayAccessFunction;
}

TypeSignature* IRArrayAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
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