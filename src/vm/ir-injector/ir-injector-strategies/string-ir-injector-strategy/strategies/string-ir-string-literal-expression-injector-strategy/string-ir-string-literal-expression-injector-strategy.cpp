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

#include "string-ir-string-literal-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRStringLiteralExpressionInjectorStrategy::inject(std::shared_ptr<IRStringLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irArrayPointerType = irExpression->getIRArrayPointerType();
    auto arrayAllocation = irExpression->getSourceAggregateAllocation()->getValue();
    InstructionIRInjectorHelper::inject(irExpression->getSourceAggregateAllocation(), irBlock);
    InstructionIRInjectorHelper::injectStore(irExpression->getValue(), arrayAllocation, irBlock, irExpression->getSourceAggregateAllocation()->getIRType()->getUnderlyingType());
    auto array = ArrayIRInjectorHelper::injectArrayPointer(irBlock, irArrayPointerType, irExpression->getValue()->getType()->getArrayNumElements(),
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation());
    if (irOperation->isOperandPointer()) {
        return irExpression->getAggregatePointerAllocation()->getValue();
    }

    if (irOperation->isFunctionArgument()) {
        auto functionArgumentAllocation = irBlock->getBuilder()->get()->CreateAlloca(irArrayPointerType->getType());
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { functionArgumentAllocation, irExpression->getAggregatePointerAllocation()->getValue() });
        return irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getType(), functionArgumentAllocation);
    }
    return array;
}