//
// Created by Johny Georges on 2025-01-13.
//

#include "ir-context.h"

IRContext::IRContext(IRBlockNode* irBlock, IRModuleNode* irModule, std::unique_ptr<llvm::LLVMContext>* context) {
    _irBlock = irBlock;
    _irModule = irModule;
    _context = context;
    _irScope = IRScope();
    _dataLayout = new llvm::DataLayout(_irModule->getModule());
}

llvm::DataLayout* IRContext::getDataLayout() {
    return _dataLayout;
}

std::unique_ptr<llvm::LLVMContext>* IRContext::getContext() {
    return _context;
}

IRBlockNode* IRContext::getIRBlock() {
    return _irBlock;
}

IRModuleNode* IRContext::getIRModule() {
    return _irModule;
}

IRScope* IRContext::getIRScope() {
    return &_irScope;
}

llvm::Module* IRContext::getModule() {
    return _irModule->getModule();
}

llvm::Function* IRContext::getFunction() {
    return _irBlock->getBlock()->getParent();
}

IRContext* IRContext::clone(IRBlockNode* irBlock) {
    return new IRContext(irBlock, _irModule, _context);
}