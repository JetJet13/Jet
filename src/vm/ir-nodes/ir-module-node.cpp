//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-module-node.h"

IRModuleNode::IRModuleNode(llvm::Module* irValue, std::string arrayAccessFunctionName, std::string copyStringFunctionName) {
    _irValue = irValue;
    _arrayAccessFunctionName = arrayAccessFunctionName;
    _copyStringFunctionName = copyStringFunctionName;
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