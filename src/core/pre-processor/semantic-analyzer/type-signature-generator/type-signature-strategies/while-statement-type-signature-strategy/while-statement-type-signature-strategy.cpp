//
// Created by Johny Georges on 2024-05-23.
//

#include "while-statement-type-signature-strategy.h"

void WhileStatementTypeSignatureStrategy::assign(ASTWhileStatementNode* whileStatementNode, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(whileStatementNode->getCondition(), context, scope);
    strategyMap->assignTypeSignatureFor(whileStatementNode->getBlock(), context, scope);
}