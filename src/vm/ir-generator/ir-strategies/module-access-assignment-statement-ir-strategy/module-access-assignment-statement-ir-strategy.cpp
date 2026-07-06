//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-module-access-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> ModuleAccessAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTModuleAccessAssignmentStatementNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();

    return std::make_shared<IRModuleAccessAssignmentStatementNode>(
            node,
            std::dynamic_pointer_cast<IRModuleAccessExpressionNode>(irGenerator->generateFor(node->getModuleAccessAssignment()->getModuleAccess(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP))),
            irExpression
    );
}