//
// Created by Johny Georges on 2024-08-05.
//

#include "ir-string-literal-expression-node.h"
#include "../../ir-support-functions/ir-array-pointer-support-function/ir-array-pointer-support-function.h"

IRStringLiteralExpressionNode::IRStringLiteralExpressionNode(ASTLiteralExpressionNode* node, IRStringLiteralNode* irValue, IRArrayPointerType* irArrayPointerType, IRInstructionNode* sourceAllocation, IRInstructionNode* arrayPointerSourceAllocation) {
    _node = node;
    _irValue = irValue;
    _irArrayPointerType = irArrayPointerType;
    _sourceAllocation = sourceAllocation;
    _arrayPointerSourceAllocation = arrayPointerSourceAllocation;
}

llvm::Value* IRStringLiteralExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *injectorMap) {
    return injectorMap->getStringInjector()->inject(this, builder);
}

IRArrayPointerType* IRStringLiteralExpressionNode::getIRType() {
    return _irArrayPointerType;
}

llvm::Constant* IRStringLiteralExpressionNode::getValue() {
    return _irValue->getConstantIRValue();
}

std::optional<IRInstructionNode*> IRStringLiteralExpressionNode::getSourceAllocation() {
    return _arrayPointerSourceAllocation;
}

std::optional<IRInstructionNode*> IRStringLiteralExpressionNode::getRootAllocation() {
    return _sourceAllocation;
}

IRInstructionNode* IRStringLiteralExpressionNode::getSourceArrayAllocation() {
    return _sourceAllocation;
}

IRInstructionNode* IRStringLiteralExpressionNode::getArrayPointerAllocation() {
    return _arrayPointerSourceAllocation;
}

IRNodeType IRStringLiteralExpressionNode::getNodeType() {
    return IR_STRING_LITERAL_EXPRESSION_NODE;
}

std::string IRStringLiteralExpressionNode::toString() {
    return "IR_STRING_LITERAL_EXPRESSION_NODE";
}

void IRStringLiteralExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}