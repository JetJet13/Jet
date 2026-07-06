//
// Created by Johny Georges on 2025-01-11.
//

#include "procedure-declaration-ir-injector-strategy.h"
#include "../ir-injector-helpers/free-variables-ir-injector-helper/free-variables-ir-injector-helper.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../ir-type/ir-invocable-type.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ProcedureDeclarationIRInjectorStrategy::inject(std::shared_ptr<IRProcedureDeclarationNode> irProcedureDeclaration, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    irInjector->inject(irBlock, irProcedureDeclaration->getBlock(), irModule);
    if (!irProcedureDeclaration->getBlock()->hasReturnStatement()) {
        irProcedureDeclaration->getBlock()->getLastChildOrSelf()->addVoidReturn();
    }

    auto irType = std::dynamic_pointer_cast<IRInvocableType>(irProcedureDeclaration->getGlobalVariable()->getIRType()->getSourceType());
    auto functionIndex = irType->getFunctionIndex();
    auto functionPointer = irBlock->getBuilder()->get()->CreateStructGEP(irType->getType(), irProcedureDeclaration->getGlobalVariable()->getValue(), functionIndex);
    InstructionIRInjectorHelper::injectStore(irProcedureDeclaration->getValue(), functionPointer, irBlock, irType);
    auto refCounterIndex = irType->getFunctionRefCounterIndex();
    auto refCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irType->getType(), irProcedureDeclaration->getGlobalVariable()->getValue(), refCounterIndex);
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

    auto isPerpetualPointer = irBlock->getBuilder()->get()->CreateStructGEP(irType->getType(), irProcedureDeclaration->getGlobalVariable()->getValue(), irType->getIsPerpetualIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getTrue(), isPerpetualPointer, irBlock);

    FreeIRInjectorHelper::freeFunctionBlockNodes(irProcedureDeclaration->getBlock(), irInjector, irModule, irProcedureDeclaration->getBlock()->getScope());
    FreeIRInjectorHelper::freeFunctionParameters(irProcedureDeclaration->getBlock(), irProcedureDeclaration->getParameters(), irInjector, irModule, irProcedureDeclaration->getBlock()->getScope());
    DebugIRInjectorHelper::injectFunctionEnterLog(irProcedureDeclaration->getBlock(), irProcedureDeclaration->getName(), irInjector, irModule);
    DebugIRInjectorHelper::injectFunctionExitLog(irProcedureDeclaration->getBlock(), irProcedureDeclaration->getName(), irInjector, irModule);
}