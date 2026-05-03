//
// Created by Johny Georges on 2026-04-18.
//

#include "ir-node-to-free.h"
#include "ir-block-nodes/ir-block-node.h"

IRNodeToFree::IRNodeToFree(IRNode* irNode, IRBlockNode* irBlock) {
    _irNode = irNode;
    _irBlock = irBlock;
}

IRNode* IRNodeToFree::getIRNode() {
    return _irNode;
}

void IRNodeToFree::setFinalBlockToFree(IRBlockNode* irBlock) {
    _finalIRBlockToFree = irBlock;
}

bool IRNodeToFree::comesBefore(IRBlockNode* irBlockNode, llvm::DominatorTree* dominator) {
    auto function = _irBlock->getBlock()->getParent();
    if (function != irBlockNode->getBlock()->getParent()) {
        return false;
    }

    if (_finalIRBlockToFree && dominator->dominates(_finalIRBlockToFree.value()->getBlock(), irBlockNode->getBlock())) {
        return false;
    } else if (dominator->dominates(_irBlock->getBlock(), irBlockNode->getBlock())) {
        return true;
    }

    return false;
}