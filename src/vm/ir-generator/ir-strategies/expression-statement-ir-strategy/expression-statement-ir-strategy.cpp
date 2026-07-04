//
// Created by Johny Georges on 2024-11-25.
//

#include "expression-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-expression-statement-node.h"

IRStatementNode* ExpressionStatementIRStrategy::generate(std::shared_ptr<ASTExpressionStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return new IRExpressionStatementNode(node, irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)));
}