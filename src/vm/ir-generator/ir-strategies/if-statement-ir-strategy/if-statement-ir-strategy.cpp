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

#include "if-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-else-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-statement-node.h"

std::shared_ptr<IRStatementNode> IfStatementIRStrategy::generate(std::shared_ptr<ASTIfStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto ifConditionIRExpression = irGenerator->generateFor(node->getIfBlock()->getCondition()->getCondition(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto ifConditionBlock = irGenerator->generateIfBlock(irContext, scope);
    auto thenBlock = irGenerator->generateIfThenBlock(irContext, scope);
    this->setupBlock(thenBlock, node->getIfBlock()->getBlock(), irGenerator, scope, irContext);
    auto endBlock = irGenerator->generateIfEndBlock(irContext, scope);
    auto ifNode = std::make_shared<IRIfElseNode>(
            ifConditionIRExpression,
            ifConditionBlock,
            thenBlock,
            irGenerator->generateIfElseBlock(irContext, scope)->markAsFakeBlock(),
            endBlock
    );
    auto currentIfNode = ifNode;
    for (auto elseIf : *node->getElseIfBlocks()) {
        auto elseIfConditionIRExpression = irGenerator->generateFor(elseIf->getCondition()->getCondition(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
        auto elseIfNode = std::make_shared<IRIfElseNode>(
            elseIfConditionIRExpression,
            irGenerator->generateIfBlock(irContext, scope),
            this->setupBlock(irGenerator->generateIfThenBlock(irContext, scope), elseIf->getBlock(), irGenerator, scope, irContext),
            irGenerator->generateIfElseBlock(irContext, scope)->markAsFakeBlock(),
            endBlock
        );
        currentIfNode->setNext(elseIfNode);
        currentIfNode = elseIfNode;
    }

    if (node->getElseBlock()) {
        auto elseBlock = irGenerator->generateIfElseBlock(irContext, scope);
        this->setupBlock(elseBlock, node->getElseBlock().value()->getBlock(), irGenerator, scope, irContext);
        return std::make_shared<IRIfStatementNode>(node, ifNode, elseBlock);
    }
    return std::make_shared<IRIfStatementNode>(node, ifNode);
}

std::shared_ptr<IRBlockNode> IfStatementIRStrategy::setupBlock(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<ASTControlFlowBlockNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    for (auto statement : *node->getContents()) {
        irBlockNode->insert(irGenerator->generateFor(statement, irBlockNode->getScope(), irContext));
    }
    return irBlockNode;
}