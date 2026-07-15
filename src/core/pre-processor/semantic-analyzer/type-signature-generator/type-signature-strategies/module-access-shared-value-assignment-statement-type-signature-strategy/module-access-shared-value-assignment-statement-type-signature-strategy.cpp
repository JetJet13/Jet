//
// Created by Johny Georges on 2026-06-27.
//

#include "module-access-shared-value-assignment-statement-type-signature-strategy.h"

void ModuleAccessSharedValueAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTModuleAccessSharedValueAssignmentStatementNode> moduleAccessSharedValueAssignmentStatement, std::shared_ptr<TypeSignatureContext> context,  std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(moduleAccessSharedValueAssignmentStatement->getModuleAccessAssignment()->getModuleAccess(), context, scope);

    auto expressionStatementContext = std::make_shared<TypeSignatureContext>(moduleAccessSharedValueAssignmentStatement->getModuleAccessAssignment()->getModuleAccess()->getTypeSignature());
    strategyMap->assignTypeSignatureFor(moduleAccessSharedValueAssignmentStatement->getExpression(), expressionStatementContext, scope);
    moduleAccessSharedValueAssignmentStatement->getExpression()->setTypeSignature(
            moduleAccessSharedValueAssignmentStatement->getExpression()->getTypeSignature()->convertToVariableTypeSignature()
    );
}