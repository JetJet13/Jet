//
// Created by Johny Georges on 2024-07-17.
//

#include "ir-global-identifier-expression-node.h"

IRGlobalIdentifierExpressionNode::IRGlobalIdentifierExpressionNode(ASTIdentifierExpressionNode* node, llvm::GlobalVariable* irValue) {
    _node = node;
    _irValue = irValue;
}

llvm::GlobalVariable* IRGlobalIdentifierExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    return _irValue;
}

llvm::GlobalVariable* IRGlobalIdentifierExpressionNode::getIRValue() {
    return _irValue;
}

llvm::Type* IRGlobalIdentifierExpressionNode::getType() {
    return _irValue->getValueType();
}

llvm::Type* IRGlobalIdentifierExpressionNode::getTypeAtIndex(unsigned long index) {
    auto type = _irValue->getType();
    if (type->isArrayTy()) {
        return type->getArrayElementType();
    } else if (type->isStructTy()) {
        return type->getStructElementType(index);
    } else {
        return type;
    }
}

IRNodeType IRGlobalIdentifierExpressionNode::getNodeType() {
    return IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE;
}

std::string IRGlobalIdentifierExpressionNode::toString() {
    return "IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE";
}

void IRGlobalIdentifierExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}