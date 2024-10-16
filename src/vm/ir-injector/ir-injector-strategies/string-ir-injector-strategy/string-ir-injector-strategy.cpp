//
// Created by Johny Georges on 2024-08-12.
//

#include "string-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

llvm::Value* StringIRInjectorStrategy::inject(IRExpressionNode *irExpression, std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    if (irExpression->is(IR_STRING_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRStringLiteralExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRAggregateIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRTupleAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    }
    throw std::logic_error("StringIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StringIRInjectorStrategy::inject(IRStringLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto arrayAllocation = irExpression->getSourceAggregateAllocation()->getValue();
    builder->get()->Insert(arrayAllocation);
    builder->get()->CreateStore(irExpression->getValue(), arrayAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(builder, irExpression->getIRType(), irExpression->getValue()->getType()->getArrayNumElements(),
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRAggregateIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, builder, irModule)->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    if (irExpression->getSource()->is(IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE)) {
        auto arrayAllocation = irExpression->getSourceAllocation().value()->getParentAllocation().value();
        builder->get()->Insert(arrayAllocation->getValue());
        auto type = irExpression->getSource()->getIRType()->getSourceType()->getType()->getStructElementType(irExpression->getTargetKeyIndex());
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(
                irExpression->getSource()->getType(),
                irExpression->getSource()->getValue(),
                { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() }
        );
        builder->get()->Insert(pointer);
        auto loaded = builder->get()->CreateLoad(type, pointer);
        builder->get()->CreateStore(loaded, arrayAllocation->getValue());
        return ArrayIRInjectorHelper::injectArrayPointer(
                builder,
                irArrayPointerType,
                type->getArrayNumElements(),
                arrayAllocation,
                irExpression->getSourceAllocation().value())->getValue();
    }
    auto arrayAccessAllocation = irInjectorMap->getInjector(irExpression->getSource()->getTypeSignature())->inject(irExpression->getSource(), builder, irInjectorMap, IR_OPERAND_OP, irModule);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), arrayAccessAllocation, { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    builder->get()->Insert(pointer);
    auto loadedPointerToIndexedElement = builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    return ArrayIRInjectorHelper::injectArrayCopy(builder, irArrayPointerType, irArrayPointerType->getElementIRType(), irModule, loadedPointerToIndexedElement, irExpression->getSourceAllocation().value())->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto elementIrType = ((IRArrayPointerType*)irExpression->getIRType()->getSourceType())->getElementIRType();
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto loadedPointerToIndexedElement = irInjectorMap->getInjector(irExpression->getSourceExpression()->getTypeSignature())->inject(irExpression->getSourceExpression(), builder, irInjectorMap, IR_OPERAND_OP, irModule);
    return ArrayIRInjectorHelper::injectArrayCopy(
            builder,
            arrayPointerType,
            elementIrType,
            irModule,
            loadedPointerToIndexedElement,
            irExpression->getSourceAllocation().value()
    )->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto arrayAccessAllocation = irInjectorMap->getInjector(irExpression->getSource()->getTypeSignature())->inject(irExpression->getSource(), builder, irInjectorMap, IR_OPERAND_OP, irModule);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), arrayAccessAllocation, { builder->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
    builder->get()->Insert(pointer);
    auto loadedPointerToIndexedElement = builder->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    return ArrayIRInjectorHelper::injectArrayCopy(builder, irArrayPointerType, irArrayPointerType->getElementIRType(), irModule, loadedPointerToIndexedElement, irExpression->getSourceAllocation().value())->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(std::string rawString, IRArrayPointerType* stringPointerType, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    auto stringAllocation = builder->get()->CreateAlloca(stringPointerType->getElementType(), rawString.size());
    auto sourceAllocation = IRInstructionNodeFactory::create(stringAllocation, IRPointerType::create(stringPointerType->getElementIRType()));
    auto arrayPointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(stringPointerType));
    arrayPointerAllocation->setParentAllocation(sourceAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(builder, stringPointerType, rawString.size(), sourceAllocation, arrayPointerAllocation)->getValue();
}