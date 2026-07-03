//
// Created by Johny Georges on 2024-05-23.
//

#include "condition-type-signature-strategy.h"

void ConditionTypeSignatureStrategy::assign(ASTControlFlowConditionNode* controlFlowConditionNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(controlFlowConditionNode->getCondition(), context, scope);
    controlFlowConditionNode->setTypeSignature(
        controlFlowConditionNode->getCondition()->getTypeSignature()
    );
}