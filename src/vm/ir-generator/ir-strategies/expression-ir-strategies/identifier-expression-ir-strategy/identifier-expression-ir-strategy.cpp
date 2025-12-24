//
// Created by Johny Georges on 2024-06-26.
//

#include "identifier-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../../../shared/utils/logger/logger.h"

IRExpressionNode* IdentifierExpressionIRStrategy::generate(ASTIdentifierExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto id = node->getIdentifierNode()->getId();
    auto allocation = scope->findAcrossScopes(id);
    if (irOperation->isCopy() && allocation.value()->getIRType()->getSourceType()->requiresArc()) {
        return new IRIdentifierExpressionNode(node, allocation.value(), irGenerator->generateArcAllocation(irContext));
    }
    return new IRIdentifierExpressionNode(node, allocation.value(), scope->findArc(id));
}