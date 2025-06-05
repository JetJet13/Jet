//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-module-node.h"

IRModuleNode::IRModuleNode(llvm::Module* irValue, std::string arrayAccessFunctionName, std::string copyArrayFunctionName, std::string copyPointerFunctionName, std::string copyStructFunctionName, std::string copyValueFunctionName, std::string copyStringFunctionName, std::string copyRefFunctionName, std::string freeArrayFunctionName, std::string freePointerFunctionName, std::string freeStructFunctionName, std::string freeValueFunctionName, std::string freeStringFunctionName, std::string freeRefFunctionName, std::string printFunctionName, std::string range1pFunctionName, std::string range2pFunctionName, std::string range3pFunctionName, std::string mallocFunctionName, std::string mallocFreeFunctionName, std::string mallocSizeFunctionName, std::string arrayPopFunctionName, std::string arrayPushFunctionName, std::string arrayConcatFunctionName, std::string arrayHeadFunctionName, std::string arrayLastFunctionName, std::string arrayDropFunctionName, std::string arrayDropLastFunctionName, std::string memcpyFunctionName, std::string setupSrefFunctionName, std::string setupRefFunctionName) {
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
    _range1pFunctionName = range1pFunctionName;
    _range2pFunctionName = range2pFunctionName;
    _range3pFunctionName = range3pFunctionName;
    _mallocFunctionName = mallocFunctionName;
    _mallocFreeFunctionName = mallocFreeFunctionName;
    _mallocSizeFunctionName = mallocSizeFunctionName;
    _arrayPopFunctionName = arrayPopFunctionName;
    _arrayPushFunctionName = arrayPushFunctionName;
    _arrayConcatFunctionName = arrayConcatFunctionName;
    _arrayHeadFunctionName = arrayHeadFunctionName;
    _arrayLastFunctionName = arrayLastFunctionName;
    _arrayDropFunctionName = arrayDropFunctionName;
    _arrayDropLastFunctionName = arrayDropLastFunctionName;
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

llvm::Function* IRModuleNode::getRange1pFunction() {
    return _irValue->getFunction(_range1pFunctionName);
}

llvm::Function* IRModuleNode::getRange2pFunction() {
    return _irValue->getFunction(_range2pFunctionName);
}

llvm::Function* IRModuleNode::getRange3pFunction() {
    return _irValue->getFunction(_range3pFunctionName);
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

llvm::Function* IRModuleNode::getArrayPopFunction() {
    return _irValue->getFunction(_arrayPopFunctionName);
}

llvm::Function* IRModuleNode::getArrayPushFunction() {
    return _irValue->getFunction(_arrayPushFunctionName);
}

llvm::Function* IRModuleNode::getArrayConcatFunction() {
    return _irValue->getFunction(_arrayConcatFunctionName);
}

llvm::Function* IRModuleNode::getArrayHeadFunction() {
    return _irValue->getFunction(_arrayHeadFunctionName);
}

llvm::Function* IRModuleNode::getArrayLastFunction() {
    return _irValue->getFunction(_arrayLastFunctionName);
}

llvm::Function* IRModuleNode::getArrayDropFunction() {
    return _irValue->getFunction(_arrayDropFunctionName);
}

llvm::Function* IRModuleNode::getArrayDropLastFunction() {
    return _irValue->getFunction(_arrayDropLastFunctionName);
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