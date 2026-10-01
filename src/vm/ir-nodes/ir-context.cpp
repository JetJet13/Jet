//
// Created by Johny Georges on 2025-01-13.
//

#include "ir-context.h"

#ifndef BUILD_TARGET
#define BUILD_TARGET "unknown"
#endif

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

bool IRContext::isTargetX86_64() {
    std::string buildTarget = BUILD_TARGET;
    return buildTarget.find("x86_64", 0) != std::string::npos;
}

bool IRContext::isTargetArm64() {
    std::string buildTarget = BUILD_TARGET;
    return buildTarget.find("aarch64", 0) != std::string::npos;
}

std::shared_ptr<IRContext> IRContext::clone(std::shared_ptr<IRBlockNode> irBlock) {
    return std::make_shared<IRContext>(irBlock, _irModule, _context);
}