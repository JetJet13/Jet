//
// Created by Johny Georges on 2024-05-11.
//

#include "literal-expression-type-signature-strategy.h"

void LiteralExpressionTypeSignatureStrategy::assign(ASTLiteralExpressionNode* literalExpression, TypeSignatureContext* context, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(literalExpression->getLiteralNode(), context);
    literalExpression->setTypeSignature(literalExpression->getLiteralNode()->getTypeSignature());
}