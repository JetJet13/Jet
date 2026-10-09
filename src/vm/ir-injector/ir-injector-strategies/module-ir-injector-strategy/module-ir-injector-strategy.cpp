// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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