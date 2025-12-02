//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-tuple-access-assignment-statement-node.h"

IRStatementNode* TupleAccessAssignmentStatementIRStrategy::generate(ASTTupleAccessAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    return new IRTupleAccessAssignmentStatementNode(
            node,
            (IRTupleAccessExpressionNode*)irGenerator->generateFor(node->getTupleAccessAssignment()->getTupleAccess(), scope, irContext, new IROperation(IR_COPY_REASSIGNMENT_OP)),
            irExpression
    );
}