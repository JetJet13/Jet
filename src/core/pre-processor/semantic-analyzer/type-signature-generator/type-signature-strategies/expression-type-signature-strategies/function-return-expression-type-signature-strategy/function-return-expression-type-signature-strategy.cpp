//
// Created by Johny Georges on 2024-05-08.
//

#include "function-return-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void FunctionReturnExpressionTypeSignatureStrategy::assign(ASTFunctionReturnExpressionNode* functionReturnExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(functionReturnExpression->getExpression(), scope);
    functionReturnExpression->setTypeSignature(functionReturnExpression->getExpression()->getTypeSignature());
}