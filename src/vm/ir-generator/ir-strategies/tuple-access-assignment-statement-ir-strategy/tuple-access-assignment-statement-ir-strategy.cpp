//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-tuple-access-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> TupleAccessAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTTupleAccessAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    return std::make_shared<IRTupleAccessAssignmentStatementNode>(
            node,
            std::dynamic_pointer_cast<IRTupleAccessExpressionNode>(irGenerator->generateFor(node->getTupleAccessAssignment()->getTupleAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
            irExpression
    );
}