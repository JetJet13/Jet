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
// Created by Johny Georges on 2026-03-16.
//

#include "class-static-property-assignment-ir-injector-strategy.h"
#include "../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void ClassStaticPropertyAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRClassStaticPropertyAssignmentStatementNode> irClassStaticPropertyAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerToTarget = ClassPropertyAccessIRInjectorHelper::inject(irClassStaticPropertyAssignmentStatement->getIRClassStaticPropertyAccessExpressionNode(),irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irClassStaticPropertyAssignmentStatement->getIRExpression(),
                    std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope
            );
    InstructionIRInjectorHelper::injectStore(irExpressionValue, pointerToTarget, irBlock);
}