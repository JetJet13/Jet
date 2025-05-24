//
// Created by Johny Georges on 2024-05-23.
//

#include "for-in-statement-type-signature-strategy.h"
#include "../../../../../type-signature/array-type-signature/array-type-signature.h"

void ForInStatementTypeSignatureStrategy::assign(ASTForInStatementNode* forStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(forStatementNode->getSource()->getSource(), scope);
    forStatementNode->getSource()->setTypeSignature(
            forStatementNode
                    ->getSource()
                    ->getSource()
                    ->getTypeSignature()
    );

    if (forStatementNode->getSource()->getSource()->getTypeSignature()->typeSourceIs(ARRAY_TYPE_SOURCE)) {
        auto arrayTypeSignature = (ArrayTypeSignature*)forStatementNode->getSource()->getSource()->getTypeSignature();
        forStatementNode->getVariable()->getVariable()->setTypeSignature(arrayTypeSignature->getElementType());
    } else {
        forStatementNode->getVariable()->getVariable()->setTypeSignature(new UnknownTypeSignature());
    }
    forStatementNode->getVariable()->setTypeSignature(
        forStatementNode->getVariable()->getVariable()->getTypeSignature()
    );
    scope->insert(forStatementNode->getVariable()->getVariable()->getId(), forStatementNode->getVariable()->getTypeSignature());
    strategyMap->assignTypeSignatureFor(forStatementNode->getBlock(), scope);
}