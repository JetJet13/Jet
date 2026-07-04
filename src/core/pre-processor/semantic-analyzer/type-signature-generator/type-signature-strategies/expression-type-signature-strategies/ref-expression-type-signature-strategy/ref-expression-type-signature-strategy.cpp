//
// Created by Johny Georges on 2025-02-01.
//

#include "ref-expression-type-signature-strategy.h"

void RefExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTRefExpressionNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), context, scope);
    if (node->getExpressionNode()->getTypeSignature()->isUnknownOrInvalidOrVoid()) {
        node->setTypeSignature(std::make_shared<RefTypeSignature>());
        return;
    }

    node->setTypeSignature(std::make_shared<RefTypeSignature>(node->getExpressionNode()->getTypeSignature()->convertToVariableTypeSignature()));
}