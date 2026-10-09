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
// Created by Johny Georges on 2026-03-27.
//

#include "module-access-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"


llvm::Value* ModuleAccessIRInjectorHelper::inject(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation) {
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

    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock, irExpression->getIRType()->getSourceType());
}