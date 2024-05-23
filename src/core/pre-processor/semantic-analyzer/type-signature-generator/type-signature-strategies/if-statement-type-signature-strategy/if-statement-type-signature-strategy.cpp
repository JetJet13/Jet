//
// Created by Johny Georges on 2024-05-22.
//

#include "if-statement-type-signature-strategy.h"

void IfStatementTypeSignatureStrategy::assign(ASTIfStatementNode* ifStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForCondition(ifStatementNode->getIfBlock()->getCondition(), scope);
    strategyMap->assignTypeSignatureForBlockContents(ifStatementNode->getIfBlock()->getBlock(), scope);

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        strategyMap->assignTypeSignatureForCondition(elseIfBlock->getCondition(), scope);
        strategyMap->assignTypeSignatureForBlockContents(elseIfBlock->getBlock(), scope);
    }

    if (ifStatementNode->getElseBlock()) {
        strategyMap->assignTypeSignatureForBlockContents(
            ifStatementNode->getElseBlock().value()->getBlock(),
            scope
        );
    }
}