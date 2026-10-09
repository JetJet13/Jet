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

#include "literal-ir-binary-comparison-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

llvm::Value* LiteralIRBinaryComparisonExpressionInjectorStrategy::inject(std::shared_ptr<IRBinaryComparisonExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irExpression->isPredicateEqual() || irExpression->isPredicateNotEqual()) {
        auto leftIrTypeValue = irInjector->inject(irBlock, irExpression->getLeftIrType(), irModule);
        auto loadedLeftIrTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getLeftIrType()->getValue()->getAllocatedType(), leftIrTypeValue, irBlock);
        auto rightIrTypeValue = irInjector->inject(irBlock, irExpression->getRightIrType(), irModule);
        auto loadedRightIrTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getRightIrType()->getValue()->getAllocatedType(), rightIrTypeValue, irBlock);
        auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, scope);
        auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, scope);
        auto result = irBlock->getBuilder()->get()->CreateCall(irModule->getEqualValueFunction(), { irLeftNodeValue, irRightNodeValue, loadedLeftIrTypeValue, loadedRightIrTypeValue });
        return irExpression->isPredicateEqual()
        ? result
        : irBlock->getBuilder()->get()->CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ, result, irBlock->getBuilder()->get()->getFalse());
    }

    auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), (std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
    auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), (std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
    return irBlock->getBuilder()->get()->CreateCmp(irExpression->getValue()->getPredicate(), irLeftNodeValue, irRightNodeValue);
}