//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-statement-type-signature-strategy.h"

void ModuleAccessAssignmentStatementTypeSignatureStrategy::assign(ASTModuleAccessAssignmentStatementNode* moduleAccessAssignmentStatement, TypeSignatureContext* context,  TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(moduleAccessAssignmentStatement->getExpression(), context, scope);
    moduleAccessAssignmentStatement->getExpression()->setTypeSignature(
        moduleAccessAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
    strategyMap->assignTypeSignatureFor(moduleAccessAssignmentStatement->getModuleAccessAssignment()->getModuleAccess(), context, scope);
}