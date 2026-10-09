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
// Created by Johny Georges on 2025-05-24.
//

#ifndef JETLANG_IR_WHILE_STATEMENT_NODE_H
#define JETLANG_IR_WHILE_STATEMENT_NODE_H

#include "../ir-statement-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"
#include "../../ir-block-nodes/ir-block-node.h"

class IRWhileStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTWhileStatementNode> _node;
    std::shared_ptr<IRExpressionNode> _condition;
    std::shared_ptr<IRBlockNode> _whileBlock;
    std::shared_ptr<IRBlockNode> _bodyBlock;
    std::shared_ptr<IRBlockNode> _endBlock;
public:
    IRWhileStatementNode(std::shared_ptr<ASTWhileStatementNode> node, std::shared_ptr<IRExpressionNode> condition, std::shared_ptr<IRBlockNode> whileBlock, std::shared_ptr<IRBlockNode> bodyBlock, std::shared_ptr<IRBlockNode> endBlock);
    std::shared_ptr<IRExpressionNode> getExpression();
    std::shared_ptr<IRBlockNode> getWhileBlock();
    std::shared_ptr<IRBlockNode> getBodyBlock();
    std::shared_ptr<IRBlockNode> getEndBlock();
    void nestIn(std::shared_ptr<IRBlockNode> irBlock);
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_WHILE_STATEMENT_NODE_H
