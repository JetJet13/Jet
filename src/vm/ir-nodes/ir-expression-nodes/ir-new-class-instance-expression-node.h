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
// Created by Johny Georges on 2024-12-30.
//

#ifndef JETLANG_IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE_H
#define JETLANG_IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../core/type-signature/class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../../ir-type/ir-class-type.h"
#include "../../ir-type/ir-new-class-instance-type.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRNewClassInstanceExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTNewClassInstanceExpressionNode> _node;
    std::string _constructorId;
    std::shared_ptr<IRFunctionType> _irConstructorType;
    std::vector<std::shared_ptr<IRFunctionArgumentNode>> _arguments;
    std::shared_ptr<IRNewClassInstanceType> _type;
    std::shared_ptr<IRInstructionNode> _classInstanceAllocation;
    std::shared_ptr<IRInstructionNode> _irArc;
public:
    IRNewClassInstanceExpressionNode(std::shared_ptr<ASTNewClassInstanceExpressionNode> node, std::string constructorId, std::shared_ptr<IRFunctionType> irConstructorType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRNewClassInstanceType> type, std::shared_ptr<IRInstructionNode> classInstanceAllocation, std::shared_ptr<IRInstructionNode> irArc);
    void markAsGlobal() override;
    std::shared_ptr<IRInstructionNode> getClassInstanceAllocation();
    std::vector<std::shared_ptr<IRFunctionArgumentNode>>* getIRArguments();
    std::optional<std::shared_ptr<IRInstructionNode>> getArc() override;
    llvm::Value* getValue() override;
    std::shared_ptr<IRFunctionType> getConstructorIRType();
    std::string getConstructorId();
    std::shared_ptr<IRNewClassInstanceType> getIRClassInstanceType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE_H
