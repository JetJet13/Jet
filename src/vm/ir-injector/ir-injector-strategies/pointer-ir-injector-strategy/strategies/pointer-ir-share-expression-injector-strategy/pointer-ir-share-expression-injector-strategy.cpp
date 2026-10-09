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
// Created by Johny Georges on 2026-07-13.
//

#include "pointer-ir-share-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* PointerIRShareExpressionInjectorStrategy::inject(std::shared_ptr<IRShareExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irExpression->getExpression()->isOneOf({ IR_OBJECT_ACCESS_EXPRESSION_NODE, IR_TUPLE_ACCESS_EXPRESSION_NODE })) {
        auto value = irInjector->inject(irBlock, irExpression->getExpression(), irOperation, irModule, scope);
        auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
        auto pointerBitCast = irBlock->getBuilder()->get()->CreateBitCast(value, irExpression->getIRType()->getType()->getPointerTo());
        InstructionIRInjectorHelper::injectStore(pointerBitCast, allocation, irBlock);
        return allocation;
    } else if (irExpression->getExpression()->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
        auto pointerBitCast = irBlock->getBuilder()->get()->CreateBitCast(irExpression->getExpression()->getValue(), irExpression->getIRType()->getType()->getPointerTo());
        InstructionIRInjectorHelper::injectStore(pointerBitCast, allocation, irBlock);
        return allocation;
    }
    auto value = this->injectRawValue(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    auto pointerBitCast = irBlock->getBuilder()->get()->CreateBitCast(value, irExpression->getIRType()->getType()->getPointerTo());
    InstructionIRInjectorHelper::injectStore(pointerBitCast, allocation, irBlock);
    return allocation;
}

llvm::Value* PointerIRShareExpressionInjectorStrategy::injectRawValue(std::shared_ptr<IRShareExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto rawValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperation, irModule, scope);
    if (irOperation->isRefGlobalAssignment()) {
        auto globalVariable = new llvm::GlobalVariable(
                irExpression->getUnderlyingIRType()->getType(),
                false,
                llvm::GlobalValue::InternalLinkage
        );
        irModule->getModule()->get()->insertGlobalVariable(globalVariable);
        InstructionIRInjectorHelper::injectStore(rawValue, globalVariable, irBlock, irExpression->getIRSharedPtrType()->getSharedValueIRType());
        return globalVariable;
    }

    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getExpression()->getType());
    InstructionIRInjectorHelper::injectStore(rawValue, allocation, irBlock, irExpression->getIRSharedPtrType()->getSharedValueIRType());
    return allocation;
}