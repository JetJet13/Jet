//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-assignment-statement-ir-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-property-assignment-statement-node.h"

IRStatementNode* ClassPropertyAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTClassPropertyAssignmentStatementNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irClassType = std::dynamic_pointer_cast<IRClassType>(scope->findGlobalType(node->getPropertyAssignment()->getClassAccess()->getThis()->getId()).value());
    auto propertyName = node->getPropertyAssignment()->getProperty()->getId();
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, new IROperation(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    return new IRClassPropertyAssignmentStatementNode(
            node,
            irExpression,
            propertyName,
            irClassType->getClassProperties()->getStructIRType()->getIndexForKey(propertyName)
    );
}