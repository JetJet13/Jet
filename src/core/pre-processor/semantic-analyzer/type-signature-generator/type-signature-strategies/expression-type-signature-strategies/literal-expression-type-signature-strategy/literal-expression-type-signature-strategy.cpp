//
// Created by Johny Georges on 2024-05-11.
//

#include "literal-expression-type-signature-strategy.h"

void LiteralExpressionTypeSignatureStrategy::assign(ASTLiteralExpressionNode* literalExpression, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForLiteral(literalExpression->getLiteralNode());
    literalExpression->setTypeSignature(literalExpression->getLiteralNode()->getTypeSignature());
}