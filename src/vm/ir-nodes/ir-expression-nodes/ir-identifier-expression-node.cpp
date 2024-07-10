//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-identifier-expression-node.h"

IRIdentifierExpressionNode::IRIdentifierExpressionNode(ASTIdentifierExpressionNode* astNode, IRExpressionNode* irNode) {
    _astNode = astNode;
    _irNode = irNode;
}

llvm::Value* IRIdentifierExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    return builder->get()->CreateStore(builder->get()->Insert(_irNode->getIRValue()), parent);
}

llvm::Value* IRIdentifierExpressionNode::getIRValue() {
    return _irNode->getIRValue();
}

llvm::Type* IRIdentifierExpressionNode::getIRTypeAtIndex(unsigned long index) {
    return _irNode->getIRTypeAtIndex(index);
}

IRNodeType IRIdentifierExpressionNode::getNodeType() {
    return IR_IDENTIFIER_EXPRESSION_NODE;
}

std::string IRIdentifierExpressionNode::toString() {
    return "IR_IDENTIFIER_EXPRESSION_NODE";
}

void IRIdentifierExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irNode->print(stream);
}