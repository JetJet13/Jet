//
// Created by Johny Georges on 2024-12-31.
//

#include "argument-list-type-signature-strategy.h"

void ArgumentListTypeSignatureStrategy::assign(std::shared_ptr<ASTFunctionArgumentListNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto argumentTypes = std::vector<std::shared_ptr<TypeSignature>>();
    if (context->getTypeSignatures() && context->getTypeSignatures().value()->size() != node->numArguments()) {
        node->setTypeSignature(std::make_shared<ArgumentListTypeSignature>(argumentTypes));
        return;
    }
    for (int i = 0; i < node->numArguments(); ++i) {
        auto argument = node->getArguments()->at(i);
        auto argumentContext = context;
        if (context->getTypeSignatures()) {
            argumentContext = std::make_shared<TypeSignatureContext>(context->getTypeSignatures().value()->at(i));
        }
        strategyMap->assignTypeSignatureFor(argument->getArgument(), argumentContext, scope);
        argumentTypes.push_back(argument->getArgument()->getTypeSignature()->convertToVariableTypeSignature());
    }

    node->setTypeSignature(std::make_shared<ArgumentListTypeSignature>(argumentTypes));
}