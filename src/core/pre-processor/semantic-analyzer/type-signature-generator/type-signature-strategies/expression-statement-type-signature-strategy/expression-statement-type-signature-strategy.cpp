//
// Created by Johny Georges on 2024-05-23.
//

#include "expression-statement-type-signature-strategy.h"

void ExpressionStatementTypeSignatureStrategy::assign(ASTExpressionStatementNode* expressionStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(expressionStatementNode->getExpression(), scope);
}