//
// Created by Johny Georges on 2025-03-24.
//

#include "instruction-ir-injector-helper.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

llvm::Value* InstructionIRInjectorHelper::inject(IRInstructionNode* irInstruction, IRBlockNode* irBlock, std::string name) {
    for (auto ancestorValue : *irInstruction->getAncestorValues()) {
        irBlock->getBuilder()->get()->Insert(ancestorValue);
    }

    auto value = irBlock->getBuilder()->get()->Insert(irInstruction->getValue(), name);

    for (auto descendentValue : *irInstruction->getDescendentValues()) {
        irBlock->getBuilder()->get()->Insert(descendentValue);
    }

    return value;
}

llvm::Value* InstructionIRInjectorHelper::injectLoad(IRInstructionNode* irInstruction, IRBlockNode* irBlock, std::string name) {
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

llvm::Value* InstructionIRInjectorHelper::injectLoad(IRPointerType* irPointerType, llvm::Value* sourcePointer, IRBlockNode* irBlock, std::string name) {
    auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irPointerType->getType(), sourcePointer);
    auto loadedValue = irBlock->getBuilder()->get()->CreateLoad(
            irPointerType->getSourceType()->getType(),
            loadedPointer,
            name
    );
    loadedValue->setAlignment(irPointerType->getSourceType()->getAlignment());
    return loadedValue;
}

llvm::LoadInst* InstructionIRInjectorHelper::injectLoad(llvm::Type* type, llvm::Value* source, IRBlockNode* irBlock, std::optional<IRType*> irType, std::string name) {
    auto loadInstruction = irBlock->getBuilder()->get()->CreateLoad(type, source, name);
    if (irType && irType.value()->isPointerType()) {
        loadInstruction->setAlignment(irType.value()->getSourceType()->getAlignment());
    } else if (irType) {
        loadInstruction->setAlignment(irType.value()->getAlignment());
    }
    return loadInstruction;
}

llvm::StoreInst* InstructionIRInjectorHelper::injectStore(llvm::Value* value, llvm::Value* source, IRBlockNode* irBlock, std::optional<IRType*> irType) {
    auto storeInstruction = irBlock->getBuilder()->get()->CreateStore(value, source);
    if (irType && irType.value()->isPointerType()) {
        storeInstruction->setAlignment(irType.value()->getSourceType()->getAlignment());
    } else if (irType) {
        storeInstruction->setAlignment(irType.value()->getAlignment());
    }
    return storeInstruction;
}
