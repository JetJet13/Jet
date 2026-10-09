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
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_BOOL_LITERAL_NODE_H
#define JETLANG_IR_BOOL_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "ir-literal-node.h"

class IRBoolLiteralNode : public IRLiteralNode {
private:
    std::shared_ptr<ASTBooleanLiteralNode> _astNode;
    llvm::ConstantInt* _irValue;
    std::shared_ptr<IRType> _type;
public:
    IRBoolLiteralNode(std::shared_ptr<ASTBooleanLiteralNode> astNode, llvm::ConstantInt* irValue);
    llvm::ConstantInt* getConstantIRValue() override;
    std::shared_ptr<IRType> getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_BOOL_LITERAL_NODE_H
