//
// Created by Johny Georges on 2024-05-22.
//

#include "if-statement-type-signature-strategy.h"

void IfStatementTypeSignatureStrategy::assign(ASTIfStatementNode* ifStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(ifStatementNode->getIfBlock()->getCondition(), scope);
    strategyMap->assignTypeSignatureFor(ifStatementNode->getIfBlock()->getBlock(), scope);

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        strategyMap->assignTypeSignatureFor(elseIfBlock->getCondition(), scope);
        strategyMap->assignTypeSignatureFor(elseIfBlock->getBlock(), scope);
    }

    if (ifStatementNode->getElseBlock()) {
        strategyMap->assignTypeSignatureFor(
            ifStatementNode->getElseBlock().value()->getBlock(),
            scope
        );
    }
}