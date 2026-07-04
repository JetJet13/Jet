//
// Created by Johny Georges on 2026-06-27.
//

#include "module-access-ref-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-module-access-ref-assignment-statement-node.h"

IRStatementNode* ModuleAccessRefAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTModuleAccessRefAssignmentStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();

    return new IRModuleAccessRefAssignmentStatementNode(
            node,
            (IRModuleAccessExpressionNode*)irGenerator->generateFor(node->getModuleAccessAssignment()->getModuleAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)),
            irExpression
    );
}