//
// Created by Johny Georges on 2024-05-08.
//

#include "function-return-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void FunctionReturnExpressionTypeSignatureStrategy::assign(ASTFunctionReturnExpressionNode* functionReturnExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(functionReturnExpression->getExpression(), scope);
    Logger::log("FunctionReturnExpressionTypeSignatureStrategy");
    Logger::log(functionReturnExpression->toSourceCode());
    functionReturnExpression->getExpression()->getTypeSignature()->print();
    Logger::log("!----");
    functionReturnExpression->setTypeSignature(functionReturnExpression->getExpression()->getTypeSignature());
}