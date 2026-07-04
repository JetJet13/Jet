//
// Created by Johny Georges on 2024-05-11.
//

#include "literal-expression-type-signature-strategy.h"

void LiteralExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTLiteralExpressionNode> literalExpression, std::shared_ptr<TypeSignatureContext> context, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(literalExpression->getLiteralNode(), context);
    literalExpression->setTypeSignature(literalExpression->getLiteralNode()->getTypeSignature());
}