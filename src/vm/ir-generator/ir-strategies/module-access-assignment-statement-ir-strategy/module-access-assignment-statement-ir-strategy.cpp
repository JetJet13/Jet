//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-module-access-assignment-statement-node.h"

IRStatementNode* ModuleAccessAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTModuleAccessAssignmentStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();

    return new IRModuleAccessAssignmentStatementNode(
            node,
            (IRModuleAccessExpressionNode*)irGenerator->generateFor(node->getModuleAccessAssignment()->getModuleAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP)),
            irExpression
    );
}