//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-item-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ParameterListItemTypeSignatureStrategy::assignAndAddToScope(ASTFunctionParameterNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(node->getType(), context, scope);
    node->setTypeSignature(new ParameterListItemTypeSignature(
        node->getIdentifier()->getIdentifierNode()->getId(),
        node->getType()->getTypeSignature()->convertToVariableTypeSignature()
    ));
}