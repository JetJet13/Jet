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
// Created by Johny Georges on 2024-09-04.
//

#ifndef JETLANG_IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE_H
#define JETLANG_IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-array-pointer-type.h"
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"


class IRAggregateIdentifierExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTIdentifierExpressionNode> _node;
    std::shared_ptr<IRInstructionNode> _arrayAllocation;
    std::shared_ptr<IRInstructionNode> _arrayPointerAllocation;
    llvm::GetElementPtrInst* _intPointer;
    llvm::LoadInst* _loadedNumElements;
    std::shared_ptr<IRInstructionNode> _sourceAllocation;
    std::shared_ptr<IRArrayPointerType> _type;
public:
    IRAggregateIdentifierExpressionNode(std::shared_ptr<ASTIdentifierExpressionNode> node, std::shared_ptr<IRInstructionNode> irAllocation, std::shared_ptr<IRInstructionNode> arrayPointerSourceAllocation, std::shared_ptr<IRInstructionNode> sourceAllocation, llvm::GetElementPtrInst* intPointer, llvm::LoadInst* loadedNumElements, std::shared_ptr<IRArrayPointerType> type);
    llvm::GetElementPtrInst* getIntPointer();
    llvm::LoadInst* getLoadedNumElements();
    llvm::Value* getValue() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    std::shared_ptr<IRInstructionNode> getAggregateSourceAllocation();
    std::shared_ptr<IRInstructionNode> getAggregateAllocation();
    std::shared_ptr<IRInstructionNode> getAggregatePointerAllocation();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    llvm::Type* getTypeAtIndex(uint64_t index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE_H
