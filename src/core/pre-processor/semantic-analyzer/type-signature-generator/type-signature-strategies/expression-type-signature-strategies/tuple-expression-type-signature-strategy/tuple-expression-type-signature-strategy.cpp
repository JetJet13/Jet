//
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void TupleExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTTupleExpressionNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = std::vector<std::shared_ptr<TypeSignature>>();
    for (uint64_t i = 0; i < node->numItems(); ++i) {
        auto tupleItem = node->getItems()->at(i);
        strategyMap->assignTypeSignatureFor(tupleItem->getItem(), context, scope);
        auto valueTypeSignature = tupleItem->getItem()->getTypeSignature()->convertToVariableTypeSignature();
        valueTypeSignature->setKeyId(std::to_string(i));
        typeSignatures.push_back(valueTypeSignature);
    }
    node->setTypeSignature(std::make_shared<TupleTypeSignature>(typeSignatures));
}