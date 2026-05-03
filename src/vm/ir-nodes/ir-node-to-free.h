//
// Created by Johny Georges on 2026-04-18.
//

#ifndef JETLANG_IR_NODE_TO_FREE_H
#define JETLANG_IR_NODE_TO_FREE_H

#include "ir-node.h"
#include "llvm/IR/Dominators.h"

class IRBlockNode;

class IRNodeToFree {
private:
    IRNode* _irNode;
    IRBlockNode* _irBlock;
    std::optional<IRBlockNode*> _finalIRBlockToFree = {};
public:
    IRNodeToFree(IRNode* irNode, IRBlockNode* irBlock);
    IRNode* getIRNode();
    void setFinalBlockToFree(IRBlockNode* irBlock);
    bool comesBefore(IRBlockNode* irBlockNode, llvm::DominatorTree* dominator);
};

#endif //JETLANG_IR_NODE_TO_FREE_H
