//
// Created by Johny Georges on 2024-05-23.
//

#include "while-statement-type-signature-strategy.h"

void WhileStatementTypeSignatureStrategy::assign(ASTWhileStatementNode* whileStatementNode, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForCondition(whileStatementNode->getCondition(), scope);
    strategyMap->assignTypeSignatureForBlockContents(whileStatementNode->getBlock(), scope);
}