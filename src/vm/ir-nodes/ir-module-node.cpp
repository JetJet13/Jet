//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-module-node.h"

IRModuleNode::IRModuleNode(llvm::Module* irValue, std::string arrayAccessFunctionName, std::string copyStringFunctionName, std::string printFunctionName, std::string mallocFunctionName, std::string mallocFreeFunctionName, std::string mallocSizeFunctionName) {
    _irValue = irValue;
    _arrayAccessFunctionName = arrayAccessFunctionName;
    _copyStringFunctionName = copyStringFunctionName;
    _printFunctionName = printFunctionName;
    _mallocFunctionName = mallocFunctionName;
    _mallocFreeFunctionName = mallocFreeFunctionName;
    _mallocSizeFunctionName = mallocSizeFunctionName;
}

llvm::Module* IRModuleNode::getModule() {
    return _irValue;
}

llvm::Function* IRModuleNode::getArrayAccessFunction() {
    return _irValue->getFunction(_arrayAccessFunctionName);
}

llvm::Function* IRModuleNode::getCopyStringFunction() {
    return _irValue->getFunction(_copyStringFunctionName);
}

llvm::Function* IRModuleNode::getPrintFunction() {
    return _irValue->getFunction(_printFunctionName);
}

llvm::Function* IRModuleNode::getMallocFunction() {
    return _irValue->getFunction(_mallocFunctionName);
}

llvm::Function* IRModuleNode::getMallocFreeFunction() {
    return _irValue->getFunction(_mallocFreeFunctionName);
}

llvm::Function* IRModuleNode::getMallocSizeFunction() {
    return _irValue->getFunction(_mallocSizeFunctionName);
}