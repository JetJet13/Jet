//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-variable-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

IRStatementNode* VariableAssignmentStatementIRStrategy::generate(ASTVariableAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto isGlobal = scope->findGlobalVariable(node->getVariableAssignment()->getIdentifierNode()->getId()).has_value();
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, isGlobal ? IR_COPY_GLOBAL_ASSIGNMENT_OP : IR_COPY_ASSIGNMENT_OP);
    return new IRVariableAssignmentStatementNode(node, irExpression);
}