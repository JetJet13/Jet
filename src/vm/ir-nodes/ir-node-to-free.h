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
