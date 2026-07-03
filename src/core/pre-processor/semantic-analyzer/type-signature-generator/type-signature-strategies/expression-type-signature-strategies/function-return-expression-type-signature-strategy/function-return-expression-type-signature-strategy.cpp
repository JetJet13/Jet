//
// Created by Johny Georges on 2024-05-08.
//

#include "function-return-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void FunctionReturnExpressionTypeSignatureStrategy::assign(ASTFunctionReturnExpressionNode* functionReturnExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    if (functionReturnExpression->getExpression()) {
        strategyMap->assignTypeSignatureFor(functionReturnExpression->getExpression().value(), context, scope);
        functionReturnExpression->setTypeSignature(functionReturnExpression->getExpression().value()->getTypeSignature());
    } else {
        functionReturnExpression->setTypeSignature(new VoidTypeSignature());
    }
}