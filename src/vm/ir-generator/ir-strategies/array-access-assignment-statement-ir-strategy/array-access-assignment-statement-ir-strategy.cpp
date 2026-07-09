//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-array-access-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> ArrayAccessAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTArrayAccessAssignmentStatementNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    return std::make_shared<IRArrayAccessAssignmentStatementNode>(
        node,
        std::dynamic_pointer_cast<IRArrayAccessExpressionNode>(irGenerator->generateFor(node->getArrayAccessAssignment()->getArrayAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
        irExpression
    );
}