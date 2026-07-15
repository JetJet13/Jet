//
// Created by Johny Georges on 2026-06-27.
//

#include "module-access-shared-value-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-module-access-shared-value-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> ModuleAccessSharedValueAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTModuleAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();

    return std::make_shared<IRModuleAccessSharedValueAssignmentStatementNode>(
            node,
            std::dynamic_pointer_cast<IRModuleAccessExpressionNode>(irGenerator->generateFor(node->getModuleAccessAssignment()->getModuleAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
            irExpression
    );
}