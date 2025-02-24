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
    std::string _copyStringFunctionName;
    std::string _printFunctionName;
    std::string _mallocFunctionName;
    std::string _mallocFreeFunctionName;
    std::string _mallocSizeFunctionName;
public:
    IRModuleNode(llvm::Module* irValue, std::string arrayAccessFunctionName, std::string copyStringFunctionName, std::string printFunctionName, std::string mallocFunctionName, std::string mallocFreeFunctionName, std::string mallocSizeFunctionName);
    llvm::Module* getModule();
    llvm::Function* getArrayAccessFunction();
    llvm::Function* getCopyStringFunction();
    llvm::Function* getPrintFunction();
    llvm::Function* getMallocFunction();
    llvm::Function* getMallocFreeFunction();
    llvm::Function* getMallocSizeFunction();
};

#endif //JETLANG_IR_MODULE_NODE_H
