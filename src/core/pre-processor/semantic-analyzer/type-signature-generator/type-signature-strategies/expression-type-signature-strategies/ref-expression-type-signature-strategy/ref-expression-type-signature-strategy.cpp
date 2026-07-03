//
// Created by Johny Georges on 2025-02-01.
//

#include "ref-expression-type-signature-strategy.h"

void RefExpressionTypeSignatureStrategy::assign(ASTRefExpressionNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), context, scope);
    if (node->getExpressionNode()->getTypeSignature()->isUnknownOrInvalidOrVoid()) {
        node->setTypeSignature(new RefTypeSignature());
        return;
    }

    node->setTypeSignature(new RefTypeSignature(node->getExpressionNode()->getTypeSignature()->convertToVariableTypeSignature()));
}