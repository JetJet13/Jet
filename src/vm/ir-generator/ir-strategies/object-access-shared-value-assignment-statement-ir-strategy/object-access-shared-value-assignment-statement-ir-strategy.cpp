//
// Created by Johny Georges on 2026-06-27.
//

#include "object-access-shared-value-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-shared-value-assignment-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-static-property-shared-value-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> ObjectAccessSharedValueAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTObjectAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    if (node->getObjectAccessAssignment()->getObjectAccess()->getSource()->getSource()->getTypeSignature()->typeSourceIs(CLASS_TYPE_SOURCE)) {
        return std::make_shared<IRClassStaticPropertySharedValueAssignmentStatementNode>(
                node,
                std::dynamic_pointer_cast<IRClassStaticPropertyAccessExpressionNode>(irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
                irExpression
        );
    }
    return std::make_shared<IRObjectAccessSharedValueAssignmentStatementNode>(
            node,
            std::dynamic_pointer_cast<IRObjectAccessExpressionNode>(irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
            irExpression
    );
}