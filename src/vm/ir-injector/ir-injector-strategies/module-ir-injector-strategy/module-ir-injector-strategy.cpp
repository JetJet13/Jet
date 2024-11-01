//
// Created by Johny Georges on 2024-10-31.
//

#include "module-ir-injector-strategy.h"
#include "../../ir-injector-map.h"

void ModuleIRInjectorStrategy::inject(IRModuleDeclarationNode* irModuleDeclaration, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode* irModule) {
    builder->get()->Insert(irModuleDeclaration->getAllocation()->getValue());
    auto numElements = irModuleDeclaration->getExports()->size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto exportAtIndex = irModuleDeclaration->getExports()->at(i);
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(irModuleDeclaration->getIRType()->getType(), irModuleDeclaration->getAllocation()->getValue(), { zeroIndex, irIndex });
        builder->get()->CreateStore(exportAtIndex->getValue(), pointer);
    }
}