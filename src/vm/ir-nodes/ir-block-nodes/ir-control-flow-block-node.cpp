//
// Created by Johny Georges on 2025-11-24.
//

#include "ir-control-flow-block-node.h"

std::vector<IRVariableDeclarationNode*>* IRControlFlowBlockNode::getVariablesToFree() {
    return &_variablesToFree;
}

void IRControlFlowBlockNode::setInsertionPointBeforeLastInstruction() {
    if (llvm::isa<llvm::BranchInst>(this->getBlock()->back())) {
        this->getBuilder()->get()->SetInsertPoint(this->getBlock()->getTerminator());
    }
}