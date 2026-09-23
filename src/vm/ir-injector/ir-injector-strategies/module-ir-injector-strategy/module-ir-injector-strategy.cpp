//
// Created by Johny Georges on 2024-10-31.
//

#include "module-ir-injector-strategy.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ModuleIRInjectorStrategy::inject(std::shared_ptr<IRModuleDeclarationNode> irModuleDeclaration, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    InstructionIRInjectorHelper::inject(irModuleDeclaration->getAllocation(), irBlock);
    auto numElements = irModuleDeclaration->getExports()->size();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    for (uint64_t i = 0; i < numElements; ++i) {
        auto exportAtIndex = irModuleDeclaration->getExports()->at(i);
        auto irIndex = irBlock->getBuilder()->get()->getInt64(i);
        auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irModuleDeclaration->getIRType()->getType(), irModuleDeclaration->getAllocation()->getValue(), { zeroIndex, irIndex });
        InstructionIRInjectorHelper::injectStore(exportAtIndex->getValue(), pointer, irBlock);
    }
}