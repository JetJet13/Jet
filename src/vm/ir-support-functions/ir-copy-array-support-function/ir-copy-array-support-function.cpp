//
// Created by Johny Georges on 2024-08-07.
//

#include "ir-copy-array-support-function.h"

void IRCopyArraySupportFunction::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* sourceAllocation, IRInstructionNode* destinationAllocation) {
    builder->get()->CreateMemCpy(
            destinationAllocation->getValue(),
            destinationAllocation->getAlignment(),
            sourceAllocation->getValue(),
            sourceAllocation->getAlignment(),
            sourceAllocation->getSizeInBytes());
}