//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-object-access-expression-node.h"
#include "ir-global-identifier-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRObjectAccessExpressionNode::IRObjectAccessExpressionNode(ASTObjectAccessExpressionNode* node, IRExpressionNode* irSource, std::string targetKey, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex) {
    _node = node;
    _irSource = irSource;
    _targetKey = targetKey;
    _irTargetKeyIndex = irTargetKeyIndex;
    _targetKeyIndex = targetKeyIndex;
}

llvm::Value* IRObjectAccessExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(
            _irSource->getIRType()->getSourceType()->getType(),
            _irSource->getValue(),
            { builder->get()->getInt32(0), _irTargetKeyIndex }
    );
    builder->get()->Insert(pointer);

    if (_irSource->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        return builder->get()->CreateLoad(this->getIRType()->getType(), pointer);
    }

    return builder->get()->CreateLoad(this->getIRType()->getType(), pointer);
}

IRType* IRObjectAccessExpressionNode::getIRType() {
    return ((IRStructType*)_irSource->getIRType()->getSourceType())->getIRTypeForKey(_targetKey);
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