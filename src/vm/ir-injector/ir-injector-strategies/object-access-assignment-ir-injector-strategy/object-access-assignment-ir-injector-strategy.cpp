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
// Created by Johny Georges on 2025-08-30.
//

#include "object-access-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ObjectAccessAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRObjectAccessAssignmentStatementNode> irObjectAccessAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto objectAccess = irObjectAccessAssignmentStatement->getIRObjectAccessExpression();
    auto source = irInjector->inject(irBlock, objectAccess->getSource(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointerToTarget = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irObjectAccessAssignmentStatement->getIRObjectAccessExpression(), source);
    auto irExpressionValue = irInjector
            ->inject(
                irBlock,
                irObjectAccessAssignmentStatement->getIRExpression(),
                std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope
            );
    auto irType = irObjectAccessAssignmentStatement->getIRObjectAccessExpression()->getIRType()->getSourceType();
    if (irType->containsTypeThatRequiresFreeing()) {
        auto typeValue = irInjector->inject(irBlock, irType, irModule);
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irType->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getFreeValueFunction(),
                { pointerToTarget, loadedTypeValue }
        );
    }
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointerToTarget, irBlock);
}