//
// Created by Johny Georges on 2025-01-08.
//

#include "if-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-else-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-if-statement-nodes/ir-if-statement-node.h"

IRStatementNode* IfStatementIRStrategy::generate(ASTIfStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto ifConditionIRExpression = irGenerator->generateFor(node->getIfBlock()->getCondition()->getCondition(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto ifConditionBlock = irGenerator->generateIfBlock(irContext);
    auto thenBlock = irGenerator->generateIfThenBlock(irContext);
    this->setupBlock(thenBlock, node->getIfBlock()->getBlock(), irGenerator, scope, irContext);
    auto elseBlock = irGenerator->generateIfElseBlock(irContext);
    if (node->getElseBlock()) {
        this->setupBlock(elseBlock, node->getElseBlock().value()->getBlock(), irGenerator, scope, irContext);
    }

    auto endBlock = irGenerator->generateIfEndBlock(irContext);
    auto ifNode = new IRIfElseNode(ifConditionIRExpression, ifConditionBlock, thenBlock, elseBlock, endBlock);
    auto currentIfNode = ifNode;
    for (auto elseIf : *node->getElseIfBlocks()) {
        auto elseIfConditionIRExpression = irGenerator->generateFor(elseIf->getCondition()->getCondition(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
        auto elseIfNode = new IRIfElseNode(
            elseIfConditionIRExpression,
            irGenerator->generateIfBlock(irContext),
            this->setupBlock(irGenerator->generateIfThenBlock(irContext), elseIf->getBlock(), irGenerator, scope, irContext),
            irGenerator->generateIfElseBlock(irContext),
            endBlock
        );
        currentIfNode->setNext(elseIfNode);
        currentIfNode = elseIfNode;
    }
    return new IRIfStatementNode(node, ifNode);
}

IRBlockNode* IfStatementIRStrategy::setupBlock(IRBlockNode* irBlockNode, ASTControlFlowBlockNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto blockScope = new IRLookupTable(scope);
    for (auto statement : *node->getContents()) {
        irBlockNode->insert(irGenerator->generateFor(statement, blockScope, irContext));
    }
    return irBlockNode;
}