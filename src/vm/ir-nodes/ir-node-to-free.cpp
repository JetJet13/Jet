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


bool IRNodeToFree::comesBefore(IRBlockNode* irBlockNode) {
    auto function = _irBlock->getBlock()->getParent();
    if (function != irBlockNode->getBlock()->getParent()) {
        return false;
    } else if (_irBlock == irBlockNode) {
        return true;
    }

    for (auto &block : function->getFunction()) {
        if (&block == irBlockNode->getBlock()) {
            return false;
        }
        if (&block == _irBlock->getBlock()) {
            return true;
        }
    }
    return false;
}