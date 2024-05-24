//
// Created by Johny Georges on 2024-05-23.
//

#include "try-statement-type-signature-strategy.h"

void TryStatementTypeSignatureStrategy::assign(ASTTryStatementNode* tryStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(tryStatementNode->getTryBlock()->getBlock(), scope);
    strategyMap->assignTypeSignatureFor(tryStatementNode->getCatchBlock()->getBlock(), scope);
    if (tryStatementNode->getFinallyBlock()) {
        strategyMap->assignTypeSignatureFor(
            tryStatementNode->getFinallyBlock().value()->getBlock(),
            scope
        );
    }
}