//
// Created by Johny Georges on 2025-01-13.
//

#include "ir-context.h"

IRContext::IRContext(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRModuleNode> irModule, std::unique_ptr<llvm::LLVMContext>* context) {
    _irBlock = irBlock;
    _irModule = irModule;
    _context = context;
    _irScope = IRScope();
    _dataLayout = new llvm::DataLayout(_irModule->getModule()->get());
}

llvm::DataLayout* IRContext::getDataLayout() {
    return _dataLayout;
}

std::unique_ptr<llvm::LLVMContext>* IRContext::getContext() {
    return _context;
}

std::shared_ptr<IRBlockNode> IRContext::getIRBlock() {
    return _irBlock;
}

std::shared_ptr<IRModuleNode> IRContext::getIRModule() {
    return _irModule;
}

IRScope* IRContext::getIRScope() {
    return &_irScope;
}

llvm::Module* IRContext::getModule() {
    return _irModule->getModule()->get();
}

llvm::Function* IRContext::getFunction() {
    return _irBlock->getBlock()->getParent();
}

IRContext* IRContext::clone(std::shared_ptr<IRBlockNode> irBlock) {
    return new IRContext(irBlock, _irModule, _context);
}