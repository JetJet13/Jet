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
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-shared-value-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-type/ir-shared-ptr-type.h"

void ArrayAccessSharedValueAssignmentIRInjectorStrategy::inject(std::shared_ptr<IRArrayAccessSharedValueAssignmentStatementNode> irArrayAccessSharedValueAssignmentStatement, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto pointerToIndexedElement = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irArrayAccessSharedValueAssignmentStatement->getIRArrayAccessExpression(), irModule, irInjector, scope);
    auto newValue = irInjector->inject(
            irBlock,
            irArrayAccessSharedValueAssignmentStatement->getIRExpression(),
            std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    auto irType = irArrayAccessSharedValueAssignmentStatement->getIRExpression()->getUnderlyingIRType();
    auto newValueMalloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(irType->getSizeInBytes())
            }
    );
    InstructionIRInjectorHelper::injectStore(newValue, newValueMalloc, irBlock, irType);
    auto irSharedPtrType = std::dynamic_pointer_cast<IRSharedPtrType>(irArrayAccessSharedValueAssignmentStatement->getIRArrayAccessExpression()->getIRType()->getSourceType());
    auto typeValue = irInjector->inject(irBlock, irSharedPtrType->getUnderlyingType(), irModule);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetSharedValueFunction(),
            { pointerToIndexedElement, newValueMalloc,  loadedTypeValue }
    );
}