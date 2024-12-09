//
// Created by Johny Georges on 2024-12-09.
//

#ifndef JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H
#define JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H

#include <llvm/IR/Function.h>

class IRClassConstructorNode {
private:
    llvm::Function* _irValue;
public:
    IRClassConstructorNode(llvm::Function* irValue);
    llvm::Function* getFunction();
};


#endif //JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H
