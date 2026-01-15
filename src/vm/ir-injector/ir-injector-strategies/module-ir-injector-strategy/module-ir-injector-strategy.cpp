//
// Created by Johny Georges on 2024-10-31.
//

#include "module-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ModuleIRInjectorStrategy::inject(IRModuleDeclarationNode* irModuleDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    InstructionIRInjectorHelper::inject(irModuleDeclaration->getAllocation(), irBlock);
    auto numElements = irModuleDeclaration->getExports()->size();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    for (unsigned long i = 0; i < numElements; ++i) {
        auto exportAtIndex = irModuleDeclaration->getExports()->at(i);
        auto irIndex = irBlock->getBuilder()->get()->getInt64(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irModuleDeclaration->getIRType()->getType(), irModuleDeclaration->getAllocation()->getValue(), { zeroIndex, irIndex });
        InstructionIRInjectorHelper::injectStore(exportAtIndex->getValue(), pointer, irBlock);
//        irBlock->getBuilder()->get()->CreateStore(exportAtIndex->getValue(), pointer);
    }
}