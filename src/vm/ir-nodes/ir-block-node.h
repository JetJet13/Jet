//
// Created by Johny Georges on 2024-07-05.
//

#ifndef JETLANG_IR_BLOCK_NODE_H
#define JETLANG_IR_BLOCK_NODE_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "ir-node.h"
#include "ir-declaration-nodes/ir-variable-declaration-node.h"
#include "ir-statement-nodes/ir-function-return-expression-node.h"

class IRBlockNode {
private:
    llvm::BasicBlock* _irValue;
    std::unique_ptr<llvm::IRBuilder<>> _builder;
    std::vector<IRNode*> _body;
    std::vector<IRBlockNode*> _successors;
    std::optional<IRBlockNode*> _parentBlock;
public:
    IRBlockNode(llvm::BasicBlock* irValue);
    bool hasReturnStatement();
    bool hasBranchStatement();
    llvm::BasicBlock* getBlock();
    std::vector<IRNode*>* getBody();
    void insert(IRNode* irNode);
    std::unique_ptr<llvm::IRBuilder<>>* getBuilder();
    void addVoidReturn();
    void createSuccessor();
    std::vector<IRBlockNode*>* getSuccessors();
    void addSuccessor(IRBlockNode* successorIrBlock);
    IRBlockNode* getLastSuccessorOrSelf();
    std::optional<IRBlockNode*> getParentBlock();
    void setParentBlock(IRBlockNode* parentIRBlock);
};

#endif //JETLANG_IR_BLOCK_NODE_H
