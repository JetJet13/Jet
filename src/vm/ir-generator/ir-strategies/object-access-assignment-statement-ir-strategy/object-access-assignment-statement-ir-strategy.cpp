//
// Created by Johny Georges on 2025-08-30.
//

#include "object-access-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-assignment-statement-nodes/ir-object-access-assignment-statement-node.h"

IRStatementNode* ObjectAccessAssignmentStatementIRStrategy::generate(ASTObjectAccessAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    return new IRObjectAccessAssignmentStatementNode(
            node,
            (IRObjectAccessExpressionNode*)irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)),
            irExpression
    );
}