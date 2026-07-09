//
// Created by Johny Georges on 2026-02-20.
//

#include "class-property-ref-value-assignment-statement-ir-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-property-ref-value-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> ClassPropertyRefValueAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTClassPropertyRefValueAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irClassType = std::dynamic_pointer_cast<IRClassType>(scope->findGlobalType(node->getPropertyAssignment()->getClassAccess()->getThis()->getId()).value());
    auto propertyName = node->getPropertyAssignment()->getProperty()->getId();
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    return std::make_shared<IRClassPropertyRefValueAssignmentStatementNode>(
            node,
            irExpression,
            propertyName,
            irClassType->getClassProperties()->getStructIRType()->getIndexForKey(propertyName)
    );
}