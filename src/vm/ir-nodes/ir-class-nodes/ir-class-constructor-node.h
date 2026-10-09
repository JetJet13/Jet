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
// Created by Johny Georges on 2024-12-09.
//

#ifndef JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H
#define JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H

#include <llvm/IR/Function.h>
#include "../ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"

class IRClassConstructorNode {
private:
    std::shared_ptr<ASTClassConstructorDeclarationNode> _node;
    llvm::Function* _irValue;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRFunctionParameterListNode> _irParameters;
public:
    IRClassConstructorNode(std::shared_ptr<ASTClassConstructorDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameters, std::shared_ptr<IRBlockNode> irBlock);
    std::shared_ptr<ASTClassConstructorDeclarationNode> getNode();
    llvm::Function* getFunction();
    std::shared_ptr<IRFunctionParameterListNode> getParameters();
    std::shared_ptr<IRBlockNode> getBlock();
};


#endif //JETLANG_IR_CLASS_CONSTRUCTOR_NODE_H
