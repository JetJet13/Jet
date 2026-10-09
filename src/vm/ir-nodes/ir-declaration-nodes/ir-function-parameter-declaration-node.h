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

#ifndef JETLANG_IR_FUNCTION_PARAMETER_DECLARATION_NODE_H
#define JETLANG_IR_FUNCTION_PARAMETER_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-declaration-node.h"
#include "../ir-function-nodes/ir-function-parameter-node.h"
#include "../ir-instruction-node.h"

class IRFunctionParameterDeclarationNode : public IRDeclarationNode {
private:
    llvm::Argument* _argument;
    std::shared_ptr<IRInstructionNode> _irValue;
    std::optional<std::shared_ptr<IRInstructionNode>> _irArc;
public:
    IRFunctionParameterDeclarationNode(llvm::Argument* argument, std::shared_ptr<IRInstructionNode> irValue, std::optional<std::shared_ptr<IRInstructionNode>> irArc = {});
    llvm::Value* getValue() override;
    llvm::Argument* getArgument();
    std::shared_ptr<IRInstructionNode> getAllocation();
    std::optional<std::shared_ptr<IRInstructionNode>> getArc();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_DECLARATION_NODE_H
