//
// Created by Johny Georges on 2024-05-11.
//

#include "unary-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void UnaryExpressionTypeSignatureStrategy::assign(ASTUnaryExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), scope);
    if (node->getExpressionNode()->getTypeSignature()->isUnknownOrInvalidOrVoid()) {
        node->setTypeSignature(new InvalidTypeSignature());
        return;
    }

    auto unaryOperatorSymbol = node->getUnaryOperatorNode()->getOperator()->getToken()->getSymbol();
    if (unaryOperatorSymbol->isBang()) {
        node->setTypeSignature(new BoolLiteralTypeSignature());
        return;
    } else if (unaryOperatorSymbol->isPlus() || unaryOperatorSymbol->isMinus()) {
        if (node->getExpressionNode()->getTypeSignature()->is(INT_LITERAL_TYPE_SOURCE)) {
            node->setTypeSignature(new IntLiteralTypeSignature());
            return;
        } else if (node->getExpressionNode()->getTypeSignature()->is(FLOAT_LITERAL_TYPE_SOURCE)) {
            node->setTypeSignature(new FloatLiteralTypeSignature());
            return;
        }

    }

    node->setTypeSignature(new InvalidTypeSignature());
}