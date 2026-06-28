//
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-ref-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-array-access-ref-assignment-statement-node.h"

IRStatementNode* ArrayAccessRefAssignmentStatementIRStrategy::generate(ASTArrayAccessRefAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    return new IRArrayAccessRefAssignmentStatementNode(
            node,
            (IRArrayAccessExpressionNode*)irGenerator->generateFor(node->getArrayAccessAssignment()->getArrayAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)),
            irExpression
    );
}