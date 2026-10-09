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
// Created by Johny Georges on 2025-01-08.
//

#ifndef JETLANG_IR_IF_ELSE_NODE_H
#define JETLANG_IR_IF_ELSE_NODE_H

#include "../../ir-expression-nodes/ir-expression-node.h"
#include "../../ir-block-nodes/ir-block-node.h"

class IRIfElseNode : public IRNode {
private:
    std::shared_ptr<IRExpressionNode> _condition;
    std::shared_ptr<IRBlockNode> _ifBlock;
    std::shared_ptr<IRBlockNode> _thenBlock;
    std::shared_ptr<IRBlockNode> _elseBlock;
    std::shared_ptr<IRBlockNode> _endBlock;
    std::optional<std::shared_ptr<IRIfElseNode>> _next;
public:
    IRIfElseNode(std::shared_ptr<IRExpressionNode> condition, std::shared_ptr<IRBlockNode> ifBlock, std::shared_ptr<IRBlockNode> thenBlock, std::shared_ptr<IRBlockNode> elseBlock, std::shared_ptr<IRBlockNode> endBlock, std::optional<std::shared_ptr<IRIfElseNode>> next = {});
    std::shared_ptr<IRExpressionNode> getExpression();
    std::shared_ptr<IRBlockNode> getIfBlock();
    std::shared_ptr<IRBlockNode> getThenBlock();
    std::shared_ptr<IRBlockNode> getElseBlock();
    std::shared_ptr<IRBlockNode> getEndBlock();
    void nestIn(std::shared_ptr<IRBlockNode> irBlock);
    void setNext(std::shared_ptr<IRIfElseNode> next);
    std::optional<std::shared_ptr<IRIfElseNode>> getNext();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IF_ELSE_NODE_H
