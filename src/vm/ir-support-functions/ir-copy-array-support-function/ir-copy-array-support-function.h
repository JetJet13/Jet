//
// Created by Johny Georges on 2024-08-07.
//

#ifndef JETLANG_IR_COPY_ARRAY_SUPPORT_FUNCTION_H
#define JETLANG_IR_COPY_ARRAY_SUPPORT_FUNCTION_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Intrinsics.h>
#include <utility>
#include "../../ir-nodes/ir-instruction-node.h"
#include "../../ir-type/ir-array-pointer-type.h"

class IRCopyArraySupportFunction {
public:
    static void insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* sourceAllocation, IRInstructionNode* destinationAllocation);
};

#endif //JETLANG_IR_COPY_ARRAY_SUPPORT_FUNCTION_H
