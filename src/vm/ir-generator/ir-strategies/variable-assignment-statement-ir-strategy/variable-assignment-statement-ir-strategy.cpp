//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-variable-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRStatementNode> VariableAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTVariableAssignmentStatementNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto isGlobal = scope->findGlobalVariable(node->getVariableAssignment()->getIdentifierNode()->getId()).has_value();
    auto irOperation = std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP);
    if (isGlobal) {
        irOperation->markAsGlobal();
    }
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, irOperation);
    irExpression->markAsAssigned();
    return std::make_shared<IRVariableAssignmentStatementNode>(node, irExpression);
}