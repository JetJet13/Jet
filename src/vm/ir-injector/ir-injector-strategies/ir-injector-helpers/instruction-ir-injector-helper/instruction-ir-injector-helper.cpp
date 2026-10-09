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
// Created by Johny Georges on 2025-03-24.
//

#include "instruction-ir-injector-helper.h"

llvm::Value* InstructionIRInjectorHelper::inject(std::shared_ptr<IRTypeValueInstructionNode> irTypeValueInstructionNode, std::shared_ptr<IRBlockNode> irBlock, std::string name) {
    auto value = irBlock->getBuilder()->get()->Insert(irTypeValueInstructionNode->getValue(), name);
    irBlock->getBuilder()->get()->Insert(irTypeValueInstructionNode->getInitialValueStoreInstruction());
    return value;
}

llvm::Value* InstructionIRInjectorHelper::inject(std::shared_ptr<IRInstructionNode> irInstruction, std::shared_ptr<IRBlockNode> irBlock, std::string name) {
    if (irInstruction->isInserted()) {
        return irInstruction->getValue();
    }

    for (auto ancestorValue : *irInstruction->getAncestorValues()) {
        irBlock->getBuilder()->get()->Insert(ancestorValue);
    }

    auto value = irBlock->getBuilder()->get()->Insert(irInstruction->getValue(), name);

    for (auto descendentValue : *irInstruction->getDescendentValues()) {
        irBlock->getBuilder()->get()->Insert(descendentValue);
    }

    return value;
}

llvm::Value* InstructionIRInjectorHelper::injectLoad(std::shared_ptr<IRInstructionNode> irInstruction, std::shared_ptr<IRBlockNode> irBlock, std::string name) {
    if (irInstruction->getIRType()->getSourceType()->isPointerType()) {
        auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irInstruction->getAllocatedType(), irInstruction->getValue());
        auto loadedValue = irBlock->getBuilder()->get()->CreateLoad(
                irInstruction->getIRType()->getUnderlyingType()->getType(),
                loadedPointer
        );
        loadedValue->setAlignment(irInstruction->getIRType()->getUnderlyingType()->getAlignment());
        return loadedValue;
    }
    auto loadedValue = irBlock->getBuilder()->get()->CreateLoad(irInstruction->getAllocatedType(), irInstruction->getValue());
    loadedValue->setAlignment(irInstruction->getIRType()->getUnderlyingType()->getAlignment());
    return loadedValue;
}

llvm::Value* InstructionIRInjectorHelper::injectLoad(std::shared_ptr<IRPointerType> irPointerType, llvm::Value* sourcePointer, std::shared_ptr<IRBlockNode> irBlock, std::string name) {
    auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irPointerType->getType(), sourcePointer);
    auto loadedValue = irBlock->getBuilder()->get()->CreateLoad(
            irPointerType->getSourceType()->getType(),
            loadedPointer,
            name
    );
    loadedValue->setAlignment(irPointerType->getSourceType()->getAlignment());
    return loadedValue;
}

llvm::LoadInst* InstructionIRInjectorHelper::injectLoad(llvm::Type* type, llvm::Value* source, std::shared_ptr<IRBlockNode> irBlock, std::optional<std::shared_ptr<IRType>> irType, std::string name) {
    auto loadInstruction = irBlock->getBuilder()->get()->CreateLoad(type, source, name);
    if (irType && irType.value()->isPointerType()) {
        loadInstruction->setAlignment(irType.value()->getSourceType()->getAlignment());
    } else if (irType) {
        loadInstruction->setAlignment(irType.value()->getAlignment());
    }
    return loadInstruction;
}

llvm::StoreInst* InstructionIRInjectorHelper::injectStore(llvm::Value* value, llvm::Value* source, std::shared_ptr<IRBlockNode> irBlock, std::optional<std::shared_ptr<IRType>> irType) {
    auto storeInstruction = irBlock->getBuilder()->get()->CreateStore(value, source);
    if (irType && irType.value()->isPointerType()) {
        storeInstruction->setAlignment(irType.value()->getSourceType()->getAlignment());
    } else if (irType) {
        storeInstruction->setAlignment(irType.value()->getAlignment());
    }
    return storeInstruction;
}
