//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-string-literal-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRStringLiteralExpressionInjectorStrategy::inject(IRStringLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = irExpression->getIRType();
    auto arrayAllocation = irExpression->getSourceAggregateAllocation()->getValue();
    InstructionIRInjectorHelper::inject(irExpression->getSourceAggregateAllocation(), irBlock);
    InstructionIRInjectorHelper::injectStore(irExpression->getValue(), arrayAllocation, irBlock, irExpression->getSourceAggregateAllocation()->getIRType()->getUnderlyingType());
    auto array = ArrayIRInjectorHelper::injectArrayPointer(irBlock, irArrayPointerType, irExpression->getValue()->getType()->getArrayNumElements(),
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
    if (irOperation->isOperandPointer()) {
        return irExpression->getAggregatePointerAllocation()->getValue();
    }

    if (irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        auto functionArgumentAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { functionArgumentAllocation, irExpression->getAggregatePointerAllocation()->getValue() });
        return irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getType(), functionArgumentAllocation);
    }
    return array;
}