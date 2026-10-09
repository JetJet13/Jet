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

#include "while-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-while-statement-node/ir-while-statement-node.h"

std::shared_ptr<IRStatementNode> WhileStatementIRStrategy::generate(std::shared_ptr<ASTWhileStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto whileConditionIRExpression = irGenerator->generateFor(node->getCondition()->getCondition(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto whileConditionBlock = irGenerator->generateWhileConditionBlock(irContext, scope);
    auto whileBodyBlock = irGenerator->generateWhileBodyBlock(irContext, scope);
    this->setupBlock(whileBodyBlock, node->getBlock(), irGenerator, scope, irContext);
    auto endBlock = irGenerator->generateWhileEndBlock(irContext, scope);
    return std::make_shared<IRWhileStatementNode>(node, whileConditionIRExpression, whileConditionBlock, whileBodyBlock, endBlock);
}

std::shared_ptr<IRBlockNode> WhileStatementIRStrategy::setupBlock(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<ASTControlFlowBlockNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    for (auto statement : *node->getContents()) {
        irBlockNode->insert(irGenerator->generateFor(statement, irBlockNode->getScope(), irContext));
    }
    return irBlockNode;
}