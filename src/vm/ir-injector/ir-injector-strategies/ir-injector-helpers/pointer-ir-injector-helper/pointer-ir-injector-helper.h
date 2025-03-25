//
// Created by Johny Georges on 2025-03-24.
//

#ifndef JETLANG_POINTER_IR_INJECTOR_HELPER_H
#define JETLANG_POINTER_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"

class PointerIRInjectorHelper {
public:
    static llvm::Value* injectPointerCopy(IRBlockNode* irBlock, IRPointerType* irPointerType, llvm::Value* sourcePointer, IRInstructionNode* sourceValueAllocation, IRModuleNode* irModule, IROperationType irOperationType);
    static llvm::Value* injectPointerCopy(IRBlockNode* irBlock, IRPointerType* irPointerType, llvm::Value* sourcePointer, IRModuleNode* irModule, IROperationType irOperationType);
};

#endif //JETLANG_POINTER_IR_INJECTOR_HELPER_H
