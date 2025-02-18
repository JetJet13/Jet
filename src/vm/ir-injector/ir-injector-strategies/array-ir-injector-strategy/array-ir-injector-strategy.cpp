//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector-strategy.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"

llvm::Value* ArrayIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector *irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_ARRAY_EXPRESSION_NODE)) {
        return this->inject((IRArrayExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRAggregateIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRObjectAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_ARRAY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRArrayAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRTupleAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionParameterInvocationExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
    throw std::logic_error("ArrayIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRArrayExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    irBlock->getBuilder()->get()->Insert(irExpression->getSourceAggregateAllocation()->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto elementExpression = irExpression->getValues()->at(i);
        auto irIndex = irBlock->getBuilder()->get()->getInt32(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceAggregateAllocation()->getAllocatedType(),
                                                         irExpression->getSourceAggregateAllocation()->getValue(), { zeroIndex, irIndex });
        auto irExpressionValue = irInjector->inject(irBlock, elementExpression, irOperationType, irModule, scope);
        irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointer);
    }

    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, irExpression->getIRType(), numElements,
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRAggregateIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(irExpression, irBlock, irModule)->getValue();
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    if (irExpression->getSource()->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        auto arrayAllocation = irExpression->getSourceAllocation().value()->getParentAllocation().value();
        irBlock->getBuilder()->get()->Insert(arrayAllocation->getValue());
        auto type = irExpression->getSource()->getIRType()->getSourceType()->getType()->getStructElementType(irExpression->getTargetKeyIndex());
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(
                irExpression->getSource()->getType(),
                irExpression->getSource()->getValue(),
                { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() }
        );
        irBlock->getBuilder()->get()->Insert(pointer);
        auto loaded = irBlock->getBuilder()->get()->CreateLoad(type, pointer);
        irBlock->getBuilder()->get()->CreateStore(loaded, arrayAllocation->getValue());
        return ArrayIRInjectorHelper::injectArrayPointer(
                irBlock,
                irArrayPointerType,
                type->getArrayNumElements(),
                arrayAllocation,
                irExpression->getSourceAllocation().value())->getValue();
    } else if (irOperationType == IR_COPY_ASSIGNMENT_OP) {
        auto arrayAccessAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_OP, irModule, scope);
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), arrayAccessAllocation, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        irBlock->getBuilder()->get()->Insert(pointer);
        auto loadedPointerToIndexedElement = irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
        return ArrayIRInjectorHelper::injectArrayCopy(irBlock, irArrayPointerType, irArrayPointerType->getElementIRType(), irModule, loadedPointerToIndexedElement, irExpression->getSourceAllocation().value())->getValue();
    } else {
        auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_OP, irModule, scope);
        auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSource()->getIRType()->getType(), loadedPointerToIndexedElement, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), pointerToIndexedElement);
    }
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_OP, irModule, scope);
    if (irOperationType == IR_COPY_ASSIGNMENT_OP) {
        return ArrayIRInjectorHelper::injectArrayCopy(
                irBlock,
                (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType(),
                ((IRArrayPointerType*)irExpression->getIRType()->getSourceType())->getElementIRType(),
                irModule,
                loadedPointerToIndexedElement,
                irExpression->getSourceAllocation().value()
        )->getValue();
    }

    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_OP, irModule, scope);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceExpression()->getIRType()->getType(), loadedPointerToIndexedElement, { indexValue });
    if (irOperationType == IR_ASSIGNMENT_OP) {
        return pointerToIndexedElement;
    } else if (irOperationType == IR_OPERAND_OP) {
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), pointerToIndexedElement);
    }
    throw std::logic_error("ArrayIRInjectorStrategy not implemented for IRArrayAccessExpressionNode + irOperationType");
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    if (irOperationType == IR_COPY_ASSIGNMENT_OP) {
        auto arrayAccessAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_OP, irModule, scope);
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), arrayAccessAllocation, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        irBlock->getBuilder()->get()->Insert(pointer);
        auto loadedPointerToIndexedElement = irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
        return ArrayIRInjectorHelper::injectArrayCopy(irBlock, irArrayPointerType, irArrayPointerType->getElementIRType(), irModule, loadedPointerToIndexedElement, irExpression->getSourceAllocation().value())->getValue();
    } else {
        auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_OP, irModule, scope);
        auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSource()->getIRType()->getType(), loadedPointerToIndexedElement, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), pointerToIndexedElement);
    }
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope);
}

llvm::Value* ArrayIRInjectorStrategy::inject(IRFunctionParameterInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope);
}