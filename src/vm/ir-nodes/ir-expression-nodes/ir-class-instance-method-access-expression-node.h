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
// Created by Johny Georges on 2026-08-29.
//

#ifndef JETLANG_IR_CLASS_INSTANCE_METHOD_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_CLASS_INSTANCE_METHOD_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "ir-expression-node.h"
#include "../../ir-type/ir-struct-ref-type.h"
#include "../../ir-type/ir-invocable-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"

class IRClassInstanceMethodAccessExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessExpressionNode> _node;
    std::shared_ptr<IRExpressionNode> _classInstance;
    std::shared_ptr<IRInstructionNode> _irMethod;
    std::shared_ptr<IRType> _irType;
public:
    IRClassInstanceMethodAccessExpressionNode(std::shared_ptr<ASTObjectAccessExpressionNode> node, std::shared_ptr<IRExpressionNode> classInstance, std::shared_ptr<IRInstructionNode> irMethod, std::shared_ptr<IRType> irType);
    std::shared_ptr<ASTObjectAccessExpressionNode> getNode();
    std::shared_ptr<IRExpressionNode> getClassInstance();
    std::shared_ptr<IRInstructionNode> getIRMethod();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CLASS_INSTANCE_METHOD_ACCESS_EXPRESSION_NODE_H
