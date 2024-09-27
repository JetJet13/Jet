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
public:
    IRModuleNode(llvm::Module* irValue, std::string arrayAccessFunctionName, std::string copyStringFunctionName);
    llvm::Module* getModule();
    llvm::Function* getArrayAccessFunction();
    llvm::Function* getCopyStringFunction();
};

#endif //JETLANG_IR_MODULE_NODE_H
