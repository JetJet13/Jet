//
// Created by Johny Georges on 2025-03-24.
//

#ifndef JETLANG_INSTRUCTION_IR_INJECTOR_HELPER_H
#define JETLANG_INSTRUCTION_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-load-instruction-node.h"
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../ir-injector.h"

class InstructionIRInjectorHelper {
public:
    static llvm::Value* inject(IRTypeValueInstructionNode* irTypeValueInstructionNode, IRBlockNode* irBlock, std::string name = "");
    static llvm::Value* inject(IRInstructionNode* irInstruction, IRBlockNode* irBlock, std::string name = "");
    static llvm::Value* injectLoad(IRInstructionNode* irInstruction, IRBlockNode* irBlock, std::string name = "");
    static llvm::Value* injectLoad(std::shared_ptr<IRPointerType> irPointerType, llvm::Value* sourcePointer, IRBlockNode* irBlock, std::string name = "");
    static llvm::LoadInst* injectLoad(llvm::Type* type, llvm::Value* source, IRBlockNode* irBlock, std::optional<std::shared_ptr<IRType>> irType = {}, std::string name = "");
    static llvm::StoreInst* injectStore(llvm::Value* value, llvm::Value* source, IRBlockNode* irBlock, std::optional<std::shared_ptr<IRType>> irType = {});
};

#endif //JETLANG_INSTRUCTION_IR_INJECTOR_HELPER_H
