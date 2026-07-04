//
// Created by Johny Georges on 2024-05-22.
//

#include "if-statement-type-signature-strategy.h"

void IfStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTIfStatementNode> ifStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(ifStatementNode->getIfBlock()->getCondition(), context, scope);
    strategyMap->assignTypeSignatureFor(ifStatementNode->getIfBlock()->getBlock(), context, scope);

    for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
        strategyMap->assignTypeSignatureFor(elseIfBlock->getCondition(), context, scope);
        strategyMap->assignTypeSignatureFor(elseIfBlock->getBlock(), context, scope);
    }

    if (ifStatementNode->getElseBlock()) {
        strategyMap->assignTypeSignatureFor(
            ifStatementNode->getElseBlock().value()->getBlock(),
            context,
            scope
        );
    }
}