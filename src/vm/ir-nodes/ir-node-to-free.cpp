// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2026-04-18.
//

#include "ir-node-to-free.h"
#include "ir-block-nodes/ir-block-node.h"

IRNodeToFree::IRNodeToFree(std::shared_ptr<IRNode> irNode, std::shared_ptr<IRBlockNode> irBlock) {
    _irNode = irNode;
    _irBlock = irBlock;
}

std::shared_ptr<IRNode> IRNodeToFree::getIRNode() {
    return _irNode;
}

void IRNodeToFree::setFinalBlockToFree(std::shared_ptr<IRBlockNode> irBlock) {
    _finalIRBlockToFree = irBlock;
}

bool IRNodeToFree::comesBefore(std::shared_ptr<IRBlockNode> irBlockNode, llvm::DominatorTree* dominator) {
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