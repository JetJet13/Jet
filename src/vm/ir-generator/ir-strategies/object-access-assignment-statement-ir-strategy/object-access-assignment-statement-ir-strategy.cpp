//
// Created by Johny Georges on 2025-08-30.
//

#include "object-access-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-assignment-statement-nodes/ir-object-access-assignment-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-static-property-assignment-node/ir-class-static-property-assignment-node.h"

IRStatementNode* ObjectAccessAssignmentStatementIRStrategy::generate(ASTObjectAccessAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    if (node->getObjectAccessAssignment()->getObjectAccess()->getSource()->getSource()->getTypeSignature()->typeSourceIs(CLASS_TYPE_SOURCE)) {
        return new IRClassStaticPropertyAssignmentStatementNode(
                node,
                (IRClassStaticPropertyAccessExpressionNode*)irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)),
                irExpression
        );
    }
    return new IRObjectAccessAssignmentStatementNode(
            node,
            (IRObjectAccessExpressionNode*)irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)),
            irExpression
    );
}