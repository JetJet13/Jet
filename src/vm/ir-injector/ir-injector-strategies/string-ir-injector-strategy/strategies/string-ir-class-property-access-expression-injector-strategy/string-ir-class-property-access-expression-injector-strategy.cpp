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
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRClassPropertyAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRClassPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irArrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irExpression->getIRType());
    auto pointerToPropertyValue = ClassPropertyAccessIRInjectorHelper::inject(
            irExpression,
            irBlock,
            irInjector,
            irModule,
            scope,
            (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying()
    );

    if (irOperation->isOperandPointer()) {
        return pointerToPropertyValue;
    } else if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getType(), pointerToPropertyValue, irBlock);
    }

    auto destinationAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyStringFunction(),
            {
                destinationAllocation,
                pointerToPropertyValue
            }
    );
    return InstructionIRInjectorHelper::injectLoad(destinationAllocation->getAllocatedType(), destinationAllocation, irBlock);
}