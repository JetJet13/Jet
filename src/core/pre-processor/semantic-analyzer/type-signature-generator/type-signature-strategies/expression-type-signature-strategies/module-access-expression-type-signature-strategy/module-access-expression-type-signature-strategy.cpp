//
// Created by Johny Georges on 2024-11-07.
//

#include "module-access-expression-type-signature-strategy.h"

void ModuleAccessExpressionTypeSignatureStrategy::assign(ASTModuleAccessExpressionNode* moduleAccessExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    moduleAccessExpression->setTypeSignature(scope->find(moduleAccessExpression->getId()));
}