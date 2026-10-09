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

#include "shared-ptr-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"

void SharedPtrIRInjectorHelper::incrementSharedPtrCountForInvocationExpression(llvm::Value* value, std::shared_ptr<IRType> irType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule) {
    if (irOperation->isFunctionArgument()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { value });
    }
}

llvm::Value* SharedPtrIRInjectorHelper::injectForInvocationExpression(llvm::Value* value, std::shared_ptr<IRSharedPtrType> irSharedPtrType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IROperation> irOperation) {
    // value is expected to be a ptr
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), value, irSharedPtrType->getSharedValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), pointerToRefValue, irBlock);
    } else if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), value, irSharedPtrType->getSharedValueIndex());
        auto refValuePointer = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), pointerToRefValue, irBlock);
        return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueIRType()->getType(), refValuePointer, irBlock);
    } else if (irOperation->isOperandPointer()) {
        return value;
    }
    return InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getType(), value, irBlock);
}