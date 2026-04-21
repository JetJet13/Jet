//
// Created by Johny Georges on 2025-11-24.
//

#include "ir-control-flow-block-node.h"


void IRControlFlowBlockNode::setInsertionPointBeforeLastInstruction() {
    if (this->getBlock()->getTerminator()) {
        this->getBuilder()->get()->SetInsertPoint(this->getBlock()->getTerminator());
    }
}