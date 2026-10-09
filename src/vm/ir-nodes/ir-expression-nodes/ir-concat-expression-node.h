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
// Created by Johny Georges on 2025-06-09.
//

#ifndef JETLANG_IR_CONCAT_EXPRESSION_NODE_H
#define JETLANG_IR_CONCAT_EXPRESSION_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-concat-expression-node.h"
#include "ir-expression-node.h"
#include "../../ir-type/ir-array-pointer-type.h"

class IRConcatExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTConcatExpressionNode> _node;
    llvm::CallInst* _irValue;
    std::shared_ptr<IRExpressionNode> _irLeftNode;
    std::shared_ptr<IRExpressionNode> _irRightNode;
    std::shared_ptr<IRArrayPointerType> _type;
public:
    IRConcatExpressionNode(std::shared_ptr<ASTConcatExpressionNode> astNode, llvm::CallInst* irValue, std::shared_ptr<IRExpressionNode> irLeftNode, std::shared_ptr<IRExpressionNode> irRightNode, std::shared_ptr<IRArrayPointerType> type);
    void markAsGlobal() override;
    llvm::CallInst* getValue() override;
    std::shared_ptr<IRExpressionNode> getLeftNode();
    std::shared_ptr<IRExpressionNode> getRightNode();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CONCAT_EXPRESSION_NODE_H
