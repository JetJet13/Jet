//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-object-access-expression-node.h"
#include "ir-global-identifier-expression-node.h"

IRObjectAccessExpressionNode::IRObjectAccessExpressionNode(ASTObjectAccessExpressionNode* node, IRExpressionNode* irSource, std::string targetKey, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex, IRPointerType* irType) {
    _node = node;
    _irSource = irSource;
    _targetKey = targetKey;
    _irTargetKeyIndex = irTargetKeyIndex;
    _targetKeyIndex = targetKeyIndex;
    _irType = irType;
}

llvm::Value* IRObjectAccessExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    if (_irSource->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(
                _irSource->getType(),
                _irSource->getValue(),
                { builder->get()->getInt32(0), _irTargetKeyIndex }
        );
        return builder->get()->Insert(pointer);

    }

    _irSource->insertSelfIntoBlock(builder);
    auto allocation = builder->get()->CreateAlloca(_irType->getPointerSourceIRType()->getType());
    auto valueToLoad = _irSource->getSourceAllocationAtIndex(_targetKeyIndex);
    auto loadedValue = builder->get()->CreateLoad(_irType->getPointerSourceIRType()->getType(), valueToLoad->getValue());
    builder->get()->CreateStore(loadedValue, allocation);
    return allocation;
}

IRPointerType* IRObjectAccessExpressionNode::getIRType() {
    return _irType;
}

llvm::Value* IRObjectAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

IRInstructionNode* IRObjectAccessExpressionNode::getSourceAllocation() {
    if (_irSource->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
     return _irSource->getSourceAllocation();
    }
    return _irSource->getSourceAllocation()->getSourceAllocationAtIndex(_targetKeyIndex);
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