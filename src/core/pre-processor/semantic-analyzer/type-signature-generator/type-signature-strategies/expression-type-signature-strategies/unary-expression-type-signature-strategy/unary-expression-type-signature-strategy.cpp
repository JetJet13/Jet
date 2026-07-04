//
// Created by Johny Georges on 2024-05-11.
//

#include "unary-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void UnaryExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTUnaryExpressionNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), context, scope);
    if (node->getExpressionNode()->getTypeSignature()->isUnknownOrInvalidOrVoid()) {
        node->setTypeSignature(std::make_shared<InvalidTypeSignature>());
        return;
    }

    auto unaryOperatorSymbol = node->getUnaryOperatorNode()->getLexeme()->getToken()->getSymbol();
    if (unaryOperatorSymbol->isBang()) {
        node->setTypeSignature(std::make_shared<BoolLiteralTypeSignature>());
        return;
    } else if (unaryOperatorSymbol->isPlus() || unaryOperatorSymbol->isMinus()) {
        if (node->getExpressionNode()->getTypeSignature()->typeTargetIs(INT_LITERAL_TYPE_SOURCE)) {
            node->setTypeSignature(std::make_shared<IntLiteralTypeSignature>());
            return;
        } else if (node->getExpressionNode()->getTypeSignature()->typeTargetIs(FLOAT_LITERAL_TYPE_SOURCE)) {
            node->setTypeSignature(std::make_shared<FloatLiteralTypeSignature>());
            return;
        }

    }

    node->setTypeSignature(std::make_shared<InvalidTypeSignature>());
}