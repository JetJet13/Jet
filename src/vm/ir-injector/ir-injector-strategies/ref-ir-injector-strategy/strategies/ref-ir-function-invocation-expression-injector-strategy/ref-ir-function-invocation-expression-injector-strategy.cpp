//
// Created by Johny Georges on 2026-03-07.
//

#include "ref-ir-function-invocation-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-ref-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/function-invocation-ir-injector-helper/function-invocation-ir-injector-helper.h"

llvm::Value* RefIRFunctionInvocationExpressionInjectorStrategy::inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irRefType = (IRRefType*)irExpression->getIRType()->getSourceType();
    auto functionResult = FunctionInvocationIRInjectorHelper::inject((IRFunctionInvocationExpressionNode*)irExpression, irBlock, irInjector, irModule, scope, irOperation);
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), functionResult, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), functionResult, irRefType->getRefValueIndex());
        auto refValuePointer = InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), refValuePointer, irBlock);
    }
    return functionResult;
}