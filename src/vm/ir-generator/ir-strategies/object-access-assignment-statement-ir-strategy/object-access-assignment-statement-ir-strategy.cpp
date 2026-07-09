//
// Created by Johny Georges on 2025-08-30.
//

#include "object-access-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-assignment-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-static-property-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> ObjectAccessAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTObjectAccessAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    if (node->getObjectAccessAssignment()->getObjectAccess()->getSource()->getSource()->getTypeSignature()->typeSourceIs(CLASS_TYPE_SOURCE)) {
        return std::make_shared<IRClassStaticPropertyAssignmentStatementNode>(
                node,
                std::dynamic_pointer_cast<IRClassStaticPropertyAccessExpressionNode>(irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
                irExpression
        );
    }
    return std::make_shared<IRObjectAccessAssignmentStatementNode>(
            node,
            std::dynamic_pointer_cast<IRObjectAccessExpressionNode>(irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
            irExpression
    );
}