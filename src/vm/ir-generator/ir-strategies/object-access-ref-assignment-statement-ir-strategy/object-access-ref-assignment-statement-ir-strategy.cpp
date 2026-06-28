//
// Created by Johny Georges on 2026-06-27.
//

#include "object-access-ref-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-ref-assignment-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-static-property-ref-assignment-statement-node.h"

IRStatementNode* ObjectAccessRefAssignmentStatementIRStrategy::generate(ASTObjectAccessRefAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    if (node->getObjectAccessAssignment()->getObjectAccess()->getSource()->getSource()->getTypeSignature()->typeSourceIs(CLASS_TYPE_SOURCE)) {
        return new IRClassStaticPropertyRefAssignmentStatementNode(
                node,
                (IRClassStaticPropertyAccessExpressionNode*)irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)),
                irExpression
        );
    }
    return new IRObjectAccessRefAssignmentStatementNode(
            node,
            (IRObjectAccessExpressionNode*)irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)),
            irExpression
    );
}