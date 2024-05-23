//
// Created by Johny Georges on 2024-05-23.
//

#include "condition-type-signature-strategy.h"

void ConditionTypeSignatureStrategy::assign(ASTControlFlowConditionNode* controlFlowConditionNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForExpression(controlFlowConditionNode->getCondition(), scope);
    controlFlowConditionNode->setTypeSignature(
        controlFlowConditionNode->getCondition()->getTypeSignature()
    );
}