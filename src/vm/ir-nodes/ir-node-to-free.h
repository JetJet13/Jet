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
    std::shared_ptr<IRNode> _irNode;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::optional<std::shared_ptr<IRBlockNode>> _finalIRBlockToFree = {};
public:
    IRNodeToFree(std::shared_ptr<IRNode> irNode, std::shared_ptr<IRBlockNode> irBlock);
    std::shared_ptr<IRNode> getIRNode();
    void setFinalBlockToFree(std::shared_ptr<IRBlockNode> irBlock);
    bool comesBefore(std::shared_ptr<IRBlockNode> irBlockNode, llvm::DominatorTree* dominator);
};

#endif //JETLANG_IR_NODE_TO_FREE_H
