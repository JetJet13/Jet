//
// Created by Johny Georges on 2024-12-09.
//

#ifndef JETLANG_IR_CLASS_METHOD_NODE_H
#define JETLANG_IR_CLASS_METHOD_NODE_H

#include <llvm/IR/Function.h>

class IRClassMethodNode {
private:
    llvm::Function* _irValue;
public:
    IRClassMethodNode(llvm::Function* irValue);
    llvm::Function* getFunction();
};

#endif //JETLANG_IR_CLASS_METHOD_NODE_H
