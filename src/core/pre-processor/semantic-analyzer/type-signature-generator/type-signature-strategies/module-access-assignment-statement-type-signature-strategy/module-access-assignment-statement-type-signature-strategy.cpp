//
// Created by Johny Georges on 2026-04-02.
//

#include "module-access-assignment-statement-type-signature-strategy.h"

void ModuleAccessAssignmentStatementTypeSignatureStrategy::assign(ASTModuleAccessAssignmentStatementNode* moduleAccessAssignmentStatement, std::shared_ptr<TypeSignatureContext> context,  std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(moduleAccessAssignmentStatement->getModuleAccessAssignment()->getModuleAccess(), context, scope);

    auto expressionStatementContext = std::make_shared<TypeSignatureContext>(moduleAccessAssignmentStatement->getModuleAccessAssignment()->getModuleAccess()->getTypeSignature());
    strategyMap->assignTypeSignatureFor(moduleAccessAssignmentStatement->getExpression(), expressionStatementContext, scope);
    moduleAccessAssignmentStatement->getExpression()->setTypeSignature(
        moduleAccessAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
}