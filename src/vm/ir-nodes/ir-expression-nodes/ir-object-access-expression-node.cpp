//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-object-access-expression-node.h"

IRObjectAccessExpressionNode::IRObjectAccessExpressionNode(ASTObjectAccessExpressionNode* node, IRExpressionNode* irSource, std::string targetKey, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex) {
    _node = node;
    _irSource = irSource;
    _targetKey = targetKey;
    _irTargetKeyIndex = irTargetKeyIndex;
    _targetKeyIndex = targetKeyIndex;
}

llvm::Value* IRObjectAccessExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    if (_irSource->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        return llvm::GetElementPtrInst::CreateInBounds(
                _irSource->getIRType()->getType(),
                _irSource->getValue(),
                { builder->get()->getInt32(0), _irTargetKeyIndex }
        );
    }
    auto sourceValue = _irSource->insertSelfIntoBlock(builder);
    // we need to return a pointer to the source allocation of the target because we want to copy the value
    // from the source (required for aggregate types (strings, tuples, structs and arrays)
    // todo: create a source allocation lookup table
    return _irSource->getSourceAllocationAtIndex(_targetKeyIndex)->getValue();
}

IRType* IRObjectAccessExpressionNode::getIRType() {
    return _irSource->getIRType();
}

llvm::Value* IRObjectAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

IRInstructionNode* IRObjectAccessExpressionNode::getSourceAllocation() {
    return _irSource->getSourceAllocation();
}

IRNodeType IRObjectAccessExpressionNode::getNodeType() {
    return IR_OBJECT_ACCESS_EXPRESSION_NODE;
}

std::string IRObjectAccessExpressionNode::toString() {
    return "IR_OBJECT_ACCESS_EXPRESSION_NODE";
}

void IRObjectAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irSource->print(stream);
}