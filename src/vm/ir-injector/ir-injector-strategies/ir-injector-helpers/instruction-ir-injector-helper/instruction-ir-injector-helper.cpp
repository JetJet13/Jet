//
// Created by Johny Georges on 2025-03-24.
//

#include "instruction-ir-injector-helper.h"

llvm::Value* InstructionIRInjectorHelper::inject(IRInstructionNode* irInstruction, IRBlockNode* irBlock, std::string name) {
    for (auto ancestorValue : *irInstruction->getAncestorValues()) {
        irBlock->getBuilder()->get()->Insert(ancestorValue);
    }
    return irBlock->getBuilder()->get()->Insert(irInstruction->getValue(), name);
}