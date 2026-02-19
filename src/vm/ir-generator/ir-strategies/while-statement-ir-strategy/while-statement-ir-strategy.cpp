//
// Created by Johny Georges on 2025-05-24.
//

#include "while-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-while-statement-node/ir-while-statement-node.h"

IRStatementNode* WhileStatementIRStrategy::generate(ASTWhileStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto whileConditionIRExpression = irGenerator->generateFor(node->getCondition()->getCondition(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    auto whileConditionBlock = irGenerator->generateWhileConditionBlock(irContext, scope);
    auto whileBodyBlock = irGenerator->generateWhileBodyBlock(irContext, scope);
    this->setupBlock(whileBodyBlock, node->getBlock(), irGenerator, scope, irContext);
    auto endBlock = irGenerator->generateWhileEndBlock(irContext, scope);
    return new IRWhileStatementNode(node, whileConditionIRExpression, whileConditionBlock, whileBodyBlock, endBlock);
}

IRBlockNode* WhileStatementIRStrategy::setupBlock(IRBlockNode* irBlockNode, ASTControlFlowBlockNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    for (auto statement : *node->getContents()) {
        irBlockNode->insert(irGenerator->generateFor(statement, irBlockNode->getScope(), irContext));
    }
    return irBlockNode;
}