//
// Created by Johny Georges on 2024-05-23.
//

#include "try-statement-type-signature-strategy.h"

void TryStatementTypeSignatureStrategy::assign(ASTTryStatementNode* tryStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForBlockContents(tryStatementNode->getTryBlock()->getBlock(), scope);
    strategyMap->assignTypeSignatureForBlockContents(tryStatementNode->getCatchBlock()->getBlock(), scope);
    if (tryStatementNode->getFinallyBlock()) {
        strategyMap->assignTypeSignatureForBlockContents(
            tryStatementNode->getFinallyBlock().value()->getBlock(),
            scope
        );
    }
}