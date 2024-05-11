//
// Created by Johny Georges on 2024-05-11.
//

#include "literal-expression-type-signature-strategy.h"

TypeSignature* LiteralExpressionTypeSignatureStrategy::create(ASTLiteralExpressionNode* literalExpression, TypeSignatureStrategyProvider* strategyMap) {
    return strategyMap->getTypeSignatureFor(literalExpression->getLiteralNode());
}