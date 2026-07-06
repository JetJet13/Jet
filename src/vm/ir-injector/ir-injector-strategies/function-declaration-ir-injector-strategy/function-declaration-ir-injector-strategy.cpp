//
// Created by Johny Georges on 2025-01-11.
//

#include "function-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-invocable-type.h"

void FunctionDeclarationIRInjectorStrategy::inject(std::shared_ptr<IRFunctionDeclarationNode> irFunctionDeclaration, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    irInjector->inject(irBlock, irFunctionDeclaration->getBlock(), irModule);

    auto irType = std::dynamic_pointer_cast<IRInvocableType>(irFunctionDeclaration->getGlobalVariable()->getIRType()->getSourceType());
    auto functionPointer = irBlock->getBuilder()->get()->CreateStructGEP(irType->getType(), irFunctionDeclaration->getGlobalVariable()->getValue(), irType->getFunctionIndex());
    InstructionIRInjectorHelper::injectStore(irFunctionDeclaration->getValue(), functionPointer, irBlock, irType);
    auto refCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irType->getType(), irFunctionDeclaration->getGlobalVariable()->getValue(), irType->getFunctionRefCounterIndex());
    auto refCounterAlloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(irType->getRefCounterSizeInBytes()),
            }
    );
    auto refCounterValue = irBlock->getBuilder()->get()->getInt64(1);
    InstructionIRInjectorHelper::injectStore(refCounterValue, refCounterAlloc, irBlock);
    InstructionIRInjectorHelper::injectStore(refCounterAlloc, refCounterPointer, irBlock);

    auto isPerpetualPointer = irBlock->getBuilder()->get()->CreateStructGEP(irType->getType(), irFunctionDeclaration->getGlobalVariable()->getValue(), irType->getIsPerpetualIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getTrue(), isPerpetualPointer, irBlock);

    FreeIRInjectorHelper::freeFunctionBlockNodes(irFunctionDeclaration->getBlock(), irInjector, irModule, irFunctionDeclaration->getBlock()->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irFunctionDeclaration->getBlock(), irFunctionDeclaration->getParameters(), irInjector, irModule, irFunctionDeclaration->getBlock()->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irFunctionDeclaration->getBlock(), irFunctionDeclaration->getName(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irFunctionDeclaration->getBlock(), irFunctionDeclaration->getName(), irInjector, irModule);
}