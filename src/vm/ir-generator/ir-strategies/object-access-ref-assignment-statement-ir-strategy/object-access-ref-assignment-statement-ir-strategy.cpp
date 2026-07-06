//
// Created by Johny Georges on 2026-06-27.
//

#include "object-access-ref-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-ref-assignment-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-static-property-ref-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> ObjectAccessRefAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTObjectAccessRefAssignmentStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    if (node->getObjectAccessAssignment()->getObjectAccess()->getSource()->getSource()->getTypeSignature()->typeSourceIs(CLASS_TYPE_SOURCE)) {
        return std::make_shared<IRClassStaticPropertyRefAssignmentStatementNode>(
                node,
                std::dynamic_pointer_cast<IRClassStaticPropertyAccessExpressionNode>(irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP))),
                irExpression
        );
    }
    return std::make_shared<IRObjectAccessRefAssignmentStatementNode>(
            node,
            std::dynamic_pointer_cast<IRObjectAccessExpressionNode>(irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP))),
            irExpression
    );
}