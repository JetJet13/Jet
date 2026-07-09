//
// Created by Johny Georges on 2025-03-08.
//

#include "array-ir-array-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ArrayIRArrayExpressionInjectorStrategy::inject(std::shared_ptr<IRArrayExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    InstructionIRInjectorHelper::inject(irExpression->getSourceAggregateAllocation(), irBlock);
    auto numElements = irExpression->size();
    for (unsigned long i = 0; i < numElements; ++i) {
        auto elementExpression = irExpression->getValues()->at(i);
        auto irIndex = irBlock->getBuilder()->get()->getInt64(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getIRArrayPointerType()->getElementType(),
                                                                       irExpression->getSourceAggregateAllocation()->getValue(), { irIndex });
        auto irExpressionValue = irInjector->inject(irBlock, elementExpression, std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, scope);
        InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, elementExpression->getIRType());
    }

    auto loadedArray = ArrayIRInjectorHelper::injectArrayPointer(irBlock, irExpression->getIRArrayPointerType(), numElements,
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
    if (irOperation->isOperandPointer()) {
        return irExpression->getAggregatePointerAllocation()->getValue();
    }

    if (irOperation->isFunctionArgument()) {
        auto irArrayPointerType = irExpression->getIRType();
        auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
        auto typeValue = irInjector->inject(irBlock, irArrayPointerType, irModule);
        auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyArrayFunction(), { destinationPointerAllocation, irExpression->getAggregatePointerAllocation()->getValue(), loadedTypeValue });
        return irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getType(), destinationPointerAllocation);
    }
    return loadedArray;
}