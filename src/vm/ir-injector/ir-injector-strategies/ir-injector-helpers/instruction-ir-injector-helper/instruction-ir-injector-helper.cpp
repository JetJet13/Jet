//
// Created by Johny Georges on 2025-03-24.
//

#include "instruction-ir-injector-helper.h"

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
        return irBlock->getBuilder()->get()->CreateLoad(
                irInstruction->getIRType()->getSourceType()->getSourceType()->getType(),
                loadedPointer
        );
    }
    return irBlock->getBuilder()->get()->CreateLoad(irInstruction->getAllocatedType(), irInstruction->getValue());
}

llvm::Value* InstructionIRInjectorHelper::injectLoad(IRPointerType* irPointerType, llvm::Value* sourcePointer, IRBlockNode* irBlock, std::string name) {
    auto loadedPointer = irBlock->getBuilder()->get()->CreateLoad(irPointerType->getType(), sourcePointer);
    return irBlock->getBuilder()->get()->CreateLoad(
            irPointerType->getSourceType()->getType(),
            loadedPointer
    );
}