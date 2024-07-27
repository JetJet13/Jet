//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-literal-expression-node.h"

IRLiteralExpressionNode::IRLiteralExpressionNode(ASTLiteralExpressionNode* node, IRLiteralNode* irValue, IRInstructionNode* sourceAllocation) {
    _node = node;
    _irValue = irValue;
    _sourceAllocation = sourceAllocation;
}

llvm::Value* IRLiteralExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    if (_irValue->is(IR_STRING_LITERAL_NODE)) {
        auto allocation = builder->get()->CreateAlloca(_irValue->getType());
        builder->get()->CreateStore(_irValue->getConstantIRValue(), allocation);
        auto zero = builder->get()->getInt32(0);
        return builder->get()->CreateInBoundsGEP(
                _irValue->getType()->getArrayElementType(),
                allocation,
                { zero, zero }
        );
    }
    return _irValue->getConstantIRValue();
}

IRType* IRLiteralExpressionNode::getIRType() {
    return _irValue->getIRType();
}

llvm::Constant* IRLiteralExpressionNode::getValue() {
    return _irValue->getConstantIRValue();
}

IRInstructionNode* IRLiteralExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRNodeType IRLiteralExpressionNode::getNodeType() {
    return IR_LITERAL_EXPRESSION_NODE;
}

std::string IRLiteralExpressionNode::toString() {
    return "IR_LITERAL_EXPRESSION_NODE";
}

void IRLiteralExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}