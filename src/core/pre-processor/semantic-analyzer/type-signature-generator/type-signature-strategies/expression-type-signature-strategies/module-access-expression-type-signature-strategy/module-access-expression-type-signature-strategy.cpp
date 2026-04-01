//
// Created by Johny Georges on 2024-11-07.
//

#include "module-access-expression-type-signature-strategy.h"

void ModuleAccessExpressionTypeSignatureStrategy::assign(ASTModuleAccessExpressionNode* moduleAccessExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignature = scope->find(moduleAccessExpression->getId());
    moduleAccessExpression->setTypeSignature(typeSignature);
}