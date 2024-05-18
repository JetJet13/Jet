//
// Created by Johny Georges on 2024-05-11.
//

#include "unary-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

TypeSignature* UnaryExpressionTypeSignatureStrategy::create(ASTUnaryExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto expressionTypeSignature = strategyMap->getTypeSignatureForExpression(node->getExpressionNode(), scope);
    if (expressionTypeSignature->isUnknownOrInvalidOrVoid()) {
        return new InvalidTypeSignature();
    }

    auto unaryOperatorSymbol = node->getUnaryOperatorNode()->getOperator()->getToken()->getSymbol();
    if (unaryOperatorSymbol->isBang()) {
        return new BoolLiteralTypeSignature();
    } else if (unaryOperatorSymbol->isPlus() || unaryOperatorSymbol->isMinus()) {
        if (expressionTypeSignature->is(INT_LITERAL_TYPE_SOURCE)) {
            return new IntLiteralTypeSignature();
        } else if (expressionTypeSignature->is(FLOAT_LITERAL_TYPE_SOURCE)) {
            return new FloatLiteralTypeSignature();
        }

    }

    return new InvalidTypeSignature();
}