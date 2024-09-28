//
// Created by Johny Georges on 2024-08-12.
//

#include "string-ir-injector-strategy.h"
#include "../../ir-injector-map.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

llvm::Value * StringIRInjectorStrategy::inject(IRExpressionNode *irExpression,
                                               std::unique_ptr<llvm::IRBuilder<>> *builder,
                                               IRInjectorMap *irInjectorMap,
                                               IROperationType irOperationType, IRModuleNode *irModule) {
    if (irExpression->is(IR_STRING_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRStringLiteralExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRAggregateIdentifierExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, builder, irInjectorMap, irOperationType, irModule);
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
    return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, builder)->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    if (irExpression->getSource()->getIRType()->getSourceType()->isEnumType()) {
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
                (IRArrayPointerType*)irExpression->getIRType(),
                type->getArrayNumElements(),
                arrayAllocation,
                irExpression->getSourceAllocation().value())->getValue();
    }
    auto loadedSourceAllocation = StructIRInjectorHelper::extractNestedStructAllocation(irExpression);
    return ArrayIRInjectorHelper::injectArrayPointer(
        builder,
        loadedSourceAllocation->getChildAllocationForKey(*irExpression->getTargetKey())
    )->getValue();
}

llvm::Value* StringIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IROperationType irOperationType, IRModuleNode *irModule) {
    // todo: create allocation 'alloc i8, i32 %loadedInt' and set as parent allocation to irExpression;
    auto elementIrType = ((IRArrayPointerType*)irExpression->getIRType()->getSourceType())->getElementIRType();
    auto indexValue = irInjectorMap->getInjector(irExpression->getIndexExpression()->getTypeSignature())->inject(irExpression->getIndexExpression(), builder, irInjectorMap, irOperationType, irModule);
    irExpression->getSourceExpression()->getValue()->print(llvm::outs());
    builder->get()->CreateCall(irModule->getArrayAccessFunction(), { indexValue, irExpression->getSourceExpression()->getValue() });
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto zeroIndex = builder->get()->getInt32(0);
    auto numElementsIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = builder->get()->getInt32(arrayPointerType->getPointerIndex());
    auto pointerToFirstElement = builder->get()->CreateInBoundsGEP(
        arrayPointerType->getType(),
        irExpression->getSourceExpression()->getValue(),
        { zeroIndex,  pointerIndex }
    );
    auto loadedPointerToFirstElement = builder->get()->CreateLoad(arrayPointerType->getPointerType(), pointerToFirstElement);
    auto pointerToIndexedElement = builder->get()->CreateInBoundsGEP(arrayPointerType->getPointerType(), loadedPointerToFirstElement, { indexValue });
    auto loadedPointerToIndexedElement = builder->get()->CreateLoad(arrayPointerType->getType(), pointerToIndexedElement);
    auto numElementsPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), loadedPointerToIndexedElement, { zeroIndex, numElementsIndex });
    auto loadedNumElements = builder->get()->CreateLoad(arrayPointerType->getNumElementsType(), numElementsPointer);
    auto destinationAllocation = builder->get()->CreateAlloca(elementIrType->getType(), loadedNumElements);
    irExpression->getSourceAllocation().value()->setParentAllocation(
        IRInstructionNodeFactory::create(
            destinationAllocation,
            IRPointerType::create(elementIrType)
        )
    );
    builder->get()->CreateCall(irModule->getCopyStringFunction(), { destinationAllocation, loadedPointerToIndexedElement });
    return ArrayIRInjectorHelper::injectArrayPointer(
        builder,
        arrayPointerType,
        loadedNumElements,
        irExpression->getSourceAllocation().value()
    )->getValue();
}