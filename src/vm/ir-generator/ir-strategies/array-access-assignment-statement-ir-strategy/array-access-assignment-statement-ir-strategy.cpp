//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-array-access-assignment-statement-node.h"

IRStatementNode* ArrayAccessAssignmentStatementIRStrategy::generate(ASTArrayAccessAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    return new IRArrayAccessAssignmentStatementNode(
        node,
        (IRArrayAccessExpressionNode*)irGenerator->generateFor(node->getArrayAccessAssignment()->getArrayAccess(), scope, irContext, IR_COPY_REASSIGNMENT_OP),
        irGenerator->generateFor(node->getExpression(), scope, irContext, IR_OPERAND_VALUE_OP)
    );
}