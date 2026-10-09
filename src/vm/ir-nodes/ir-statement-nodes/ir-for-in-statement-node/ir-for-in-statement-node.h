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

#ifndef JETLANG_IR_FOR_IN_STATEMENT_NODE_H
#define JETLANG_IR_FOR_IN_STATEMENT_NODE_H

#include "../ir-statement-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"
#include "../../ir-block-nodes/ir-block-node.h"
#include "../../ir-captured-variable-node.h"
#include "../../../ir-lookup-table/ir-lookup-table.h"

class IRForInStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTForInStatementNode> _node;
    std::shared_ptr<IRInstructionNode> _index;
    std::shared_ptr<IRInstructionNode> _variable;
    std::shared_ptr<IRExpressionNode> _source;
    std::shared_ptr<IRBlockNode> _setupBlock;
    std::shared_ptr<IRBlockNode> _forInBlock;
    std::shared_ptr<IRBlockNode> _bodyBlock;
    std::shared_ptr<IRBlockNode> _endBlock;
    std::optional<std::shared_ptr<IRCapturedVariableNode>> _capturedVariable;
public:
    IRForInStatementNode(std::shared_ptr<ASTForInStatementNode> node, std::shared_ptr<IRInstructionNode> index, std::shared_ptr<IRInstructionNode> variable, std::shared_ptr<IRExpressionNode> source, std::shared_ptr<IRBlockNode> setupBlock, std::shared_ptr<IRBlockNode> forInBlock, std::shared_ptr<IRBlockNode> bodyBlock, std::shared_ptr<IRBlockNode> endBlock, std::optional<std::shared_ptr<IRCapturedVariableNode>> capturedVariable = {});
    std::shared_ptr<IRInstructionNode> getIndex();
    std::shared_ptr<IRInstructionNode> getVariable();
    std::optional<std::shared_ptr<IRCapturedVariableNode>> getCapturedVariable();
    std::shared_ptr<IRExpressionNode> getSource();
    std::shared_ptr<IRBlockNode> getSetupBlock();
    std::shared_ptr<IRBlockNode> getForInBlock();
    std::shared_ptr<IRBlockNode> getBodyBlock();
    std::shared_ptr<IRBlockNode> getEndBlock();
    void nestIn(std::shared_ptr<IRBlockNode> irBlock);
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FOR_IN_STATEMENT_NODE_H
