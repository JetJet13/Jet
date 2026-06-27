//
// Created by Johny Georges on 2026-06-27.
//

#include "module-access-ref-assignment-statement-type-signature-strategy.h"

void ModuleAccessRefAssignmentStatementTypeSignatureStrategy::assign(ASTModuleAccessRefAssignmentStatementNode* moduleAccessRefAssignmentStatement, TypeSignatureContext* context,  TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(moduleAccessRefAssignmentStatement->getModuleAccessAssignment()->getModuleAccess(), context, scope);

    auto expressionStatementContext = new TypeSignatureContext(moduleAccessRefAssignmentStatement->getModuleAccessAssignment()->getModuleAccess()->getTypeSignature());
    strategyMap->assignTypeSignatureFor(moduleAccessRefAssignmentStatement->getExpression(), expressionStatementContext, scope);
    moduleAccessRefAssignmentStatement->getExpression()->setTypeSignature(
            moduleAccessRefAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
}