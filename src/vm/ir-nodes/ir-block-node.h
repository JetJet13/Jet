//
// Created by Johny Georges on 2024-07-05.
//

#ifndef JETLANG_IR_BLOCK_NODE_H
#define JETLANG_IR_BLOCK_NODE_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "ir-declaration-nodes/ir-declaration-node.h"
#include "ir-statement-nodes/ir-statement-node.h"
#include "ir-function-nodes/ir-function-parameter-list-node.h"

class IRBlockNode {
private:
    llvm::BasicBlock* _irValue;
    std::unique_ptr<llvm::IRBuilder<>> _builder;
public:
    IRBlockNode(llvm::BasicBlock* irValue);
    llvm::BasicBlock* getBlock();
    void insert(IRDeclarationNode* irNode);
    void insert(IRStatementNode* irNode);
};

#endif //JETLANG_IR_BLOCK_NODE_H
