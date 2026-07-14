//
// Created by Johny Georges on 2026-07-11.
//

#include "share-expression-type-signature-strategy.h"

void ShareExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTShareExpressionNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), context, scope);
    if (node->getExpressionNode()->getTypeSignature()->isUnknownOrInvalidOrVoid()) {
        node->setTypeSignature(std::make_shared<SharedTypeSignature>());
        return;
    }

    node->setTypeSignature(std::make_shared<SharedTypeSignature>(node->getExpressionNode()->getTypeSignature()->convertToVariableTypeSignature()));
}