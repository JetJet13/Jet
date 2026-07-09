//
// Created by Johny Georges on 2025-03-24.
//

#ifndef JETLANG_POINTER_IR_INJECTOR_HELPER_H
#define JETLANG_POINTER_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"

class PointerIRInjectorHelper {
private:
    static std::shared_ptr<IRInstructionNode> injectPointerSourceAllocation(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRPointerType> irPointerType, llvm::Value* sourceValue, std::shared_ptr<IRModuleNode> irModule);
public:
    static llvm::Value* injectPointerCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRPointerType> irPointerType, std::shared_ptr<IRInstructionNode> sourceValueAllocation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector);
    static llvm::Value* injectPointerCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRPointerType> irPointerType, llvm::Value* sourcePointer, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector);
};

#endif //JETLANG_POINTER_IR_INJECTOR_HELPER_H
