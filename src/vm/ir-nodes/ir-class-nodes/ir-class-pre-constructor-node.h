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
// Created by Johny Georges on 2025-12-27.
//

#ifndef JETLANG_IR_CLASS_PRE_CONSTRUCTOR_NODE_H
#define JETLANG_IR_CLASS_PRE_CONSTRUCTOR_NODE_H

#include <vector>
#include <llvm/IR/Function.h>
#include "../ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"

class IRClassPreConstructorNode {
private:
    llvm::Function* _irValue;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRInstructionNode> _classScopeParameter;
    std::vector<std::pair<uint64_t, std::shared_ptr<IRExpressionNode>>> _irExpressions;
    std::vector<std::pair<uint64_t, llvm::Constant*>> _irInitializers;
public:
    IRClassPreConstructorNode(llvm::Function* irValue, std::shared_ptr<IRInstructionNode> classScopeParameter, std::vector<std::pair<uint64_t, std::shared_ptr<IRExpressionNode>>> irExpressions, std::vector<std::pair<uint64_t, llvm::Constant*>> irInitializers, std::shared_ptr<IRBlockNode> irBlock);
    llvm::Function* getFunction();
    std::vector<std::pair<uint64_t, std::shared_ptr<IRExpressionNode>>>* getExpressions();
    std::vector<std::pair<uint64_t, llvm::Constant*>>* getInitializers();
    std::shared_ptr<IRInstructionNode> getClassScopeParameter();
    std::shared_ptr<IRBlockNode> getBlock();
    std::shared_ptr<IRLookupTable> getScope();
};

#endif //JETLANG_IR_CLASS_PRE_CONSTRUCTOR_NODE_H
