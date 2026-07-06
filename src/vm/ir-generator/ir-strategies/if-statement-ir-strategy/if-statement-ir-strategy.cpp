//
// Created by Johny Georges on 2025-01-08.
//

#include "if-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-else-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-statement-node.h"

std::shared_ptr<IRStatementNode> IfStatementIRStrategy::generate(std::shared_ptr<ASTIfStatementNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto ifConditionIRExpression = irGenerator->generateFor(node->getIfBlock()->getCondition()->getCondition(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
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
        auto elseIfConditionIRExpression = irGenerator->generateFor(elseIf->getCondition()->getCondition(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
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

std::shared_ptr<IRBlockNode> IfStatementIRStrategy::setupBlock(std::shared_ptr<IRBlockNode> irBlockNode, std::shared_ptr<ASTControlFlowBlockNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    for (auto statement : *node->getContents()) {
        irBlockNode->insert(irGenerator->generateFor(statement, irBlockNode->getScope(), irContext));
    }
    return irBlockNode;
}