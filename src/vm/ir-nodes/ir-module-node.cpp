//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-module-node.h"

IRModuleNode::IRModuleNode(llvm::Module* irValue, std::string arrayAccessFunctionName, std::string copyArrayFunctionName, std::string copyPointerFunctionName, std::string copyStructFunctionName, std::string copyValueFunctionName, std::string copyStringFunctionName, std::string copyRefFunctionName, std::string freeArrayFunctionName, std::string freePointerFunctionName, std::string freeStructFunctionName, std::string freeValueFunctionName, std::string freeStringFunctionName, std::string freeRefFunctionName, std::string printFunctionName, std::string mallocFunctionName, std::string mallocFreeFunctionName, std::string mallocSizeFunctionName, std::string mallocArrayPopFunctionName, std::string mallocArrayPushFunctionName, std::string mallocArrayEnqueueFunctionName, std::string mallocFreeArrayFunctionName, std::string memcpyFunctionName, std::string setupSrefFunctionName, std::string setupRefFunctionName) {
    _irValue = irValue;
    _arrayAccessFunctionName = arrayAccessFunctionName;
    _copyArrayFunctionName = copyArrayFunctionName;
    _copyPointerFunctionName = copyPointerFunctionName;
    _copyStructFunctionName = copyStructFunctionName;
    _copyValueFunctionName = copyValueFunctionName;
    _copyStringFunctionName = copyStringFunctionName;
    _copyRefFunctionName = copyRefFunctionName;
    _freeArrayFunctionName = freeArrayFunctionName;
    _freePointerFunctionName = freePointerFunctionName;
    _freeStructFunctionName = freeStructFunctionName;
    _freeValueFunctionName = freeValueFunctionName;
    _freeStringFunctionName = freeStringFunctionName;
    _freeRefFunctionName = freeRefFunctionName;
    _printFunctionName = printFunctionName;
    _mallocFunctionName = mallocFunctionName;
    _mallocFreeFunctionName = mallocFreeFunctionName;
    _mallocSizeFunctionName = mallocSizeFunctionName;
    _mallocArrayPopFunctionName = mallocArrayPopFunctionName;
    _mallocArrayPushFunctionName = mallocArrayPushFunctionName;
    _mallocArrayEnqueueFunctionName = mallocArrayEnqueueFunctionName;
    _mallocFreeArrayFunctionName = mallocFreeArrayFunctionName;
    _memcpyFunctionName = memcpyFunctionName;
    _setupSrefFunctionName = setupSrefFunctionName;
    _setupRefFunctionName = setupRefFunctionName;
}

llvm::Module* IRModuleNode::getModule() {
    return _irValue;
}

llvm::Function* IRModuleNode::getArrayAccessFunction() {
    return _irValue->getFunction(_arrayAccessFunctionName);
}

llvm::Function* IRModuleNode::getCopyArrayFunction() {
    return _irValue->getFunction(_copyArrayFunctionName);
}

llvm::Function* IRModuleNode::getCopyPointerFunction() {
    return _irValue->getFunction(_copyPointerFunctionName);
}

llvm::Function* IRModuleNode::getCopyStructFunction() {
    return _irValue->getFunction(_copyStructFunctionName);
}

llvm::Function* IRModuleNode::getCopyValueFunction() {
    return _irValue->getFunction(_copyValueFunctionName);
}

llvm::Function* IRModuleNode::getCopyStringFunction() {
    return _irValue->getFunction(_copyStringFunctionName);
}

llvm::Function* IRModuleNode::getCopyRefFunction() {
    return _irValue->getFunction(_copyRefFunctionName);
}

llvm::Function* IRModuleNode::getFreeArrayFunction() {
    return _irValue->getFunction(_freeArrayFunctionName);
}

llvm::Function* IRModuleNode::getFreePointerFunction() {
    return _irValue->getFunction(_freePointerFunctionName);
}

llvm::Function* IRModuleNode::getFreeStructFunction() {
    return _irValue->getFunction(_freeStructFunctionName);
}

llvm::Function* IRModuleNode::getFreeValueFunction() {
    return _irValue->getFunction(_freeValueFunctionName);
}

llvm::Function* IRModuleNode::getFreeStringFunction() {
    return _irValue->getFunction(_freeStringFunctionName);
}

llvm::Function* IRModuleNode::getFreeRefFunction() {
    return _irValue->getFunction(_freeRefFunctionName);
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

llvm::Function* IRModuleNode::getMallocArrayPopFunction() {
    return _irValue->getFunction(_mallocArrayPopFunctionName);
}

llvm::Function* IRModuleNode::getMallocArrayPushFunction() {
    return _irValue->getFunction(_mallocArrayPushFunctionName);
}

llvm::Function* IRModuleNode::getMallocArrayEnqueueFunction() {
    return _irValue->getFunction(_mallocArrayEnqueueFunctionName);
}

llvm::Function* IRModuleNode::getMallocFreeArrayFunction() {
    return _irValue->getFunction(_mallocFreeArrayFunctionName);
}

llvm::Function* IRModuleNode::getMemcpyFunction() {
    return _irValue->getFunction(_memcpyFunctionName);
}

llvm::Function* IRModuleNode::getSetupSrefFunction() {
    return _irValue->getFunction(_setupSrefFunctionName);
}

llvm::Function* IRModuleNode::getSetupRefFunction() {
    return _irValue->getFunction(_setupRefFunctionName);
}