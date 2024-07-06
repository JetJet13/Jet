//
// Created by Johny Georges on 2024-07-05.
//

#ifndef JETLANG_IR_MODULE_NODE_H
#define JETLANG_IR_MODULE_NODE_H

#include "ir-node.h"

class IRModuleNode {
private:
    llvm::Module* _irValue;
public:
    IRModuleNode(llvm::Module* irValue);
    llvm::Module* getModule();
};

#endif //JETLANG_IR_MODULE_NODE_H
