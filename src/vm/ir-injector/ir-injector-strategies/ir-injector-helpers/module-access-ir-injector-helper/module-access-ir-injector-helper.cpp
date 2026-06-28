//
// Created by Johny Georges on 2026-03-27.
//

#include "module-access-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"


llvm::Value* ModuleAccessIRInjectorHelper::inject(IRModuleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {
    if (irOperation->isOperandPointer()) {
        return irExpression->getValue();
    }

    if (irOperation->isCopy() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        auto irType = irExpression->getIRType()->getSourceType();
        auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irType->getType());
        auto typeValue = irInjector->inject(irBlock, irType, irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getCopyValueFunction(),
                { allocation, irExpression->getValue(), loadedTypeValue }
        );
        return InstructionIRInjectorHelper::injectLoad(irType->getType(), allocation, irBlock);
    }

    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), irExpression->getValue(), irBlock, irExpression->getIRType()->getSourceType());
}