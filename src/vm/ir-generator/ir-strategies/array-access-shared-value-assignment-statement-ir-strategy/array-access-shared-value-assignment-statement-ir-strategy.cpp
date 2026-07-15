//
// Created by Johny Georges on 2026-06-27.
//

#include "array-access-shared-value-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-array-access-shared-value-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> ArrayAccessSharedValueAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTArrayAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    return std::make_shared<IRArrayAccessSharedValueAssignmentStatementNode>(
            node,
            std::dynamic_pointer_cast<IRArrayAccessExpressionNode>(irGenerator->generateFor(node->getArrayAccessAssignment()->getArrayAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
            irExpression
    );
}