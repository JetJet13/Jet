//
// Created by Johny Georges on 2024-05-25.
//

#include "procedure-declaration-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../types/type-checker-error-message-table.h"

namespace ProcedureDeclarationTypeCheckerPolicy {
    void apply(ASTProcedureDeclarationNode* procedureDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getParameters(), typeCheckerResult);
        TypeChecker::applyPolicyTo(procedureDeclarationNode->getBlock(), typeCheckerResult);
        auto returnExpressionMessage = TypeCheckerErrorMessageTable::ProcedureHasReturnExpression(procedureDeclarationNode);
        TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule()->enforce(
            procedureDeclarationNode->getBlock(),
            returnExpressionMessage,
            typeCheckerResult
        );
    }
}