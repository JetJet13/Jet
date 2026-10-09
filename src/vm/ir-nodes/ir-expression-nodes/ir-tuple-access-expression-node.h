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
// Created by Johny Georges on 2024-10-09.
//

#ifndef JETLANG_IR_TUPLE_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_TUPLE_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "../../ir-type/ir-struct-ref-type.h"

class IRTupleAccessExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTTupleAccessExpressionNode> _node;
    std::shared_ptr<IRExpressionNode> _irSource;
    uint64_t _targetKeyIndex;
    llvm::Constant* _irTargetKeyIndex;
    std::shared_ptr<IRType> _irType;
    std::optional<std::shared_ptr<IRInstructionNode>> _sourceAllocation;
public:
    IRTupleAccessExpressionNode(std::shared_ptr<ASTTupleAccessExpressionNode> node, std::shared_ptr<IRExpressionNode> irSource, uint64_t targetKeyIndex, llvm::Constant* irTargetKeyIndex, std::shared_ptr<IRType> irType, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation = {});
    void markAsGlobal() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getArc() override;
    std::shared_ptr<IRExpressionNode> getSource();
    llvm::Constant* getIRTargetKeyIndex();
    uint64_t getTargetKeyIndex();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    std::shared_ptr<IRType> getTargetIRType();
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_TUPLE_ACCESS_EXPRESSION_NODE_H
