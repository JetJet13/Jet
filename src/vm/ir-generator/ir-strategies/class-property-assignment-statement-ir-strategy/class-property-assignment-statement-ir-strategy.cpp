//
// Created by Johny Georges on 2025-01-02.
//

#include "class-property-assignment-statement-ir-strategy.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-property-assignment-statement-node.h"

IRStatementNode* ClassPropertyAssignmentStatementIRStrategy::generate(ASTClassPropertyAssignmentStatementNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irClassType = (IRClassType*)scope->findType(node->getPropertyAssignment()->getClassAccess()->getThis()->getId()).value();
    auto propertyName = node->getPropertyAssignment()->getProperty()->getId();
    return new IRClassPropertyAssignmentStatementNode(
            node,
            irGenerator->generateFor(node->getExpression(), scope, irContext, IR_OPERAND_VALUE_OP),
            propertyName,
            irClassType->getClassProperties()->getIndexForKey(propertyName)
    );
}