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
// Created by Johny Georges on 2024-07-16.
//

#ifndef JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"
#include "../../ir-type/ir-struct-type.h"

class IRObjectAccessExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessExpressionNode> _node;
    std::shared_ptr<IRExpressionNode> _irSource;
    std::string _targetKey;
    uint64_t _targetKeyIndex;
    llvm::Constant* _irTargetKeyIndex;
    std::shared_ptr<IRType> _irType;
    std::optional<std::shared_ptr<IRInstructionNode>> _sourceAllocation;
public:
    IRObjectAccessExpressionNode(std::shared_ptr<ASTObjectAccessExpressionNode> node, std::shared_ptr<IRExpressionNode> irSource, std::string targetKey, uint64_t targetKeyIndex, llvm::Constant* irTargetKeyIndex, std::shared_ptr<IRType> irType, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation = {});
    void markAsGlobal() override;
    std::shared_ptr<ASTObjectAccessExpressionNode> getNode();
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getArc() override;
    std::shared_ptr<IRExpressionNode> getSource();
    std::string* getTargetKey();
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

#endif //JETLANG_IR_OBJECT_ACCESS_EXPRESSION_NODE_H
