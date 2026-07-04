//
// Created by Johny Georges on 2024-05-23.
//

#include "try-statement-type-signature-strategy.h"

void TryStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTTryStatementNode> tryStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(tryStatementNode->getTryBlock()->getBlock(), context, scope);
    strategyMap->assignTypeSignatureFor(tryStatementNode->getCatchBlock()->getBlock(), context, scope);
    if (tryStatementNode->getFinallyBlock()) {
        strategyMap->assignTypeSignatureFor(
            tryStatementNode->getFinallyBlock().value()->getBlock(),
            context,
            scope
        );
    }
}