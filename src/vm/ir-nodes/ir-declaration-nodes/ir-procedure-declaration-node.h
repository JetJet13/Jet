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
// Created by Johny Georges on 2024-07-13.
//

#ifndef JETLANG_IR_PROCEDURE_DECLARATION_NODE_H
#define JETLANG_IR_PROCEDURE_DECLARATION_NODE_H

#include <llvm/IR/Function.h>
#include "../ir-block-nodes/ir-block-node.h"
#include "../ir-function-nodes/ir-function-parameter-list-node.h"
#include "ir-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"
#include "../../ir-lookup-table/ir-lookup-table.h"

class IRProcedureDeclarationNode : public IRDeclarationNode {
private:
    std::shared_ptr<ASTProcedureDeclarationNode> _node;
    llvm::Function* _irValue;
    std::shared_ptr<IRFunctionParameterListNode> _irParameterList;
    std::shared_ptr<IRBlockNode> _irBlock;
    std::shared_ptr<IRInstructionNode> _globalVariable;
public:
    IRProcedureDeclarationNode(std::shared_ptr<ASTProcedureDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameterList, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> globalVariable);
    std::string getName();
    std::string getNormalizedName();
    std::shared_ptr<IRFunctionParameterListNode> getParameters();
    std::shared_ptr<IRInstructionNode> getGlobalVariable();
    std::shared_ptr<IRBlockNode> getBlock();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_PROCEDURE_DECLARATION_NODE_H
