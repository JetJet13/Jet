//
// Created by Johny Georges on 2026-06-27.
//

#include "tuple-access-ref-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-tuple-access-ref-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> TupleAccessRefAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTTupleAccessRefAssignmentStatementNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    return std::make_shared<IRTupleAccessRefAssignmentStatementNode>(
            node,
            std::dynamic_pointer_cast<IRTupleAccessExpressionNode>(irGenerator->generateFor(node->getTupleAccessAssignment()->getTupleAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
            irExpression
    );
}