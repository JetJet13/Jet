//
// Created by Johny Georges on 2024-07-05.
//

#ifndef JETLANG_IR_BLOCK_NODE_H
#define JETLANG_IR_BLOCK_NODE_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"

class IRBlockNode {
private:
    llvm::BasicBlock* _irValue;
    std::unique_ptr<llvm::IRBuilder<>> _builder;
public:
    IRBlockNode(llvm::BasicBlock* irValue);
    llvm::BasicBlock* getBlock();
    std::unique_ptr<llvm::IRBuilder<>>* getBuilder();
    void addVoidReturn();
};

#endif //JETLANG_IR_BLOCK_NODE_H
