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
// Created by Johny Georges on 2025-03-19.
//

#ifndef JETLANG_IR_DREF_EXPRESSION_NODE_H
#define JETLANG_IR_DREF_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../ir-literal-nodes/ir-literal-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"

class IRDrefExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTDrefExpressionNode> _node;
    std::shared_ptr<IRExpressionNode> _irExpression;
    std::shared_ptr<IRType> _irType;
    std::shared_ptr<IRInstructionNode> _irValue;
public:
    IRDrefExpressionNode(std::shared_ptr<ASTDrefExpressionNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRType> irType, std::shared_ptr<IRInstructionNode> irValue);
    void markAsGlobal() override;
    std::shared_ptr<IRExpressionNode> getExpression();
    std::shared_ptr<IRInstructionNode> getIRValue();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_DREF_EXPRESSION_NODE_H
