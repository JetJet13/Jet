//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-object-access-expression-node.h"
#include "ir-global-identifier-expression-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../ir-support-functions/ir-copy-array-support-function/ir-copy-array-support-function.h"
#include "../../ir-support-functions/ir-array-pointer-support-function/ir-array-pointer-support-function.h"
#include "../../ir-injector/ir-injector-map.h"

IRObjectAccessExpressionNode::IRObjectAccessExpressionNode(ASTObjectAccessExpressionNode* node, IRExpressionNode* irSource, std::string targetKey, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex, IRType* irType, std::optional<IRInstructionNode*> sourceAllocation) {
    _node = node;
    _irSource = irSource;
    _targetKey = targetKey;
    _irTargetKeyIndex = irTargetKeyIndex;
    _targetKeyIndex = targetKeyIndex;
    _irType = irType;
    _sourceAllocation = sourceAllocation;
}

llvm::Value * IRObjectAccessExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *injectorMap) {
    if (_node->getTypeSignature()->typeSourceIs(ENUM_ACCESS_TYPE_SOURCE)) {
        return injectorMap->getInjector(_node->getTypeSignature())->inject(this, builder);
    }

    if (_sourceAllocation) {
        builder->get()->Insert(_sourceAllocation.value()->getValue());
    }
    if (this->getTargetIRType()->isArrayPointerType()) {
        auto sourceAllocation = _irSource->getRootAllocationAtIndex(_targetKeyIndex).value();
        IRCopyArraySupportFunction::insertSelfIntoBlock(
                builder,
                sourceAllocation,
                _sourceAllocation.value());
        auto arrayPointerType = (IRArrayPointerType*)this->getTargetIRType();
        auto arrayPointerTypeAllocation = IRInstructionNodeFactory::create(sourceAllocation, _sourceAllocation.value());
        return IRArrayPointerSupportFunction::insertSelfIntoBlock(builder, arrayPointerType, arrayPointerTypeAllocation);
    }

    auto pointer = llvm::GetElementPtrInst::CreateInBounds(
            _irSource->getIRType()->getSourceType()->getType(),
            _irSource->getValue(),
            { builder->get()->getInt32(0), _irTargetKeyIndex }
    );
    builder->get()->Insert(pointer);

    if (_irSource->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        auto loadedValue = builder->get()->CreateLoad(this->getTargetIRType()->getType(), pointer);
        if (_irType->isArrayPointerType()) {
            builder->get()->CreateStore(loadedValue, _sourceAllocation.value()->getValue());
            auto arrayPointerType = (IRArrayPointerType*)_irType;
            auto arrayPointerTypeAllocation = builder->get()->CreateAlloca(arrayPointerType->getType());
            return IRArrayPointerSupportFunction::insertSelfIntoBlock(builder, arrayPointerType, _sourceAllocation.value(), arrayPointerTypeAllocation);
        } else {
            return loadedValue;
        }
    }

    return builder->get()->CreateLoad(this->getTargetIRType()->getType(), pointer);
}

IRExpressionNode* IRObjectAccessExpressionNode::getSource() {
    return _irSource;
}

std::string* IRObjectAccessExpressionNode::getTargetKey() {
    return &_targetKey;
}

llvm::Constant* IRObjectAccessExpressionNode::getIRTargetKeyIndex() {
    return _irTargetKeyIndex;
}

unsigned long IRObjectAccessExpressionNode::getTargetKeyIndex() {
    return _targetKeyIndex;
}

IRType* IRObjectAccessExpressionNode::getIRType() {
    return _irType;
}

IRType* IRObjectAccessExpressionNode::getTargetIRType() {
    return ((IRStructType*)_irSource->getIRType()->getSourceType())->getIRTypeForKey(_targetKey);
}

llvm::Value* IRObjectAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

std::optional<IRInstructionNode*> IRObjectAccessExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
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