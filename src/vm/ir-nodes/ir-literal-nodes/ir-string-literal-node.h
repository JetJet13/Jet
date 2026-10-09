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

#ifndef JETLANG_IR_STRING_LITERAL_NODE_H
#define JETLANG_IR_STRING_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "ir-literal-node.h"
#include "../../ir-type/ir-type.h"
#include "../../ir-type/ir-array-type.h"

class IRStringLiteralNode : public IRLiteralNode {
private:
    std::shared_ptr<ASTStringLiteralNode> _astNode;
    llvm::Constant* _irValue;
    std::shared_ptr<IRArrayType> _type;
public:
    IRStringLiteralNode(std::shared_ptr<ASTStringLiteralNode> astNode, llvm::Constant* irValue, std::shared_ptr<IRArrayType> type);
    llvm::Constant* getConstantIRValue() override;
    std::shared_ptr<IRArrayType> getIRArrayType();
    std::shared_ptr<IRType> getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRING_LITERAL_NODE_H
