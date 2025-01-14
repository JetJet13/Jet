//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-variable-assignment-statement-node.h"

IRStatementNode* VariableAssignmentStatementIRStrategy::generate(ASTVariableAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return new IRVariableAssignmentStatementNode(node, irGenerator->generateFor(node->getExpression(), scope, irContext, IR_OPERAND_OP));
}