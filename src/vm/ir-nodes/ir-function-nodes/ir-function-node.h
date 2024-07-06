//
// Created by Johny Georges on 2024-07-05.
//

#ifndef JETLANG_IR_FUNCTION_NODE_H
#define JETLANG_IR_FUNCTION_NODE_H

#include <llvm/IR/Function.h>

class IRFunctionNode {
private:
    llvm::Function* _irValue;
public:
    IRFunctionNode(llvm::Function* irValue);
    llvm::Function* getFunction();
};

#endif //JETLANG_IR_FUNCTION_NODE_H
