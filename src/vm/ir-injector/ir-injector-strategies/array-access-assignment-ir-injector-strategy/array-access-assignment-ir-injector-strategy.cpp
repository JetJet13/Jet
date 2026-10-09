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
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

void ArrayAccessAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRArrayAccessAssignmentStatementNode> irArrayAccessAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerToIndexedElement = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irArrayAccessAssignmentStatement->getIRArrayAccessExpression(), irModule, irInjector, scope);
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irArrayAccessAssignmentStatement->getIRExpression(),
                    std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope
            );

    auto irType = irArrayAccessAssignmentStatement->getIRArrayAccessExpression()->getIRType()->getSourceType();
    if (irType->containsTypeThatRequiresFreeing()) {
        auto typeValue = irInjector->inject(irBlock, irType, irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction(),
                { pointerToIndexedElement, loadedTypeValue }
        );
    }

    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointerToIndexedElement, irBlock, irArrayAccessAssignmentStatement->getIRExpression()->getIRType());
}