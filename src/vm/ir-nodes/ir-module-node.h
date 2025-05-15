//
// Created by Johny Georges on 2024-07-05.
//

#ifndef JETLANG_IR_MODULE_NODE_H
#define JETLANG_IR_MODULE_NODE_H

#include "ir-node.h"

class IRModuleNode {
private:
    llvm::Module* _irValue;
    std::string _arrayAccessFunctionName;
    std::string _copyArrayFunctionName;
    std::string _copyPointerFunctionName;
    std::string _copyStructFunctionName;
    std::string _copyValueFunctionName;
    std::string _copyStringFunctionName;
    std::string _copyRefFunctionName;
    std::string _freeArrayFunctionName;
    std::string _freePointerFunctionName;
    std::string _freeStructFunctionName;
    std::string _freeValueFunctionName;
    std::string _freeStringFunctionName;
    std::string _freeRefFunctionName;
    std::string _printFunctionName;
    std::string _mallocFunctionName;
    std::string _mallocFreeFunctionName;
    std::string _mallocSizeFunctionName;
    std::string _mallocArrayPopFunctionName;
    std::string _mallocArrayPushFunctionName;
    std::string _mallocArrayEnqueueFunctionName;
    std::string _mallocFreeArrayFunctionName;
    std::string _memcpyFunctionName;
    std::string _setupSrefFunctionName;
public:
    IRModuleNode(llvm::Module* irValue,
                 std::string arrayAccessFunctionName,
                 std::string copyArrayFunctionName,
                 std::string copyPointerFunctionName,
                 std::string copyStructFunctionName,
                 std::string copyValueFunctionName,
                 std::string copyStringFunctionName,
                 std::string copyRefFunctionName,
                 std::string freeArrayFunctionName,
                 std::string freePointerFunctionName,
                 std::string freeStructFunctionName,
                 std::string freeValueFunctionName,
                 std::string freeStringFunctionName,
                 std::string freeRefFunctionName,
                 std::string printFunctionName,
                 std::string mallocFunctionName,
                 std::string mallocFreeFunctionName,
                 std::string mallocSizeFunctionName,
                 std::string mallocArrayPopFunctionName,
                 std::string mallocArrayPushFunctionName,
                 std::string mallocArrayEnqueueFunctionName,
                 std::string mallocFreeArrayFunctionName,
                 std::string memcpyFunctionName,
                 std::string setupSrefFunctionName);
    llvm::Module* getModule();
    llvm::Function* getArrayAccessFunction();
    llvm::Function* getCopyArrayFunction();
    llvm::Function* getCopyPointerFunction();
    llvm::Function* getCopyStructFunction();
    llvm::Function* getCopyValueFunction();
    llvm::Function* getCopyStringFunction();
    llvm::Function* getCopyRefFunction();
    llvm::Function* getFreeArrayFunction();
    llvm::Function* getFreePointerFunction();
    llvm::Function* getFreeStructFunction();
    llvm::Function* getFreeValueFunction();
    llvm::Function* getFreeStringFunction();
    llvm::Function* getFreeRefFunction();
    llvm::Function* getPrintFunction();
    llvm::Function* getMallocFunction();
    llvm::Function* getMallocFreeFunction();
    llvm::Function* getMallocSizeFunction();
    llvm::Function* getMallocArrayPopFunction();
    llvm::Function* getMallocArrayPushFunction();
    llvm::Function* getMallocArrayEnqueueFunction();
    llvm::Function* getMallocFreeArrayFunction();
    llvm::Function* getMemcpyFunction();
    llvm::Function* getSetupSrefFunction();
};

#endif //JETLANG_IR_MODULE_NODE_H
