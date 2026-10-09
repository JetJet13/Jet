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

#include "tuple-ir-tuple-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* TupleIRTupleExpressionInjectorStrategy::inject(std::shared_ptr<IRTupleExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto tupleRefAllocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto tupleAllocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue()->getParentAllocation().value(), irBlock);
    auto numElements = irExpression->size();
    for (uint64_t i = 0; i < numElements; ++i) {
        auto irExpressionAtIndex = irExpression->getValues()->at(i);
        auto irTypeAtIndex = irExpression->getIRStructRefType()->getStructIRType()->getIRTypeByIndex(i);
        auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRStructRefType()->getStructIRType()->getType(), tupleAllocation, i);
        auto irExpressionValue = irInjector->inject(irBlock, irExpressionAtIndex, std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP), irModule, scope);
        InstructionIRInjectorHelper::injectStore(irExpressionValue, pointer, irBlock, irTypeAtIndex);
    }

    auto pointerToTuplePointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRStructRefType()->getType(), tupleRefAllocation, irExpression->getIRStructRefType()->getStructIndex());
    InstructionIRInjectorHelper::injectStore(tupleAllocation, pointerToTuplePointer, irBlock);
    auto pointerToCounterPointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getIRStructRefType()->getType(), tupleRefAllocation, irExpression->getIRStructRefType()->getCounterIndex());
    auto arc = InstructionIRInjectorHelper::inject(irExpression->getArc().value(), irBlock);
    InstructionIRInjectorHelper::injectStore(arc, pointerToCounterPointer, irBlock);

    if (irOperation->isOperandPointer()) {
        return tupleRefAllocation;
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRStructRefType()->getType(), tupleRefAllocation, irBlock, irExpression->getIRStructRefType());
}