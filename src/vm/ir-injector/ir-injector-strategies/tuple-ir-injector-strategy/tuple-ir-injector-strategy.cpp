//
// Created by Johny Georges on 2024-08-15.
//

#include "tuple-ir-injector-strategy.h"
#include "../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"

llvm::Value* TupleIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_TUPLE_EXPRESSION_NODE)) {
        return this->inject((IRTupleExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_TUPLE_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRTupleAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE)) {
        return this->inject((IRFunctionParameterInvocationExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE)) {
        return this->inject((IRClassPropertyAccessExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
    throw std::logic_error("TupleIRInjectorStrategy - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* TupleIRInjectorStrategy::inject(IRTupleExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto tupleExpressionAllocation = irBlock->getBuilder()->get()->Insert(irExpression->getValue());
    auto numElements = irExpression->size();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irIndex = irBlock->getBuilder()->get()->getInt32(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getIRType()->getType(), tupleExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irInjector->inject(irBlock, irExpressionAtIndex, irOperationType, irModule, scope);
        irBlock->getBuilder()->get()->CreateStore(irExpressionValue, pointer);
    }
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), tupleExpressionAllocation);
}

llvm::Value* TupleIRInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperationType == IR_OPERAND_OP) {
        return irExpression->getValue();
    }
    return StructIRInjectorHelper::injectStructCopy(
        irBlock,
        (IRStructType*)irExpression->getIRType()->getSourceType(),
        irExpression->getValue(),
        irModule
    );
}

llvm::Value* TupleIRInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irStructType = (IRStructType*)irExpression->getIRType();
    if (irOperationType == IR_COPY_ASSIGNMENT_OP) {
        auto tupleAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_OP, irModule, scope);
        auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), tupleAllocation, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        irBlock->getBuilder()->get()->Insert(pointer);
        auto loadedPointerToIndexedElement = irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
        return StructIRInjectorHelper::injectStructCopy(irBlock, irStructType, loadedPointerToIndexedElement, irModule);
    } else {
        auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression, IR_OPERAND_OP, irModule, scope);
        auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSource()->getIRType()->getType(), loadedPointerToIndexedElement, { irBlock->getBuilder()->get()->getInt32(0), irExpression->getIRTargetKeyIndex() });
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), pointerToIndexedElement);
    }
}

llvm::Value* TupleIRInjectorStrategy::inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope);
}

llvm::Value* TupleIRInjectorStrategy::inject(IRFunctionParameterInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return FunctionInvocationIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope);
}

llvm::Value* TupleIRInjectorStrategy::inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getTargetIRType()->getType());
    auto loadedStruct = ClassPropertyAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope);
    irBlock->getBuilder()->get()->CreateStore(loadedStruct, allocation);
    return allocation;
}