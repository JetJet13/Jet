//
// Created by Johny Georges on 2024-05-23.
//

#include "expression-statement-type-signature-strategy.h"

void ExpressionStatementTypeSignatureStrategy::assign(ASTExpressionStatementNode* expressionStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(expressionStatementNode->getExpression(), context, scope);
}