//
// Created by Johny Georges on 2024-05-23.
//

#include "for-statement-type-signature-strategy.h"

void ForStatementTypeSignatureStrategy::assign(ASTForStatementNode* forStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(forStatementNode->getVariable()->getVariable(), scope);
    forStatementNode->getVariable()->setTypeSignature(
        forStatementNode
        ->getVariable()
        ->getVariable()
        ->getTypeSignature()
    );

    strategyMap->assignTypeSignatureFor(forStatementNode->getSource()->getSource(), scope);
    forStatementNode->getSource()->setTypeSignature(
        forStatementNode
        ->getSource()
        ->getSource()
        ->getTypeSignature()
    );

    strategyMap->assignTypeSignatureFor(forStatementNode->getBlock(), scope);
}