//
// Created by Johny Georges on 2025-07-21.
//

#include "print-statement-type-signature-strategy.h"

void PrintStatementTypeSignatureStrategy::assign(ASTPrintStatementNode* printStatementNode, TypeSignatureContext* context,  TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    for (auto argument : *printStatementNode->getArguments()->getArguments()) {
        strategyMap->assignTypeSignatureFor(argument->getArgument(), context, scope);
    }
}