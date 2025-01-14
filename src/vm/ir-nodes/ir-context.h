//
// Created by Johny Georges on 2025-01-13.
//

#ifndef JETLANG_IR_CONTEXT_H
#define JETLANG_IR_CONTEXT_H

#include "llvm/IR/LLVMContext.h"
#include "ir-block-node.h"
#include "ir-module-node.h"

class IRContext {
private:
    std::unique_ptr<llvm::LLVMContext>* _context;
    IRBlockNode* _irBlock;
    IRModuleNode* _irModule;
public:
    IRContext(IRBlockNode* irBlock, IRModuleNode* irModule, std::unique_ptr<llvm::LLVMContext>* context);
    std::unique_ptr<llvm::LLVMContext>* getContext();
    IRBlockNode* getIRBlock();
    IRModuleNode* getIRModule();
    llvm::Module* getModule();
    llvm::Function* getFunction();
    IRContext* clone(IRBlockNode* irBlock);
};

#endif //JETLANG_IR_CONTEXT_H
