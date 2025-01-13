//
// Created by Johny Georges on 2024-10-31.
//

#include "module-ir-injector-strategy.h"

void ModuleIRInjectorStrategy::inject(IRModuleDeclarationNode* irModuleDeclaration, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    irBlock->getBuilder()->get()->Insert(irModuleDeclaration->getAllocation()->getValue());
    auto numElements = irModuleDeclaration->getExports()->size();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto exportAtIndex = irModuleDeclaration->getExports()->at(i);
        auto irIndex = irBlock->getBuilder()->get()->getInt32(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irModuleDeclaration->getIRType()->getType(), irModuleDeclaration->getAllocation()->getValue(), { zeroIndex, irIndex });
        irBlock->getBuilder()->get()->CreateStore(exportAtIndex->getValue(), pointer);
    }
}