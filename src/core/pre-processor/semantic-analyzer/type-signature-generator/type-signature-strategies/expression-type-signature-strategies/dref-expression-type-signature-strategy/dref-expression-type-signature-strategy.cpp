//
// Created by Johny Georges on 2025-02-01.
//

#include "dref-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/shared-type-signature/shared-type-signature.h"

void DrefExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTDrefExpressionNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getExpressionNode(), context, scope);
    if (node->getExpressionNode()->getTypeSignature()->getTargetTypeSignature()->typeSourceIs(SHARED_TYPE_SOURCE)) {
        auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(node->getExpressionNode()->getTypeSignature()->getTargetTypeSignature());
        node->setTypeSignature(sharedTypeSignature->getUnderlyingType());
    } else {
        node->setTypeSignature(std::make_shared<UnknownTypeSignature>());
    }
}