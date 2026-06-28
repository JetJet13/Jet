//
// Created by Johny Georges on 2026-06-27.
//

#include "ref-ir-module-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/module-access-ir-injector-helper/module-access-ir-injector-helper.h"
#include "../../../../../ir-type/ir-ref-type.h"

// TODO - refactor this injector strategy
llvm::Value* RefIRModuleAccessExpressionInjectorStrategy::inject(IRModuleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* RefIRModuleAccessExpressionInjectorStrategy::injectCopy(IRModuleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    return ModuleAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, irOperation);
}

llvm::Value* RefIRModuleAccessExpressionInjectorStrategy::injectOperand(IRModuleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irRefType = (IRRefType*)irExpression->getIRType()->getSourceType();
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), irExpression->getValue(), irRefType->getRefValueIndex(), "NAGA");
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
    }

    if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto refValue = InstructionIRInjectorHelper::injectLoad(irRefType->getType(), irExpression->getValue(), irBlock);
        auto underlyingValuePointer = irBlock->getBuilder()->get()->CreateExtractValue(refValue, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), underlyingValuePointer, irBlock, irRefType->getRefValueIRType());
    }
    return ModuleAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, irOperation);
}